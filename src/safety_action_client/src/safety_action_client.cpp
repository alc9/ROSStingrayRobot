#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <action_client/defAction.h>
#include <string>
#include <iostream>
#include <iostream>
#include <std_msgs/Empty.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Int8.h>
#include <object_detection/GoalPos.h>
#include <object_detection/GoalPositions.h>
#include <object_detection/Localization.h>
#include <object_detection/LocalizationRequest.h>
#include <object_detection/LocalizationResponse.h>
/*
 * The action client handles goal and event-based behaviour, such as searching for the goal location or handling a water leakage
 */
//SafetyClient monitors safety, informs user and cancels ros nodes if a safety issue is severe 

class SafetyClient{
    protected:
        ros::NodeHandle nh_;
        //define server 
        actionlib::SimpleActionClient<action_client::defAction>action_client_;
	//subscribers
	ros::Subscriber gt_grove_sub_;
	ros::Subscriber gt_bmp_pressure_sub_;
	ros::Subscriber gt_bmp_temp_sub_;
	ros::Subscriber gt_ram_sub_;
	ros::Subscriber gt_gpu_sub_;
	ros::Subscriber gt_jetson_power_sub_;
	ros::Subscriber gt_gpu_temp_sub_;
	ros::Subscriber gt_cpu_temp_sub_;
	ros::Subscriber gt_core_avg_sub_;
	
	bool is_dry_;
	float bmp_pressure_;
	float bmp_temp_;
	float ram_;
	float gpu_;
	float jetson_power_;
	float gpu_temp_;
	float cpu_temp_;
	float core_avg_;
	//limit for diagnostics that cause cancellation
	float max_bmp_temp_;
	//user warning limit
	float warn_bmp_temp_;
	//user intervene limit
	float intervene_bmp_temp_;
	//user
	bool user_in_loop_;
	bool user_set_shutdown_;
    public:
        SafetyClient():
            action_client_(nh_,"stingray/actions",true,boost::bind(&SafetyClient::actionCb,this),true){
                max_bmp_temp_ = 50.0;//50.0;
		intervene_bmp_temp=48.0;
		warn_bmp_temp_=30.0;
		user_in_loop_=false;
		user_set_shutdown_=false;
		initializeSubscribers();
		ROS_INFO_STREAM("safety_client is waiting for action_client server...");
		action_client_.waitForServer();
                ROS_INFO_STREAM("Server is now up for safety_client!");
	    }
	
	void actionCb(){
		while(ros::ok){
			if (!is_dry_){
				userInLoop(std::string("water leakge"));
				if (user_set_shutdown_){shutdown();}
			}
			if (max_bmp_temp_ < bmp_temp_){
				shutdown();
				continue;	
			}
			if (intervene_bmp_temp_ < bmp_temp_){
				userInLoop(std::string("water leakge"));
				if (user_set_shutdown_){shutdown(); continue;}
			}
			if (warn_bmp_tmp_ < bmp_temp_){
				ROS_INFO_STREAM("Robot temperature is greater than warn temperature " << warn_bmp_temp_);
			}	
		
		}
		return;
	}

    private:
	void setUserInputMap()
	void initializeSubscribers(void){
		//initialize the subscribers		
		gt_grove_sub_=nh_.subscribe("stingray/pysensors/grove_is_dry",1,&SafetyClient::subscriberCbGrove,this);
		gt_bmp_pressure_sub_=nh_.subscribe("stingray/pysensors/pressure",1,&SafetyClient::subscriberCbPressure,this);
		gt_bmp_temp_sub_=nh_.subscribe("stingray/pysensors/temperature",1,&SafetyClient::subscriberCbTemp,this);
		gt_ram_sub_=nh_.subscribe("stingray/pysensors/RAM",1,&SafetyClient::subscriberCbRAM,this);
		gt_gpu_sub_=nh_subscribe("stingray/pysensors/GPU",1,&SafetyClient::subscriberCbGPU,this);
		gt_jetson_power_sub_=nh_.subscribe("stingray/pysensors/jetson_power",1,&SafetyClient::subscriberCbJetsonPower,this);
		gt_gpu_temp_sub_=nh_subscribe("stingray/pysensors/GPU_temperature",1,&SafetyClient::subscriberCbGPUTemp,this);
		gt_cpu_temp_sub_=nh_.subscribe("stingray/pysensors/CPU_temperature",1,&SafetyClient::subscriberCbCPUTemp,this);
		gt_core_avg_sub_=nh_subscribe("stingray/pysensors/CPU_average_load",1,&SafetyClient::subscriberCbAvgLoad,this);
	}
	//30.0 is the max operating temperature	for the water sensor
	void subscriberCbGrove(const std_msgs::Bool::ConstPtr &info){this->is_dry_=(info->data>30.1) ? true : info->data;}
	void subscriberCbPressure(const std_msgs::Bool::ConstPtr &info){this->bmp_pressure_=info->data;}
	void subscriberCbTemp(const std_msgs::Bool::ConstPtr &info){if(this->user_in_loop_){if(this->bmp_temp_>this->max_bmp_temp){ros::Shutdown();}}else{this->bmp_temp_=info->data;}}
	void subscriberCbRAM(const std_msgs::Bool::ConstPtr &info){this->ram_=info->data;}
	void subscriberCbGPU(const std_msgs::Bool::ConstPtr &info){this->gpu_=info->data;}
	void subscriberCbJetsonPower(const std_msgs::Bool::ConstPtr &info){this->jetson_power_=info->data;}
	void subscriberCbGPUTemp(const std_msgs::Bool::ConstPtr &info){this->gpu_temp_=info->data;}
	void subscriberCbCPUTEMP(const std_msgs::Bool::ConstPtr &info){this->cpu_temp_=info->data;}
	void subscriberCbAvgLoad(const std_msgs::Bool::ConstPtr &info){this->core_avg_=info->data;}
	void shutdown(){ROS_INFO_STREAM("shutting down ROS robot!!!");ros::shutdown();}	
	
	// 0 = leakage, 1 = temp reached, 2 = ram reached, 3 = gpu reached, 4 = power surge jetson 	
	void userInLoop(std::string reason){
		char response;
		bool responseReceived=false;
		while (!responseReceived){
			std::cout << "system warning: " << reason << ". Do you want the mission to end (y/n)"<<"\n";
			cin >> response;
			switch(response)
			{
				case 'y':
					user_set_shutdown_=true;
					break;
				case 'n':
					std::cout<<"not shutting down"<<"\n";
					break;
				default:
					std::cout<<"invalid input"
					break;
				
			}
		}
	}

	void cancelGoal(int stopLevelSeverity){
		//call preemptedRequestOn with level of stop severity action_severity
		std_msgs::Int8 stopLevelSeverity_;
		stopLevelSeverity_.data=stopLevelSeverity;
		stop_severity_pub_.publish(stopLevelSeverity_);
		action_client_.cancelGoal();	
	}
};

int main(int argc,char** argv){
    ros::init(argc,argv,"safety_action_client_node");
    SafetyClient stingraySafetyActionClient;
    ros::spin();
    return 0;
}
