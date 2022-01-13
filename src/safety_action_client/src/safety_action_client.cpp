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
//class containing safety action client methods
//SafetyClient listens to all safety nodes publishing and informs other clients 
//and action_server when there is a safety issue
//it also controls how these issues are dealt with
//TODO: e.g stop severity
class SafetyClient{
    protected:
	bool safetyError=false;
        ros::NodeHandle nh_;
        //define server 
        actionlib::SimpleActionClient<action_client::defAction>action_client_;
	ros::Publisher stop_severity_pub_;
    public:
        SafetyClient():
            action_client_(nh_,"stingray/actions",true){
                initializeSubscribers();
		initializePublishers();
		ROS_INFO_STREAM("safety_client is waiting for action_client server...");
		action_client_.waitForServer();
                ROS_INFO_STREAM("Server is now up for safety_client!");
	    }
	
	void safetyClientMain(){
			
	}
	void testSC(){
		int i =1;
		while(ros::ok){
			 i--;
		}
	}

    private:

	void initializeSubscribers(void){
		//initialize the subscribers		
	}

	void initializePublishers(void){
		stop_severity_pub_=nh_.advertise<std_msgs::Int8>("stingray/safety/stop_severity",0);
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
    ros::init(argc,argv,"safety_action_client_node");
    SafetyClient stingraySafetyActionClient;
    //check is safe
    stingraySafetyActionClient.testSC();
    //is this necessary
    ros::spin();
    return 0;
}
