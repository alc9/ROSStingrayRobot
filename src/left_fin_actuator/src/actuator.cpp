/*
 * Filename: actuator.cpp
 * Description: this code controls the left actuators 
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
class LeftActuatorCommander{
	protected:
		ros::NodeHandle nh_;
		ros::Subscriber gt_frequency_params_sub_;
		ros::Subscriber gt_emergency_stop_severity_level_sub_;
		ros::Subscriber gt_emergency_stop_flag_sub_;
		ros::Subscriber gt_pause_flag_sub_;
		float frequency_left_;
		bool emergency_stop_flag_;
		//this is received from action server
		bool pause_flag_;
		int emergency_stop_severity_level_;
	public: 
		LeftActuatorCommander(){
			initializeSubscribers();
			emergency_stop_flag_=false;
			pause_flag_=true;
			emergency_stop_severity_level_=1;

			ROS_INFO_STREAM("left_fin_actuator initialized");
		}
	
	private:
		void initializeSubscribers(void){
			gt_frequency_params_sub_=nh_.subscriber("/stingray/control/frequency",&LeftActuatorCommander::subscriberFrequencyCb,this);
			gt_emergency_stop_severity_level_sub_=nh_.subscriber("/stingray/control/emergency_stop_level",&LeftActuatorCommander::subscriberEmergencyStopLevelCb,this);
			gt_emergency_stop_flag_sub_=nh_.subscriber("/stingray/control/emergency_stop_flag",&LeftActuatorCommander::subscriberEmergencyStopFlagCb,this);
			gt_pause_flag_sub_=nh_.subscriber("/stingray/control/pause_flag",&LeftActuatorCommand::subscriberPauseFlagCb,this);
		}

		void subscriberFrequencyCb(const std_msgs::Float32::ConstPtr &f){frequency_left_ = f->data;}
		void subscriberEmergencyStopLevelCb(const std_msgs::Int8::Constptr &level){emergency_stop_level_severity_=level->data;}
		void subscriberEmergencyStopFlagCb(const std_msgs::Bool::ConstPtr &sFlag){emergency_stop_flag_=sFlag->data;}
		void subscriberPauseFlagCb(const std_msgs::Bool::ConstPtr &pFlag){emergency_pause_flag_=pFlag->data;}
	public:
		float gtFrequencyParam(){return frequency_left_;}
		int gtEmergencyStopLevel(){return emergency_stop_severity_level_;}
		bool gtEmergencyStopFlag(){return emergency_stop_flag_;}
		bool gtPauseFlag(){return pause_flag_;}
};

int main(int argc,char** argv){
	ros::init(argc,argv,"left_fin_actuator_node");
    	//ros::NodeHandle nh;
    	//0.008
    	auto isRightActuator=false;
    	auto servoLowerLimit=50.0;
    	auto servoUpperLimit=150.0;
    	auto numberServos=2;
    	auto delayTime=0.01;
    	auto resolution=0.18;
    	auto winderRadius=0.006/2;
    	auto rayThickness=0.008;
    	auto alphaLink=15.0;
    	auto frequency=1.0;
    	//65.0 and 115.0
	ActuatorMultiWave <2,double>actuator(isRightActuator,servoLowerLimit,servoUpperLimit,numberServos,delayTime,resolution,winderRadius,rayThickness,alphaLink,frequency);	
	actuator.setWaveArray();
	//actuator.holdPosition(90.0);
    	auto currentFrequency=frequency;
	while(ros::ok){
		while(!actuator.gtEmergencyStopFlag()){
			if (actuator.gtPauseFlag()){
				//pause always uses lowest image stopping method
				if (currentFrequency != 0.0){
					currentFrequency=0.0;
					actuator.emergencyStop(1);	
				}
				continue;
			}
			if (abs(currentFrequency - actuator.gtFrequencyParam())>0.05){
				currentFrequency=actuator.gtFrequencyParam();
				actuator.waveServos(alphaLink,currentFrequency);
			}
			else{
				//difference in frequency is very small 
				actuator.waveServos();
			
			}
		}
		//check if already stopped
		if (currentFrequency!=0.0){
			stopLevel=actuator.gtEmergencyStopLevel();
			
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

			else{
				ROS_INFO_STREAM("Invalid input parameter");
			}
		}
	}
	return 0;
}
