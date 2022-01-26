/*
Filename: ActuatorMultiWave.h
Description: object that contains the important information for operating the stingray Servos. Operates using an 
array for each actuator
Author: Alex Cunningham alc5@hw.ac.uk
Start date: 01/12/2021
Last update: 02/12/2021
*/
#pragma once
#include <cmath>
#include "PCA9685.h"
#include "Servo.h"
#include <vector>
#include <array>
#include <unistd.h>
#include <ros/ros.h>
#include <std_msgs/String.h>
///Class that holds servo objects and important servo details
//TODO: check code for second stack of servos google "coding stacked PCA9685"
//TODO: add smooth transition between large frequency transitions
template<unsigned int N,typename T>
class ActuatorMultiWave {
    private:
    constexpr static unsigned int numServos=N;
    Servo servos[N];
    PCA9685 driver = PCA9685();
    double delayTime_;
    std::vector<std::vector<T>> waveVector;
    std::vector<T>emergencyStopVector;
    double resolution_;
    double winderRadius_;
    double rayThickness_;
    double alphaLink_;
    double frequency_; 
    int numberServos_;
    double libraryDelayTime_;
    std_msgs::String actuatorSide_;
    double servoLowerLimit_;
    double servoUpperLimit_;
    float pi = 3.14159265358979;
    public:
    ~ActuatorMultiWave(){
        setToSafePos();
	//for (auto servoIt = this->begin();servoIt!=this->end();++servoIt){
             // delete all servos
        //     delete servoIt;
         //    }
	
    }
    ActuatorMultiWave(bool isRightActuator,double servoLowerLimit,double servoUpperLimit,int numberServos,double delayTime,double resolution,double winderRadius,double rayThickness,double alphaLink,double frequency){
	 //if isRightActuator then right hand size address buses are used, this is for the bottom servo hat stack
	 if(isRightActuator){
	 	actuatorSide_.data="right";
	 }
	 else{
		actuatorSide_.data="left";
	 } 
	 ROS_INFO_STREAM("Actuator connected on " << this->actuatorSide_);
	    numberServos_ =numberServos;
        if (numberServos_%2!=0){
            ROS_ERROR_STREAM("number of servos must be an even number");
            ros::shutdown();
        }
         delayTime_=delayTime;
         waveVector=std::vector<std::vector<T>>();
         resolution_=resolution;
         winderRadius_=winderRadius;
         rayThickness_=rayThickness;
         alphaLink_=alphaLink;
         if ((frequency<-2.5) || (frequency > 2.5)){
            ROS_ERROR_STREAM("frequency "<<frequency<<"is not within boundary 0.1-2.5HZ");
            ros::shutdown();
         }
         frequency_=frequency;
         servoUpperLimit_=servoUpperLimit;
         servoLowerLimit_=servoLowerLimit;
         //TODO: determine hardware delay time
         libraryDelayTime_=0.0;
         if (delayTime_<libraryDelayTime_){
            ROS_ERROR_STREAM("specified delay time is shorter than library delay time, hence making it unachievable");
		    ros::shutdown();
        }
	 //set driver and memory locations
	 //right actuator is connected to the bottom servo hat 
	 if (isRightActuator){
		driver.init(1,0x41);
		driver.setPWMFreq(60);
		ROS_INFO_STREAM("initialized right actuator driver");
	 }
	 else{
	 	driver.init(1,0x40);
		driver.setPWMFreq(60);
		ROS_INFO_STREAM("initialized left actuator driver");

	 }	 
	 int channelIterator=0;
     ROS_INFO_STREAM("initializing servos");    
     for (auto servoIt = this->begin();servoIt!=this->end();++servoIt){
             // Attach the servos
	     ROS_INFO_STREAM("initializing servos");
	     //servoIt=new Servo(channelIterator,&driver,65,115);
	     *servoIt=Servo(channelIterator,&driver,servoLowerLimit_,servoUpperLimit_); //78,102
	     ROS_INFO_STREAM("initialized servo "<<(servoIt-this->begin())/2);
;
             channelIterator++;
	     if (channelIterator > 15){
	     	ROS_ERROR_STREAM("Channels do not exist past 16 eeek");
		ros::shutdown();
	     }
             }
        ROS_INFO_STREAM("All servos initialized");
        //set emergency stop waveVector
        //default direction is for a f is +ve
        //create triangle with max angle at leading edge (direction dependent)
        //y=mx+c with between max and min height
        ROS_INFO_STREAM("initializing emergency stop wave");
        if (numberServos_==2){
            double alphaLinkIterator = (pi/180.00)*(15.0);
            double deltaL=4*this->rayThickness_/2*sin(alphaLinkIterator/2);
            double servoAngle=90.0+((deltaL/(this->winderRadius_))*180.00/pi);
            ROS_INFO_STREAM("emergencyStopVector initialized for single actuator with  angle" <<servoAngle);
            emergencyStopVector.push_back(servoAngle);
            ROS_INFO_STREAM("ActuatorMultiWave object initialized");
            return; 
        }
        float m = (-15.0-15.0)/((numberServos_/2)-1);
        float c = 15.0;
        bool waveError=false;
        for (auto servoIterator=0;servoIterator!=this->numberServos_/2;servoIterator++){
            double alphaLinkIterator = (pi/180.00)*(m*servoIterator+c);
            if(!std::isfinite(alphaLinkIterator)){
                ROS_ERROR_STREAM("Error: non-finite input for alphaLinkIterator  "<<alphaLinkIterator);
                waveError=true;
                break;
                }
            double deltaL=4*this->rayThickness_/2*sin(alphaLinkIterator/2);
            if(!std::isfinite(deltaL)){
                ROS_ERROR_STREAM("Error: non-finite input for deltaL "<<deltaL);
                waveError=true;
                break;
                }
            double servoAngle=90.0+((deltaL/(this->winderRadius_))*180.00/pi);
            emergencyStopVector.push_back(servoAngle);
            ROS_INFO_STREAM("EMERGENCY STOP VECTOR: "<<servoAngle);
        }
        ROS_INFO_STREAM("ActuatorMultiWave object initialized");
         }

    // update servoWaveVector alpha(t)=Asin(2pift)
    int setWaveArray(int alphaLink,float frequency) {
        //if actuators already producing wave provided then return 
        if (this->alphaLink_ == alphaLink && this->frequency_ ==frequency){
            setWaveArray();
        }
        else{
        this->alphaLink_=alphaLink;
        this->frequency_=frequency;
        //contains same logic as setWaveArray() with noargs 
        return(setWaveArray());
        }
    }
    
    //update servoWaveVector alpha(t)=Asin(2pift) if no args passed set to pos given by member variables
    int setWaveArray() {
        //contains same logic as setWaveArray() with noargs 
        //float pi = 3.14159265358979;
        if (this->frequency_==0.0){
		return 0;
	}
	ROS_INFO_STREAM("setWaveArray()");
        auto tmpWaveContainer=std::vector<T>();
        bool waveError=false;
        double tIterator = 0;
        double phaseDif=this->frequency_*2*pi/(this->numberServos_/2);
        for(auto servoIterator=0;servoIterator!=this->numberServos_/2;servoIterator++){
            while (tIterator < 1/(abs(this->frequency_))){
                double alphaLinkIterator = (pi/180.00)*(this->alphaLink_)*sin((this->frequency_*2*pi*tIterator)+(phaseDif*servoIterator));
                if(!std::isfinite(alphaLinkIterator)){
                    ROS_ERROR_STREAM("Error: non-finite input for alphaLinkIterator  "<<alphaLinkIterator);
                    waveError=true;
                    break;
                }
                ROS_INFO_STREAM("alphaLinkIterator"<<alphaLinkIterator);
                double deltaL=4*this->rayThickness_/2*sin(alphaLinkIterator/2);
                if(!std::isfinite(deltaL)){
                    ROS_ERROR_STREAM("Error: non-finite input for deltaL "<<deltaL);
                    waveError=true;
                    break;
                }
                ROS_INFO_STREAM("deltaL: "<<deltaL);
                double servoAngle=90.0+((deltaL/(this->winderRadius_))*180.00/pi);
                ROS_INFO_STREAM("angle: " <<servoAngle);
                //check value is within limits
                if(!std::isfinite(servoAngle)){
                    ROS_ERROR_STREAM("Error: non-finite input for servoAngle "<<servoAngle);
                    waveError=true;
                    break;
                }
                if(servoAngle<servoLowerLimit_){
                    ROS_ERROR_STREAM("Error: servoAngle lower than servoLowerLimit "<<servoAngle<<" < "<<servoLowerLimit_);
                    waveError=true;
                    break;
                }
                if(servoAngle>servoUpperLimit_){
                    ROS_ERROR_STREAM("Error: servoAngle higher than servoUpperLimit "<<servoAngle<<" > "<<servoUpperLimit_);
                    waveError=true;
                    break;
                }
                tmpWaveContainer.push_back(servoAngle); //based on a 90 degree neutral position
                //TODO: this is currently 0, and doesn't take into account the hardware delay time
                tIterator = tIterator+this->delayTime_+this->libraryDelayTime_;
            }
            if (waveError){
                //if error then make all 90 degree positions and inform
                ROS_ERROR_STREAM("Error: setting all positions to 90 degrees - check your inputs");
                waveVector=std::vector<std::vector<T>>(int(numberServos_/2),std::vector<T>(int(abs(1/this->frequency_)),90.0));
                break;
                return 1;
            }
            //ROS_INFO_STREAM("tmpWaveContainerSize"<<tmpWaveContainer.size());
            waveVector.push_back(tmpWaveContainer);
            tmpWaveContainer.clear();
            tIterator=0;
        }
    return 0;
    }
 
    void emergencyStop(int stopMode){
        /*
         * Perform emergency stop, depending on the severity of the situation you might want to stop in a different way: this is determined by the stopMode Flag 
         * H=high=3 (stop ASAP),M=medium=2 (need to stop soon but don't want to put lots of stress on the system),L=low=1 (plenty of time to stop no need to rush)
	    *  ROS_ERROR_STREAM("Emergency stop using severity mode: "<<stopMode);
	    */    
        switch(stopMode){
            case 1:
            {
                //decrease the amplitude and frequency of the wave based on logarithm
                //decrease wave until 0.5hz and 5 degrees alphalink
                //the time for this decrease is taken as a 10% per period of the current wave 
                //std::vector<std::vector<T>> dampedWaveVector;
                std::vector<std::vector<std::vector<T>>> dampedWaveVector;
                //goals must be > 0
                //TODO: set a decrease increment thresholdhold (resolution min based)
                double alphaLinkGoal=2;
                double fGoal=0.2;
                double fZeta=log(fGoal/this->frequency_)/(1/this->frequency_);
                //ROS_INFO_STREAM("FZETA IS:"<<fZeta);
                double alphaLinkZeta=log(alphaLinkGoal/this->alphaLink_)/(1/this->frequency_);
                //ROS_INFO_STREAM("ALPHA ZETA IS:"<<alphaLinkZeta);
                auto fDampedFunc = [&](double tIt)->double{
                     return (this->frequency_*exp(fZeta*tIt));
                };
                auto alphaLinkDampedFunc=[&](double tIt)->double{
                    return (this->alphaLink_*exp(alphaLinkZeta*tIt)); 
                };
                auto phaseDifDampedFunc=[&](double tIt)->double{
                    return(fDampedFunc(tIt)*2*pi/(this->numberServos_/2));
                };
                auto tmpWaveContainer=std::vector<T>();
                auto tmpWaveContainer2D=std::vector<std::vector<T>>();
                bool waveError=false;
                double tIterator = 0;
                bool adjustWaveForm=true;
                double tIteratorAdjustWaveForm=0.0;
                double tIteratorAdjustWaveFormSteps=abs(1/this->frequency_)/10.0;
                //tIterator less than goal location time e.g denominator of zeta 
                //double phaseDif=this->frequency_*2*pi/(this->numberServos_/2);
                    for(auto servoIterator=0;servoIterator!=this->numberServos_/2;servoIterator++){
                        while(tIteratorAdjustWaveForm<abs(1/this->frequency_)){
                            tIteratorAdjustWaveForm+=tIteratorAdjustWaveFormSteps;
                            double alphaLinkDamped = alphaLinkDampedFunc(tIteratorAdjustWaveForm);
                            double phaseDifDamped=phaseDifDampedFunc(tIteratorAdjustWaveForm);
                            double fDamped=fDampedFunc(tIteratorAdjustWaveForm);
                            ROS_INFO_STREAM("ALPHALINK DAMPED "<<alphaLinkDamped);
                            ROS_INFO_STREAM("PHASEDIF DAMPED "<<phaseDifDamped);
                            ROS_INFO_STREAM("FDAMPED "<<fDamped);
                            
                        while (tIterator < 1/(abs(this->frequency_))){ 
                            double alphaLinkIterator = (pi/180.00)*(alphaLinkDamped)*sin((fDamped*2*pi*tIterator)+(phaseDifDamped*servoIterator));
                            if(!std::isfinite(alphaLinkIterator)){
                    ROS_ERROR_STREAM("Error: non-finite input for alphaLinkIterator  "<<alphaLinkIterator);
                                waveError=true;
                                break;
                            }

                            //ROS_INFO_STREAM("alphaLinkIterator"<<alphaLinkIterator);
                            
                            double deltaL=4*this->rayThickness_/2*sin(alphaLinkIterator/2);
                            if(!std::isfinite(deltaL)){
                                ROS_ERROR_STREAM("Error: non-finite input for deltaL "<<deltaL);
                                waveError=true;
                                break;
                            }
                            //ROS_INFO_STREAM("deltaL: "<<deltaL);
                            double servoAngle=90.0+((deltaL/(this->winderRadius_))*180.00/pi);
                            //ROS_INFO_STREAM("angle: " <<servoAngle);
                            //check value is within limits
                            if(!std::isfinite(servoAngle)){
                                ROS_ERROR_STREAM("Error: non-finite input for servoAngle "<<servoAngle);
                                waveError=true;
                                break;
                            }
                            if(servoAngle<servoLowerLimit_){
                                ROS_ERROR_STREAM("Error: servoAngle lower than servoLowerLimit "<<servoAngle<<" < "<<servoLowerLimit_);
                                waveError=true;
                                break;
                            }
                            if(servoAngle>servoUpperLimit_){
                                ROS_ERROR_STREAM("Error: servoAngle higher than servoUpperLimit "<<servoAngle<<" > "<<servoUpperLimit_);
                                waveError=true;
                                break;
                            }
                            tmpWaveContainer.push_back(servoAngle);
                            //TODO: doesn't take into account the hardware delay time
                            tIterator = tIterator+this->delayTime_+this->libraryDelayTime_;
                        }
                        tmpWaveContainer2D.push_back(tmpWaveContainer);
                        tmpWaveContainer.clear();
                        tIterator=0.0;
                    if (waveError){
                    //if error then make all 90 degree positions and inform
                        ROS_ERROR_STREAM("Error: setting all positions to 90 for dampedWaveVector degrees - check your inputs");
                        //do something like that here
                        //waveVector=std::vector<std::vector<T>>(int(numberServos_/2),std::vector<T>(int(abs(1/this->frequency_)),90.0));
                        break;
                        return;
                    }
                    }
                    //ROS_INFO_STREAM("damped frequency wave size"<<tmpWaveContainer.size());
                    dampedWaveVector.push_back(tmpWaveContainer2D);
                    tmpWaveContainer2D.clear();
                    tIteratorAdjustWaveForm=0.0;
                }
                //iterate through wave
                if (frequency_>0){
                    //delay time is slightly different here -> equal to period/delayTime
                    for(int waveIndexDim1=0;waveIndexDim1!=dampedWaveVector[0].size();waveIndexDim1++){
                        for (int waveIndexDim2=0;waveIndexDim2!=dampedWaveVector[0][0].size();waveIndexDim2++){
                            for (auto actuatorIterator=this->begin();actuatorIterator!=this->end();actuatorIterator++){
                                int actuatorPos=(actuatorIterator-this->begin())/2;
                                actuatorIterator->setAngle(dampedWaveVector[actuatorPos][waveIndexDim1][waveIndexDim2]);
                                actuatorIterator++;
                                actuatorIterator->setAngle(dampedWaveVector[actuatorPos][waveIndexDim1][waveIndexDim2]);
                                }
                            ros::Duration(this->delayTime_).sleep();
                            }
                        }
                    }
                else{
                    //delay time is slightly different here -> equal to period/delayTime
                    for(int waveIndexDim1=0;waveIndexDim1!=dampedWaveVector[0].size();waveIndexDim1++){
                        for (int waveIndexDim2=0;waveIndexDim2!=dampedWaveVector[0][0].size();waveIndexDim2++){
                            for (auto actuatorIterator=this->begin();actuatorIterator!=this->end();actuatorIterator++){
                                int actuatorPos=(actuatorIterator-this->begin())/2;
                                actuatorIterator->setAngle(90.0-(dampedWaveVector[actuatorPos][waveIndexDim1][waveIndexDim2]-90.0));
                                actuatorIterator++;
                                actuatorIterator->setAngle(90.0-(dampedWaveVector[actuatorPos][waveIndexDim1][waveIndexDim2]-90.0));
                                }
                            ros::Duration(this->delayTime_).sleep();
                            }
                        }

                }
                ros::Duration(this->delayTime_).sleep();  
                break;
            }
            case 2:
                //stop wave in its start position which should avoid jerking behaviour
                for (auto actuatorIterator = this->begin();actuatorIterator!=this->end();actuatorIterator++){
                    int actuatorPos=(actuatorIterator-this->begin())/2;
                    actuatorIterator->setAngle(waveVector[actuatorPos][0]);
                    actuatorIterator++;
                    actuatorIterator->setAngle(waveVector[actuatorPos][0]);
                }
                //add a small delay time
                ros::Duration(this->delayTime_).sleep();
                break;
            case 3:
                //create a barrier with the actuator - leading edge at max angle
                if (frequency_>0){
                    for (auto actuatorIterator=this->begin();actuatorIterator!=this->end();actuatorIterator++){
                    int actuatorPos=(actuatorIterator-this->begin())/2;
                    float pos= emergencyStopVector[actuatorPos];
                    actuatorIterator->setAngle(pos);
                    actuatorIterator++;
                    actuatorIterator->setAngle(pos);
                    }
                }
                else{
                    //we are moving backwards 
                    for (auto actuatorIterator=this->begin();actuatorIterator!=this->end();actuatorIterator++){
                    int actuatorPos=(actuatorIterator-this->begin())/2;
                    float pos= 90.0-(emergencyStopVector[actuatorPos]-90.0);
                    actuatorIterator->setAngle(pos);
                    actuatorIterator++;
                    actuatorIterator->setAngle(pos);
                    }
                }
                ros::Duration(this->delayTime_).sleep();                        
                break;
		}
	}
    //setServosToSafePosition - used within destructor
    
    void setToSafePos(){
        for (auto servoIt = this->begin();servoIt!=this->end();servoIt++){
            //lowest torque requirements
            servoIt->setAngle(90);
            }
        return;
    }

    void holdPosition(float angle){
        for (auto actuatorIterator=this->begin();actuatorIterator!=this->end();actuatorIterator++){
            int actuatorPos=(actuatorIterator-this->begin())/2;
            actuatorIterator->setAngle(angle);
            actuatorIterator++;
            actuatorIterator->setAngle(angle);
        }
        //add a small delay time
        ros::Duration(this->delayTime_).sleep();
    }

    void waveServos(){
        //waveVector[0] is not possible if the matrix is square
	if (this->frequency_==0){
		ROS_INFO_STREAM("Frequency is zero");
		return;
	}
        for (int waveIndex=0;waveIndex!=waveVector[0].size();waveIndex++){
            for (auto actuatorIterator=this->begin();actuatorIterator!=this->end();actuatorIterator++){
                int actuatorPos=(actuatorIterator-this->begin())/2;
                actuatorIterator->setAngle(waveVector[actuatorPos][waveIndex]);
                actuatorIterator++;
		        //now move the bottom servo; setup is tip to tail (+ve torque is anticlockwise for top servo and the opposite for the bottom servo)
                actuatorIterator->setAngle(waveVector[actuatorPos][waveIndex]);
            }
            ros::Duration(this->delayTime_).sleep();
        }
    }

    void waveServosInverted(){
        //waveVector[0] is not possible if the matrix is square
        for (int waveIndex=0;waveIndex!=waveVector[0].size();waveIndex++){
            for (auto actuatorIterator=this->begin();actuatorIterator!=this->end();actuatorIterator++){
                int actuatorPos=(actuatorIterator-this->begin())/2;
                actuatorIterator->setAngle(90.0-(waveVector[actuatorPos][waveIndex]-90.0));
                actuatorIterator++;
		        //now move the bottom servo; setup is tip to tail (+ve torque is anticlockwise for top servo and the opposite for the bottom servo)
                actuatorIterator->setAngle(90.0-(waveVector[actuatorPos][waveIndex]-90.0));
            }
            ros::Duration(this->delayTime_).sleep();
        }
    }

    void waveServosReverseOrder(){
        //iterate over the wave in reverse order
        for (int waveIndex=waveVector[0].size()-1;waveIndex!=-1;waveIndex--){
            for (auto actuatorIterator=this->end()-1;actuatorIterator!=this->begin()-1;actuatorIterator--){
                int actuatorPos=(actuatorIterator-this->begin())/2;
                actuatorIterator->setAngle(waveVector[actuatorPos][waveIndex]);
                actuatorIterator--;
		        //now move the bottom servo; setup is tip to tail (+ve torque is anticlockwise for top servo and the opposite for the bottom servo)
                actuatorIterator->setAngle(waveVector[actuatorPos][waveIndex]);
                //begin iterator dealt with so good to cancel for loop 
            }
            ros::Duration(this->delayTime_).sleep();
        } 
    }
    ///access element servo n
    ///@return Servo&
    Servo& operator[](unsigned int n) {return servos[n];}
    ///access element servo n
    ///@return Servo& 
    const Servo& operator[](unsigned int n) const {return servos[n];}
    using iterator = Servo*;

    ///get first servo
    ///@return iterator to start of servos
    iterator begin() {return &servos[0];}
    
    //get last servo
    ///@return iterator to end of servos
    iterator end() {return &servos[N];}
};
