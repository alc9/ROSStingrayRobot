/*
 * Filename: actuator.cpp
 * Description: this code controls the right actuators 
 * Author: Alex Cunningham alexanderlewiscunningham@gmail.com
 * Start date: 01/12/2021
 * Last update: 14/01/2022
*/
#include <ros/ros.h>
#include "ActuatorMultiWave.h"
#include <std_msgs/Bool.h>
#include <std_msgs/Int8.h>
#include <std_msgs/Float32.h>
#include <cmath>
//main sends controls to the actuator
//subscribes to safety, frequency parameters, and emergency stop severity
//TODO: if system is at medium safety - e.g quite hot then clamp frequency params / amplitude
class RightActuatorCommander{
	protected:
		ros::NodeHandle nh_;
		ros::Subscriber gt_frequency_params_sub_;
		ros::Subscriber gt_emergency_stop_severity_level_sub_;
		ros::Subscriber gt_emergency_stop_flag_sub_;
		ros::Subscriber gt_pause_flag_sub_;
		//ros::CallbackQueue cb_queue_;
		float frequency_right_;
		bool emergency_stop_flag_;
		//this is received from action server
		bool pause_flag_;
		int emergency_stop_severity_level_;
	public: 
		RightActuatorCommander() :
			nh_(ros::NodeHandle())
		{
			initializeSubscribers();
			emergency_stop_flag_=false;
			pause_flag_=true;
			frequency_right_=0.0;
			emergency_stop_severity_level_=1;
			ROS_INFO_STREAM("right_fin_actuator initialized");
		}
	
	private:
		void initializeSubscribers(void){
			gt_frequency_params_sub_=this->nh_.subscribe("stingray/control/frequency_right",1,&RightActuatorCommander::subscriberFrequencyCb,this);
			gt_emergency_stop_severity_level_sub_=this->nh_.subscribe("stingray/control/emergency_stop_level",1,&RightActuatorCommander::subscriberEmergencyStopLevelCb,this);
			gt_emergency_stop_flag_sub_=this->nh_.subscribe("stingray/control/emergency_stop_flag",1,&RightActuatorCommander::subscriberEmergencyStopFlagCb,this);
			gt_pause_flag_sub_=this->nh_.subscribe("stingray/control/pause_flag",1,&RightActuatorCommander::subscriberPauseFlagCb,this);
		}

		void subscriberFrequencyCb(const std_msgs::Float32::ConstPtr &freq){this->frequency_right_ = freq->data;}
		void subscriberEmergencyStopLevelCb(const std_msgs::Int8::ConstPtr &level){this->emergency_stop_severity_level_=level->data;}
		void subscriberEmergencyStopFlagCb(const std_msgs::Bool::ConstPtr &sFlag){this->emergency_stop_flag_=sFlag->data; if (emergency_stop_flag_){this->pause_flag_=true;}}
		void subscriberPauseFlagCb(const std_msgs::Bool::ConstPtr &pFlag){if (this->emergency_stop_flag_){this->pause_flag_=true; return;}this->pause_flag_=pFlag->data; ROS_INFO_STREAM("FLAG");}
	public:
		float gtFrequencyParam(){return this->frequency_right_;}
		int gtEmergencyStopLevel(){return this->emergency_stop_severity_level_;}
		bool gtEmergencyStopFlag(){return this->emergency_stop_flag_;}
		bool gtPauseFlag(){return this->pause_flag_;}
};

int main(int argc,char** argv){
	ros::init(argc,argv,"right_fin_actuator_node");
    	//ros::NodeHandle nh;
    	//0.008
    	auto isRightActuator=true;
    	auto servoLowerLimit=10.0;
    	auto servoUpperLimit=170.0;
    	auto numberServos=10;
    	auto delayTime=0.01;
    	auto resolution=0.18;
    	auto winderRadius=0.009/2;
    	auto rayThickness=0.01925;
    	auto alphaLink=15.0;
    	auto frequency=0.0;
    	//65.0 and 115.0
	ActuatorMultiWave <2,double>actuator(isRightActuator,servoLowerLimit,servoUpperLimit,numberServos,delayTime,resolution,winderRadius,rayThickness,alphaLink,frequency);	
	actuator.setWaveArray();
	RightActuatorCommander commander;
	auto stopLevel = 1;
    	auto currentFrequency=frequency;
	while(ros::ok){
		ros::spinOnce();
		while(!commander.gtEmergencyStopFlag()){
			ros::spinOnce();
			if (commander.gtPauseFlag()){
				//pause always uses lowest image stopping method
				if (currentFrequency != 0.0){
					currentFrequency=0.0;
					actuator.emergencyStop(1);
					continue;	
				}
				continue;
			}
			if (abs(abs(currentFrequency) - abs(commander.gtFrequencyParam()))>0.05){
				currentFrequency=commander.gtFrequencyParam();
				actuator.setWaveArray(alphaLink,currentFrequency);
				actuator.waveServos();
				continue;
			}
			else{
				//difference in frequency is very small 
				if (currentFrequency!=0.0){
					actuator.waveServos();
				}
				continue;
			
			}
		}
		//check if already stopped
		if (currentFrequency!=0.0){
			stopLevel=commander.gtEmergencyStopLevel();
			
			if (stopLevel <3){
				currentFrequency=0.0;
				actuator.emergencyStop(stopLevel);
				continue;
			}

			else if (stopLevel==3){
				//hold emergency stop until emergencyStopFlag is reset
				actuator.emergencyStop(stopLevel);
				continue;
			}

		}
	}
	return 0;
}
