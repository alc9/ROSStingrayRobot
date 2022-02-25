#!/usr/bin/env python
import rospy
from std_msgs.msg import Float32
from std_msgs.msg import Bool
from SunFounder_PCA9685.Servo import Servo
"""
Third PCA9685 driver in the system which should allow for easy power delivery and higher quality waves
"""
class DepthController():
    def __init__(self):
        self.nose_angle_=90.0
        #TODO: solder pin for 0x42
        self.nose_servo_=Servo(1,address=0x42)
        self.pause_flag_=False
        self.nose_sub_=rospy.Subscriber("stingray/control/nose_angle",Float32,callback=self.noseSubCb,queue_size=1)
        self.pause_flag_sub_=rospy.Subscriber("stingray/control/pause_flag",Bool,callback=self.pauseFlagSubCb,queue_size=1)
    
    def noseSubCb(self,data):
        data = data.data
        if data > 26.0 or data < -26.0:
            print("Error nose angle out of range: ",data)
            return
        #convert nose angle to servo angle
        self.nose_angle_=90.0+((90.0//26.0)*data)

    def pauseFlagSubCb(self,data):
        self.pause_flag_=data.data
    
    def getPauseFlag(self):
        return pause_flag_
    
    def actuate(self):
        servo.write(self.nose_angle_)
def main():
    rospy.init_node("depth_controller_node")
    depthController=depthController()
    while depthController.getPauseFlag() is False and not rospy.is_shutdown():
        rospy.spin()
        depthController.actuate()
    print("depth_controller shutting down")

if __name__=="__main__":
    main()
