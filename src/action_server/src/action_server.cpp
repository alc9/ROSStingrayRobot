#include <ros/ros.h>

#include <actionlib/server/simple_action_server.h>
#include<action_server/defAction.h>

#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseStamped.h>
#include <sensor_msgs/Imu.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Empty.h>
#include <std_msgs/Float64.h>
#include <std_msgs/String.h>
#include <cmath>
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
        double search_time_;
        //feedback sent to action client
        action_server::defFeedback feedback_;
        //result sent to action client
        action_server::defResult result_;

        //define subscribers
        //pose identifies tells us location and orientation of camera
        ros::Subscriber gt_odom_sub_;
        //geometry_msgs::PoseStamped pose_info_;
        //sensor_msgs::Imu imu_info_;
        //nav_msgs::Odometry odom_info_;
        float x_;
        float y_;
        float z_;
        /*
        //O is for orientation
        float xO_;
        float yO_;
        float zO_;
        float wO_;
        float u_;
        float x_;
        float y_;
        float uO_;
        float y0_;
        float z0_;
        */
        //define publishers
        ros::Publisher frequency_left_pub_;
        ros::Publisher frequency_right_pub_;
        ros::Publisher posctrl_pub_;
        ros::Publisher takeoff_pub_;
        std_msgs::Empty lift_;
    public:
        MoveStingrayAction(std::string name,double searchTime) : 
            action_server_(nh_,name,boost::bind(&MoveStingrayAction::actionCb,this,_1),false),action_name_(name),search_time_(searchTime){
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
            //initialize subscribers with queue =1
            //gt_imu_sub_=nh_.subscribe("imu",1,&MoveStingrayAction::subscriberCbImu,this);
            //gt_pos_sub_=nh_.subscribe("odom/sample",1,&MoveStingrayAction::subscriberCbPose,this);
            gt_odom_sub_=nh_.subscribe("odom/sample",1,&MoveStingrayAction::subscriberCbOdom,this);
            ROS_INFO_STREAM("Subscribers initialized");
        }

        //initiliaze publishers
        void initializePublishers(void){
            //initialize publisher with queue =1 
            frequency_left_pub_=nh_.advertise<std_msgs::Float64>("stingray/control/frequency_left",0);
            frequency_right_pub_=nh_.advertise<std_msgs::Float64>("stingray/control/frequency_right",0);
            posctrl_pub_=nh_.advertise<std_msgs::Bool>("stingray/control/posctrl",1);
            takeoff_pub_=nh_.advertise<std_msgs::Empty>("stingray/control/takeoff",1);
            //ROS_INFO_STREAM("Publishers initialized");
        }

        //define callback functions
        //callback for get_pos_sub_ and helper functions
        void subscriberCbOdom(const nav_msgs::Odometry::ConstPtr &info) {
            x_=info->pose.pose.position.x;
            y_=info->pose.pose.position.y;
            z_=info->pose.pose.position.z;
        }
        
        //calculates the distance between the current location and the goal location in 3D 
        double calcDistance3D(const action_server::defGoalConstPtr &goal){
            double dist;
            dist  = sqrt(pow((goal->x-x_),2)+pow((goal->y-y_),2)+pow((goal->z-z_),2));
            return dist;
        }

        double calcDistance2D(const action_server::defGoalConstPtr &goal){
            double dist;
            dist  = sqrt(pow((goal->x-x_),2)+pow((goal->y-y_),2));
            return dist;
        }

        double calcDistanceZ(const action_server::defGoalConstPtr &goal){
            double dist;
            dist  = sqrt(pow((goal->z-z_),2));
            return dist;
        }

        void actionCb(const action_server::defGoalConstPtr &goal){
            //ros::Rate rate(2);
            bool success = true;
            std_msgs::Float64 leftF;
            std_msgs::Float64 rightF;
            //goal id 0,1,2 = search,move to location,move to home location (stop at end)
            if(goal->id>0){
            //set goal location
            geometry_msgs::Pose moveTo;
            moveTo.position.x=goal->x;
            moveTo.position.y=goal->y;
            moveTo.position.z=goal->z;
            //advertise for actuator nodes
            takeoff_pub_.publish(lift_);
            std_msgs::Bool temp;
            temp.data=true;
            posctrl_pub_.publish(temp);
            ROS_INFO_STREAM("goal position coordinates received");
            //ROS_INFO_STREAM("x:"<<goal->x<<" y:"<<goal->y<<" z:"<<goal->z);
            }
            //move and control the stingray
            //goal->id to determine how to move
            switch (goal->id){
            case 0:
                {
                //rotate -> lower nose/camera -> move forward/backwards a bit
                double beginTime = ros::Time::now().toSec();
                do{ 
                    //perform a random search 
                    //0=rotate then lower nose,1=rotate raise nose/camera, 2=move forwards/backwards random choice unless there is a boundary the distance moved forward is in relation to the field of view
                    int searchingMethod = 0;
                    if (action_server_.isPreemptRequested()||!ros::ok()){
                        leftF.data=0.0;
                        rightF.data=0.0;
                        frequency_left_pub_.publish(leftF);
                        frequency_right_pub_.publish(rightF);
                        //ROS_INFO_STREAM("Preempted: id="<<goal->id<<" ");//<<action_name_.c_str());
                        action_server_.setPreempted();
                        success=false;
                        break;
                    }
                    switch(searchingMethod){
                    //rotate all the way around
                    //this is done by setting one of the actuators to its neutral position whilst the other one produces a wave
                    case 0:
                        {
                        ROS_INFO_STREAM("calling searching method case 0");
                        //when flat is true increment searchingMethod
                        }
                    case 1:
                        {
                        ROS_INFO_STREAM("calling searching method case 1");
                        }
                    case 2:
                        {
                        ROS_INFO_STREAM("when in doubt do nought");
                        //when flag is true set serchingMethod back to zero
                        }
                    }
                    rate.sleep(); 
                }
                while((double)(ros::Time::now().toSec()-beginTime)<search_time_);
                break;
                }
            case 1:
                {
                //publish initial wave frequencies to begin with
                leftF.data=2.0;
                rightF.data=2.0;
                frequency_left_pub_.publish(leftF);
                frequency_right_pub_.publish(rightF);
                do{
                    //echo /action_server/feedback
                    feedback_.distance=calcDistance3D(goal);
                    action_server_.publishFeedback(feedback_);
                    //take care of preemption (stop the stingray)
                    if (action_server_.isPreemptRequested()||!ros::ok()){
                        leftF.data=0.0;
                        rightF.data=0.0;
                        //emergency stopping not handled as preempt request
                        frequency_left_pub_.publish(leftF);
                        frequency_right_pub_.publish(rightF);
                        //ROS_INFO_STREAM("Preempted: id="<<goal->id<<" "<<action_name_.c_str());
                        action_server_.setPreempted();
                        success=false;
                        break;
                    }
		    //calculte the difference of frequency
		    //Kp*(yawRef-yawMeasured)
		    
		    //update fleft and right using these frequencies
                    //rate.sleep();
                    //invoke control-plant to determine frequencies to publish
                }
                while(feedback_.distance>0.1);
                break;
            }
        case 2:
            {
                //publish initial wave frequencies to begin with
                rightF.data=2.0;
                leftF.data=2.0;
                frequency_left_pub_.publish(leftF);
                frequency_right_pub_.publish(rightF);
                do{
                    //echo /action_server/feedback
                    feedback_.distance=calcDistance3D(goal);
                    action_server_.publishFeedback(feedback_);
                    //take care of preemption (stop the stingray)
                    if (action_server_.isPreemptRequested()||!ros::ok()){
                        rightF.data=0.0;
                        leftF.data=0.0;
                        frequency_left_pub_.publish(leftF);
                        frequency_right_pub_.publish(rightF);
                        //ROS_INFO_STREAM("Preempted: id="<<goal->id<<" ");//<<action_name_.c_str());
                        action_server_.setPreempted();
                        success=false;
                        break;
                    }
                    //rate.sleep();
                    //invoke control-plant to determine frequencies to publish
                }
                while(feedback_.distance>0.01);
                break;
            }

            }
        }

    };

int main(int argc, char** argv){

    ros::init(argc,argv,"action_server_node");
    //generates thread and runs MoveStingrayAction code
    //search time set to 2 minutes atm
    //first argument is the name space the client uses for communication 
    MoveStingrayAction stingrayActionServer("stingray/actions",120.0);
    //ROS Rate synchronizes the frequency for publishers
    //this is in hz 
    //ros::Rate rate(1.0);
    //ros::spinOnce();
    //rate.sleep();
    ros::spin();
    return 0;
}
