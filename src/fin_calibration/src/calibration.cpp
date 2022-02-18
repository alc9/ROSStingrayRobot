#include <ros/ros.h>
#include <conio.h>
#include <iostream>
#include <vector>
#include <string>
#include "Servo.h"
#include "PCA9685.h"
#include <boost/filesystem.hpp>
#include <fstream>
#include <sstream>
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
using namespace boost::filesystem;
template<unsigned int N>
class Calibration{
    private:
        Servo servos[N];
        PCA9685 driver_=PCA9685();
        std::string path_;
        std::vector<std::vector<int>> mappedIndices_;
        bool isRightActuator_;
        int rayIndex_;
        float angleLimits_;
        float increment_;
        double servoLowerLimit_;
        double servoUpperLimit_;
        std::vector<float> calibrations_;
    public: 
        Calibration(bool isRightActuator,double servoLowerLimit,double servoUpperLimit){
            servoLowerLimit_=servoLowerLimit;
            servoUpperLimit_=servoUpperLimit;
            increment_=0.05;
            isRightActuator_ = isRightActuator;
            mappedIndices_ = {{0,1},{2,3},{4,5},{6,7},{8,9}};
            if (isRightActuator_){
                std::cout<<"calibrating right fin"<<std::endl;
                path_=std::string("/home/stingray/stingray_ws/src/fin_calibration/src/calibration/calibrationRight.csv");
            }
            else{
                std::cout<<"calibrating left fin"<<std::endl;
                path_=std::string("/home/stingray/stingray_ws/src/fin_calibration/src/calibration/calibrationLeft.csv");
            }
            this->updateCalibrationVector();
            angleLimits_=80.0;
            rayIndex_=0;
            
            if (isRightActuator){
		driver_.init(1,0x41);
		driver_.setPWMFreq(60);
		ROS_INFO_STREAM("initialized right actuator driver");
	 }
	 else{
	 	driver_.init(1,0x40);
		driver_.setPWMFreq(60);
		ROS_INFO_STREAM("initialized left actuator driver");
        }
        
        int channelIterator=0;
        for (auto servoIt = this->begin();servoIt!=this->end();++servoIt){
	     *servoIt=Servo(channelIterator,&driver_,servoLowerLimit_,servoUpperLimit_); //78,102
             channelIterator++;
	     if (channelIterator > 15){
	        std::cout<<"out of channel range"<<std::endl;
             }
        }

    }
        void updateCalibrationVector(){
            auto readFileIntoString=[](const std::string& path)->std::string{
			auto ss = std::ostringstream{};
			std::ifstream input_file(path);
			if (!input_file.is_open()){
				ROS_INFO_STREAM("File is open or does not exist");
				ros::shutdown();
			}
			ss<<input_file.rdbuf();
			return ss.str();
		};
            try{
			if (!boost::filesystem::exists(path_)){
				ROS_INFO_STREAM("path to goalPosition does not exist...");
				ROS_INFO_STREAM("current path"<<boost::filesystem::current_path());
				ros::shutdown();
			}
			if (boost::filesystem::path(path_).extension()!=".csv"){
				ROS_INFO_STREAM("File extension should be .csv");
				ros::shutdown();
			}
		} catch(const boost::filesystem::filesystem_error& e){
			std::cerr<<std::endl<<"Error:" << e.what() << std::endl;
			ros::shutdown();
		} catch(const std::exception& e){
			std::cerr<<std::endl<<"Error: " << e.what()<<std::endl;
			ros::shutdown();
		}

	    std::string configString=readFileIntoString(path_); 
            std::stringstream ss(configString);
            for (float i;ss>>i;){
                calibrations_.push_back(i);
                if (ss.peek()==','){
                ss.ignore();
                }
            }
 

        }

        void updateCalibrationFile(){
            std::string infoString;
            for(auto calibrationsIterator=calibrations_.begin();calibrationsIterator!=calibrations_.end();calibrationsIterator++){
		infoString.append(std::to_string(*calibrationsIterator));
	       	infoString.append(",");
            }
	    std::ofstream out(path_);
	    out << infoString;
	    out.close();
        }
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
    
    void setRayIndex(bool right){
        //to the right
        if (right){
            if (rayIndex_+1 < 4){
            rayIndex_++;
        }
            else{
                std::cout<<"ray index out of range"<<std::endl;
            }
        }
        //otherwise to the left
        else{
            if (rayIndex_-1 > 0){
                rayIndex_--;
            }
            else{
                std::cout<<"ray index out of range"<<std::endl;
            }
        }
    }

    void setCalibration(bool up){
        if (up){
            if (calibrations_[rayIndex_]+increment_ < 90.0+angleLimits_){
            calibrations_[rayIndex_]=calibrations_[rayIndex_]+angleLimits_;
            }
            else{
                std::cout<<"angle out of range"<<std::endl;
            }
        }
        else{
            if (calibrations_[rayIndex_]+increment_ > 90.0-angleLimits_){
            calibrations_[rayIndex_]=calibrations_[rayIndex_]-angleLimits_;
            }
            else{
                std::cout<<"angle out of range"<<std::endl;
            }
        }
    }
    
    void printCalibration(){
        for (auto calibIterator = calibrations_.begin(); calibIterator!=calibrations_.end(); calibIterator++){
            std::cout<<*calibIterator;
        }
        std::cout<<std::endl;
    }

    void setIncrement(){
        float increment;
        std::cin >> increment;
        if (std::cin.fail()){
        std::cout<<"input must be a float"<<std::endl;
        std::cin.clear();
        return;
        }
        std::cin.clear();
       if ((0.1 <=increment) || (increment>=2.0)){
            std::cout<<"increment not within bounds 0.1 and 2.0"<<std::endl;
            return;
       }
       increment_=increment; 
    }

    void moveServos(){
        //TODO: remember delay time
        servos[mappedIndices_[rayIndex_][0]].setAngle(calibrations_[rayIndex_]); 
        servos[mappedIndices_[rayIndex_][1]].setAngle(calibrations_[rayIndex_]);
    }
};

int main(int argc, char** argv){
    //if "Y" is right actuator
    ros::init(argc,argv,"calibration_node");
    auto lower = 15.0;
    auto upper = 165.0;
    bool isRightActuator;
    if ((argc==2) && (std::string(argv[1])=="Y")){
        isRightActuator = std::string(argv[1])=="Y"?true:false;
    }
    else{
        std::cout<<"invalid command line argument"<<std::endl;
        return 1;
    }
    Calibration <10> calibrator(isRightActuator,lower,upper); 
    int c = 0;
    bool calibrate = true;
    while(calibrate)
    {
        c = 0;

        switch((c=getch())) {
        case KEY_UP:
            std::cout << std::endl << "Up" << std::endl;//key up
            calibrator.setCalibration(true);
            calibrator.updateCalibrationFile();
            calibrator.updateCalibrationVector(); 
            calibrator.moveServos();
            break;
        case KEY_DOWN:
            std::cout << std::endl << "Down" << std::endl;   // key down
            calibrator.setCalibration(false);
            calibrator.updateCalibrationFile();
            calibrator.updateCalibrationVector();
            calibrator.moveServos();
            break;
        case KEY_LEFT:
            std::cout << std::endl << "Left" << std::endl;  // key left
            calibrator.setRayIndex(true);
            break;
        case KEY_RIGHT:
            std::cout << std::endl << "Right" << std::endl;  // key right
            calibrator.setRayIndex(true);
            break;
        case 'i':
            std::cout << std::endl << "increment" << std::endl;
            calibrator.setIncrement();
            break;
        case 'q':
            std::cout<<std::endl<< "calibration done" << std::endl;
            calibrator.printCalibration();
            calibrate = false;
            break;
        default:
            std::cout << std::endl << "null" << std::endl;  // not arrow
            break;
        }

    }

    return 0;
}
