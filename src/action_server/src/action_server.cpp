#include <ros/ros.h>
#include <tf2_eigen/tf2_eigen.h>
#include <actionlib/server/simple_action_server.h>
#include<action_server/defAction.h>
#include <tf/transform_listener.h>
//#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Quaternion.h>
#include <tf/LinearMath/Matrix3x3.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseStamped.h>
#include <sensor_msgs/Imu.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Empty.h>
#include <std_msgs/Int8.h>
#include <std_msgs/Float32.h>
#include <std_msgs/String.h>
#include <cmath>
#include <tf/transform_datatypes.h>
/*
 * The action server handles the controller and plant control system, it is communicated to by the action client which handles safety and current goal logic. The action client sends goal and cancellation messages to the action server, whilst the action server sends status,result and feedback messages to the action client.
 */
//TODO: determine a suitable error threshold for modifying the frequency of one of the fins
//class containing action server methods

class MoveStingrayAction{
    protected:
        //node handle to create subscribers and publishers
        ros::NodeHandle nh_;
        // define server
        actionlib::SimpleActionServer<action_server::defAction> action_server_;
        std::string action_name_;
        //feedback sent to action client
        action_server::defFeedback feedback_;
        //result sent to action client
        action_server::defResult result_;

        //define subscribers
        //pose identifies tells us location and orientation of camera
        //TODO:check odom sub quality - if low switch to sensor fusion
	ros::Subscriber gt_odom_sub_;
	//tf::TransformListener tf_listener_;
	ros::Subscriber gt_emergency_stop_sub_;
	float x_;
        float y_;
        float z_;
        float x0_;
	float y0_;
	float z0_;
	//define publishers
        ros::Publisher frequency_left_pub_;
        ros::Publisher frequency_right_pub_;
	ros::Publisher pause_flag_pub_;
    	//control parameters
	float gp_x_;
	float gp_y_;
	float gp_z_;
	float kp_;
	float nomF_;
	float deltaF_;
	float yaw_ref_;
	//published messages
	std_msgs::Float32 f_left_;
	std_msgs::Float32 f_right_;
	std_msgs::Bool pause_flag_;
	//safety subscriber
	bool emergency_stop_flag_;
       	//state variable
	int goal_id_;
	//goal found when this far away
	float approach_distance_;	

    public:
        MoveStingrayAction(std::string name,float nomF, float kp,float approachDistance=0.2) : 
            action_server_(nh_,name,boost::bind(&MoveStingrayAction::actionCb,this,_1),false),action_name_(name){
                emergency_stop_flag_ = false;
		f_left_=std_msgs::Float32();
		f_right_=std_msgs::Float32();
		nomF_ = nomF;
		kp_ = kp;
		approach_distance_=approachDistance;
		//goal id 0,1,2 = search,move to location,move to home location (stop at end)
		//-1 indicates no state
		goal_id_ = -1;
		initializeSubscribers();
                initializePublishers();
                action_server_.start();
		ROS_INFO_STREAM("action_server is up...");

            }
        ~MoveStingrayAction(void){
        
        }
    private:

        //initialize subscribers
        void initializeSubscribers(void){
		//may need to switch to sensor fusion if there are too many dropped frames
		// rtabmap/odom - /odometry/filtered
        	gt_odom_sub_=nh_.subscribe("/odometry/filtered",1,&MoveStingrayAction::subscriberCbOdom,this);
		gt_emergency_stop_sub_ = nh_.subscribe("/stingray/control/emergency_stop_flag",1,&MoveStingrayAction::subscriberCbES,this);
		ROS_INFO_STREAM("Subscribers initialized");
        }

        //initiliaze publishers
        void initializePublishers(void){
            //initialize publisher with queue =1 
            frequency_left_pub_=nh_.advertise<std_msgs::Float32>("stingray/control/frequency_left",0);
            frequency_right_pub_=nh_.advertise<std_msgs::Float32>("stingray/control/frequency_right",0);
	    pause_flag_pub_ = nh_.advertise<std_msgs::Bool>("stingray/control/pause_flag",0);
	    ROS_INFO_STREAM("Publishers initialized");
        }
	
	void printOdom(){
		std::cout<<"x: "<<x_<<" y: "<<y_<<" z: "<< z_ <<" x0: "<<x0_<<" y0: "<<y0_<<" z0: "<<z0_<<std::endl;
	}
        //define callback functions
        //callback for get_pos_sub_ and helper functions
	void subscriberCbOdom(const nav_msgs::Odometry::ConstPtr &info) {
	    this->x_=info->pose.pose.position.x;
            this->z_=info->pose.pose.position.y;
            this->y_=info->pose.pose.position.z;
	    //std::cout<<"x: "<<x_<<" y: "<<y_<<" z: "<< z_ <<std::endl;
	    tf::Quaternion tmpQuat;
	    double x0,y0,z0;
	    tf::quaternionMsgToTF(info->pose.pose.orientation,tmpQuat);
	    tf::Matrix3x3(tmpQuat).getRPY(x0,y0,z0);
	    this->x0_=x0;
	    this->z0_=y0;
	    this->y0_=z0;
        }
/*	
	void getRobotOdom(){
		try{
			//geometry_msgs::TransformStamped tfStamped = this->tf_listener_.lookupTransform("/map","/camera_link",ros::Time::now());//ros::Duration(0.17));
			auto tfMat = tf2::transformToEigen(tfStamped);
			x_=tfMat[0][3];
			y_=tfMat[2][3];
			z_=tfMat[1][3];
			x0_=tfMat[0][0];
			y0_=tfMat[2][2];
			z0_=tfMat[3][3];
				
		}
		catch (tf2::TransformException ex){
			ROS_ERROR("%s",ex.what());
		}
	
	}
*/
	void subscriberCbES(const std_msgs::Bool::ConstPtr &info){
		emergency_stop_flag_=info->data;
	}

	void setYawRef(){
		// ab is the from the initial position to where it is heading, bc is to the goal position from the initial position
		// z is out of the camera, x is to the left hand side of the camera, y is down
		float nextZ = z_ + 1.0 * cos(y0_);
		float nextX = x_ + 1.0 * sin(y0_);
		float ABx = nextX - x_;
		float ABz = nextZ - z_;
		float BCx = gp_x_ - x_;
		float BCz = gp_z_ - z_;
		float dotProduct = ABx * BCx 
				+ ABz * BCz;
		float magAB = ABx * ABx
	       			+ ABz * ABz;
		float magBC = BCx * BCx 
				+ BCz * BCz;
		float angle = dotProduct;
		angle/=sqrt(magAB * magBC);
		this->yaw_ref_ = acos(angle);
	}

       	void actuatorController(){
		//this->getRobotOdom();
		this->setYawRef();
		float errorTheta = (180.0/M_PI)*(yaw_ref_ - y0_);
		//if large error rotate
		ROS_INFO_STREAM("error theta: "<<errorTheta<<" ref: "<<yaw_ref_<<" y0_: " << y0_);
		if (abs(errorTheta) > 90.0){
			if (errorTheta>0){
				f_left_.data = 1.5;
				f_right_.data = 0.0;
			}
			else{
			f_right_.data = 1.5;
			f_left_.data = 0.0;
			}
			frequency_left_pub_.publish(f_left_);
			frequency_right_pub_.publish(f_right_);
			return;	
		}
		float deltaF_=kp_ * errorTheta;
		//set bounds for published frequency
		f_left_.data = std::max(std::min(nomF_ - deltaF_,2.0f),-2.0f);
		f_right_.data = std::max(std::min(nomF_ + deltaF_,2.0f),-2.0f);
		frequency_left_pub_.publish(f_left_);
		frequency_right_pub_.publish(f_right_);
		printOdom();
		if (abs(f_right_.data) == 2.0 || abs(f_left_.data == 2.0)){
			ROS_INFO_STREAM("frequency is bounded");
		}
	}

	//calculates the distance between the current location and the goal location in 3D 
        double calcDistance3D(){
            double dist;
            dist  = sqrt(pow((gp_x_-x_),2)+pow((gp_y_-y_),2)+pow((gp_z_-z_),2));
            return dist;
        }

        double calcDistance2D(){
            double dist;
            dist  = sqrt(pow((gp_x_-x_),2)+pow((gp_y_-y_),2));
            return dist;
        }

        double calcDistanceZ(){
            double dist;
            dist  = sqrt(pow((gp_z_-z_),2));
            return dist;
        }

	void reset(){
		goal_id_=-1;	
		f_left_.data=0.0;
                f_right_.data=0.0;
                frequency_left_pub_.publish(f_left_);
                frequency_right_pub_.publish(f_right_);
                //ROS_INFO_STREAM("Preempted: id="<<goal->id<<" ");//<<action_name_.c_str());
		pause_flag_.data = true;
		pause_flag_pub_.publish(pause_flag_);
	}
	
	bool preemptReset(){
		reset();	
		action_server_.setPreempted();
	}

	//rotate -> lower nose/camera -> move forward/backwards a bit
        //0=rotate then lower nose,1=rotate raise nose/camera, 2=move forwards/backwards random choice unless there is a boundary the distance moved forward is in relation to the field of view
	bool search(int searchingMethod=0){
		switch(searchingMethod){
			case 0:
                        {
			f_left_.data = 1.0;
			f_right_.data = 1.0; 
                        ROS_INFO_STREAM("calling searching method case 0");
			frequency_left_pub_.publish(f_left_);
			frequency_right_pub_.publish(f_right_);
                        //when flat is true increment searchingMethod
			break;
                        }
                   	case 1:
                        {
                        ROS_INFO_STREAM("calling searching method case 1");
			break;
                        }
                    	case 2:
                        {
                        ROS_INFO_STREAM("calling searching method case 2");
			break;
                        }
                    }
		//always returns false
		return false;
	}

	bool goToGoal(){
		//this->getRobotOdom();
		this->setYawRef();
		feedback_.distance=calcDistance3D();
		if (feedback_.distance < approach_distance_){
			//goal complete send results
			return(true);
		}
		action_server_.publishFeedback(feedback_);
		actuatorController();
		return false;
	}

	bool goToHome(){
		if (goToGoal()){
			return true;	
		}
		else{
			return false;
		}
		//go to home behaviour
	}
	
	bool callGoal(){
		switch(goal_id_){
			case 0:
				return(search());
				break;
			case 1:
				return(goToGoal());
				break;
			case 2:
				return(goToHome());
				break;
		}	
	
	}

        void actionCb(const action_server::defGoalConstPtr &goal){
		//TODO: add rate to reduce processing load
		//goal id 0,1,2 = search,move to location,move to home location (stop at end)	
		if(goal->id>0){
            		//set goal location
            		gp_x_=goal->x;
            		gp_y_=goal->y;
            		gp_z_=goal->z;
            		ROS_INFO_STREAM("goal position coordinates received");
            	}
		goal_id_=goal->id;
		pause_flag_.data=false;
		pause_flag_pub_.publish(pause_flag_);
		//main loop, emergency_stop_flag_ handled internally by nodes	
		while(ros::ok()){
			if (action_server_.isPreemptRequested()){
				preemptReset();
				return;
			}
			if (emergency_stop_flag_){
				while(emergency_stop_flag_){
					if(action_server_.isPreemptRequested()){
					preemptReset();
					return;
					}
				}
			}
			//we only worry about success - client cancels 
			if(callGoal()){
				reset();
				//inform of success
				result_.status=true;
				action_server_.setSucceeded(result_);
				return;
			}	
		}
	}
    };

int main(int argc, char** argv){

    ros::init(argc,argv,"action_server_node");
    //generates thread and runs MoveStingrayAction code
    //first argument is the name space the client uses for communication 
    float nomF = 1.4;
    float kp = 0.05;
    MoveStingrayAction stingrayActionServer("stingray/actions",nomF,kp);
    ros::spin();
    return 0;
}
