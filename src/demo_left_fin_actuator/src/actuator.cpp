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

int main(int argc,char** argv){
	ros::init(argc,argv,"demo_left_fin_actuator_node");
	ros::NodeHandle nh;
	bool setup;
	bool demo;
    	if (argc != 4){
		std::cout<<"incorrect number of input params "<<std::endl;
		return 1;
	}
	if (std::string(argv[1])=="Y"){
		setup = true;		
	}
	else{
		setup = false;
	}
	
	if (std::string(argv[2])=="Y"){
		demo = true;		
	}
	else{
		demo = false;
	}
	if(setup ^ demo != 1){
		std::cout<<"exclusive either demo or setup only"<<std::endl;
	}

	//ros::NodeHandle nh;
    	//0.008
        std::cout<<"running demo_left_fin_actuator"<<std::endl;
    	auto isRightActuator=false;
    	auto servoLowerLimit=10.0;
    	auto servoUpperLimit=170.0;
    	auto numberServos=10;
    	auto delayTime=0.01;
    	auto resolution=0.18;
    	auto winderRadius=0.009/2;
    	auto rayThickness=0.018;
    	auto alphaLink=15.0;
    	auto frequency=std::stof(argv[3]);
	if (frequency < -2.0 || frequency > 2.0){
		std::cout<<"invalid frequency parameter: "<<frequency<<std::endl;
	}
    	//65.0 and 115.0
	ActuatorMultiWave <10,double>actuator(isRightActuator,servoLowerLimit,servoUpperLimit,numberServos,delayTime,resolution,winderRadius,rayThickness,alphaLink,frequency);	
	actuator.setWaveArray();
	if (demo){
		while(ros::ok()){
        		actuator.waveServos();
        		actuator.waveServos();
        		actuator.waveServos();
        		actuator.waveServos();
                        actuator.waveServos();
                        actuator.waveServos();
			//actuator.emergencyStop(1);
		}
	}
	else if (setup){
		while(ros::ok()){
        		actuator.holdPosition(90.0);
		}	
	
	
	}
	return 0;
}
