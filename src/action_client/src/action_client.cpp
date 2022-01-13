#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <action_client/defAction.h>
#include <queue> 
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <std_msgs/Empty.h>
#include <std_msgs/Int8.h>
#include <object_detection/GoalPos.h>
#include <object_detection/GoalPositions.h>
#include <object_detection/Localization.h>
#include <object_detection/LocalizationRequest.h>
#include <object_detection/LocalizationResponse.h>
//TODO: publisher shuts down object_detection
/*
 * The action client handles goal and event-based behaviour, such as searching for the goal location or handling a water leakage
 */
bool isSafe = false;
//class containing goal action client methods
class GoalClient{
    protected:
        ros::NodeHandle nh_;
        //define server 
        actionlib::SimpleActionClient<action_client::defAction>action_client_;
	//define server interactions 
	action_client::defGoal goal_;
        //member variables
	std::queue<int>goal_id_queue_;
        std::vector<float> goal_location_;
	float* goal_initial_distance_ptr_;
	float goal_initial_distance_;
	float goal_current_distance_;
	std::queue<std::vector<float>> goal_location_queue_;
	int current_goal_id_;
	bool object_detected_;
	float converge_speed_;
	bool converging_;
	float begin_time_;
	bool goal_location_achieved_;
	//search time is slightly more than allocated in action_server
	double search_time_;
	bool mission_complete_;
	//std::vector<std::vector<float>>way_points_;
    public:
        GoalClient(double searchTime,float convergeSpeed):
            action_client_(nh_,"goal_client",true),search_time_(searchTime),converge_speed_(convergeSpeed){
                action_client_.waitForServer();
                ROS_INFO("Server is now up for goal_client");
		current_goal_id_ = 0;
		goal_id_queue_.push(1);
		goal_id_queue_.push(2);
		object_detected_=false;
		converging_=true;
		mission_complete_=false;
		goal_initial_distance_ = 0;
		goal_location_achieved_=false;
		begin_time_=0;
            }
	~GoalClient(){}
    private:

	void printGoalLocation(){
		std::string infoString=std::string("Current goal location: "); 
		infoString.append(std::to_string(goal_location_[0]));
	       	infoString.append(", ");
		infoString.append(std::to_string(goal_location_[1]));
	       	infoString.append(", "); 
	       	infoString.append(std::to_string(goal_location_[2]));
		ROS_INFO_STREAM(infoString);
	}
	
	void saveGoalLocation(){
		//copy queue
		auto queueCp= goal_location_queue_;
		std::vector<float> goalLocationVector;
		std::string infoString;
		
		while (!queueCp.empty()){
			auto front = queueCp.front();
			goalLocationVector.push_back(front[0]);
			goalLocationVector.push_back(front[1]);
			goalLocationVector.push_back(front[2]);
			queueCp.pop();	
		}

		for(auto goalLocation=goalLocationVector.begin();goalLocation!=goalLocationVector.end();goalLocation++){
			infoString.append(std::to_string(*goalLocation));
	       		infoString.append(",");
		}
		std::ofstream out("cache/goalPositions.csv");
		out << infoString;
		out.close();
	}
	
	std::queue<std::vector<float>> loadGoalLocation(){
		auto readFileIntoString=[](const std::string& path)->std::string{
			auto ss = std::ostringstream{};
			std::ifstream input_file(path);
			if (!input_file.is_open()){
				ROS_INFO_STREAM("File is upon - please close for writing to");
			}
			ss<<input_file.rdbuf();
			return ss.str();
		};
		std::string gpString=readFileIntoString("cache/goalPositions.csv");
		//move positions into goal location queue
		std::vector<float>tmpVect;
		std::queue<std::vector<float>> queuePos;
		std::stringstream ss(gpString);
		int indexCounter=0;
		for (float i; ss >> i;){
			tmpVect.push_back(i);
			if (ss.peek()==','){
				indexCounter++;
				if (indexCounter%3==0){
					queuePos.push(tmpVect);
					tmpVect.clear();
				}
				ss.ignore();
			}
		}
		return queuePos;	
	}

	void reset(){
		converging_=true;
		goal_location_achieved_=false;
		goal_initial_distance_ptr_=0;
	
	}
	void sendGoal(){
		converging_=true;
		begin_time_ = ros::Time::now().toSec();
		goal_location_achieved_=false;
		goal_initial_distance_ptr_=0;
		action_client_.sendGoal(goal_,boost::bind(&GoalClient::doneCb,this,_1,_2),
				actionlib::SimpleActionClient<action_client::defAction>::SimpleActiveCallback(),
				boost::bind(&GoalClient::feedbackCb,this,_1));
	}
	
	bool getMissionStatus(){return mission_complete_;}
	
	void setGoal(){
		goal_.x=goal_location_[0];
		goal_.y=goal_location_[1];
		goal_.z=goal_location_[2];
		goal_.id=current_goal_id_;
	}

	void setGoalID(){
		goal_.id=current_goal_id_;
	}

	void setGoalLocationQueue(object_detection::GoalPositions& localizationResp){
		for(std::size_t i=0;i!=localizationResp.Coords.size();i++){
			goal_location_queue_.push(std::vector<float>{localizationResp.Coords[i].X,localizationResp.Coords[i].Y,localizationResp.Coords[i].Z});
		}	
	}

	void cancelGoal(){
		//call preemptedRequestOn with level of stop severity action_severity
		action_client_.cancelGoal();
	}

	void doneCb(const actionlib::SimpleClientGoalState &state,const action_client::defResultConstPtr &result){
		ROS_INFO_STREAM("Current goal achieved...");
		//goal location achieved even if cancelled before goal location
		//lets you know that the server publishing frequencies for motion has stopped
		goal_location_achieved_=result->status;
	}

	void feedbackCb(const action_client::defFeedbackConstPtr &feedback){
		if(!goal_initial_distance_ptr_){
			goal_current_distance_=feedback->distance;
			//goal_initial_distance_ points to a copy of first current distance
			goal_initial_distance_=goal_current_distance_;
			goal_initial_distance_ptr_=&goal_initial_distance_;
		}
		else{
			goal_current_distance_=feedback->distance;
		}
	}

    public:

	void goalClientMain(){
		/*
		 * Main function called during operation
		 */
		//TODO: while safety subscriber is true
		while(ros::ok()){
			if (current_goal_id_==0){
				if(!searchForObject()){
					//going home 
					//update server
					current_goal_id_=2;
					goal_location_=std::vector<float>{0,0,0};
					cancelGoal();
					setGoal();
					sendGoal();
					while (!goToHome() || converging_);
					if (!converging_){
						//user decide how to deal with this issue
						cancelGoal();
						//reset member variables
						reset();
						return;
					}
				}
				setGoal();
				//goal is ID = 1
				sendGoal();
			}
			//update converging to true
			if (current_goal_id_==1){
				while(!goToObject() || converging_);
				if (!converging_){
					ROS_INFO_STREAM("not converging on object going home...");
					goal_location_queue_.empty();
					//empty goal location queue - mission failed heading home	
				}
				//ID=2 return to home
				if(goal_location_queue_.size()==0){
					current_goal_id_=2;
					goal_location_=std::vector<float>{0,0,0};	
				}
				else{
					//search for the second bottle
					goal_location_=goal_location_queue_.front();
					goal_location_queue_.pop();
				}
				//inform of new goal location
				setGoal();
				//goal could be home or another object
				//action_client_.publishGoal(goal_);
				sendGoal();
				begin_time_=ros::Time::now().toSec();
				//get feedback and update goal_initial_distance_ and goal_current_distance_
			}
			if (current_goal_id_==2){
				while (!goToHome() || converging_);
				if (!converging_){
					//user decide how to deal with this issue
					cancelGoal();
				}
				ROS_INFO_STREAM("Mission complete powering off...");
				mission_complete_=true;
			}

		}
	}
	
	void searchForObjectTest(){
		while(ros::ok()){
			while(!searchForObject());
			printGoalLocation();
			return;			
		}	
	}

   private:

	bool goToObject(){
		//converging TODO: action_server should handle some instantaneous readings too
		if (!goal_location_achieved_){
			//this criteria might need to be mapped to speeds for a given time	
			auto tmpConverging = goal_initial_distance_-goal_current_distance_/ros::Time::now().toSec()-begin_time_>converge_speed_?true:false;
			if (!tmpConverging){
				//TODO: if not converging ask user if the robot should go home or go to the next object 
				goal_location_=std::vector<float>{0,0,0};
				converging_=false;
				}
			return false;
		}
		return true;
	}

	bool goToHome(){
		//converging TODO: action_server should handle some instantaneous readings too
		//get feedback from server
		if (!goal_location_achieved_){
		//this criteria might need to be mapped to speeds for a given time	
			auto tmpConverging = goal_initial_distance_-goal_current_distance_/ros::Time::now().toSec()-begin_time_>converge_speed_?true:false;
			if (!tmpConverging){
				//let user choose
				setGoalID();
				ROS_INFO_STREAM("goToHome is not converging...");

			}
			return false;
		}
		else{
			return true;
		}	
	
	}

        bool searchForObject(){
       		/*
		 * Search for object
		 */
		auto localizationClient=nh_.serviceClient<object_detection::Localization>("localize");
		object_detection::Localization localizationSrv;
		ROS_INFO_STREAM("waiting for service localize...");
		ros::service::waitForService("localize");
		try{
			if (localizationClient.call(localizationSrv)){
				ROS_INFO_STREAM("object detected");
				//set goal_location_queue
				setGoalLocationQueue(localizationSrv.response.Coords);
				goal_location_=goal_location_queue_.front();
				goal_location_queue_.pop();
				//set new goal
				current_goal_id_=goal_id_queue_.front();
				goal_id_queue_.pop();
				object_detected_=true;
				return true;	
			}
			//Not detected first time so will notify action_server to do a random search
			setGoalID();
			//publish goalId=0
			sendGoal();
			begin_time_ =ros::Time::now().toSec();
			while(!object_detected_ || ros::Time::now().toSec()-begin_time_<search_time_){
				object_detected_=localizationClient.call(localizationSrv);
			}
			if (object_detected_){
				ROS_INFO_STREAM("object detected");
				//set goal_location_queue
				setGoalLocationQueue(localizationSrv.response.Coords);	
				goal_location_=goal_location_queue_.front();
				goal_location_queue_.pop();
				current_goal_id_=goal_id_queue_.front();
				goal_id_queue_.pop();
				object_detected_=true;
				return true;	
			}
			else{
				ROS_INFO_STREAM("Object not detected - calling exit...");
				return false;
			}
		}catch(const std::exception& e){
			//catch service exceptions
			std::cout<<e.what();
		}
        }
};

//class containing safety action client methods
//SafetyClient listens to all safety nodes publishing and informs other clients 
//and action_server when there is a safety issue
//it also controls how these issues are dealt with 
class SafetyClient{
    protected:
	bool safetyError=false;
        ros::NodeHandle nh_;
        //define server 
        actionlib::SimpleActionClient<action_client::defAction>action_client_;
	ros::Publisher stop_severity_pub_;
    public:
        SafetyClient():
            action_client_(nh_,"safety_client",true){
                initializeSubscribers();
		initializePublishers();
		action_client_.waitForServer();
                ROS_INFO("Server is now up for action_client");
            }
    private:

	void initializeSubscribers(void){
		//initialize the subscribers		
	}

	void initializePublishers(void){
		stop_severity_pub_=nh_.advertise<std_msgs::Int8>("stingray/stop_severity",0);
	}

	void cancelGoal(int stopLevelSeverity){
		//call preemptedRequestOn with level of stop severity action_severity
		std_msgs::Int8 stopLevelSeverity_;
		stopLevelSeverity_.data=stopLevelSeverity;
		stop_severity_pub_.publish(stopLevelSeverity_);
		action_client_.cancelGoal();	
	}

        bool checkSafe(){
            ROS_INFO_STREAM("not implemented");
        }
};

int main(int argc,char** argv){
    ros::init(argc,argv,"action_client_node");
    SafetyClient stingraySafetyActionClient();
    //check is safe 
    isSafe=true;
    GoalClient stingrayGoalActionClient(140,0.05);    
    //stingrayGoalActionClient.goalClientMain();
    stingrayGoalActionClient.searchForObjectTest();
    ros::spin();
    return 0;
}
