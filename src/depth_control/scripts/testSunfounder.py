#!/usr/bin/env python
import rospy
from std_msgs.msg import Float32
from std_msgs.msg import Bool
from SunFounder_PCA9685.Servo import Servo
noseServo=Servo(1,address=0x41,bus_number=1)
noseServo.setup()
noseServo.write(90.0)
import numpy as np
def test(a):
	'''Servo driver test on channel 1'''
	import time
	for i in range(0, 180, 5):
		print(i)
		a.write(i)
		time.sleep(0.1)
	for i in range(180, 0, -5):
		print(i)
		a.write(i)
		time.sleep(0.1)
	for i in range(0, 91, 2):
		a.write(i)
		time.sleep(0.05)
	print(i)
def testb(s):
    import time
    data = np.arange(-27,27.5,0.5).tolist()
    posList=[]
    start = time.time()
    print(data)
    for d in data:
        angle = 90.0 + (90.0/27.0) * d
        posList.append(angle)
    while time.time()-start < 10:
        print("forward")
        for p in posList:
            print(p)
            s.write(p)
            time.sleep(0.08)
        print("reversed")
        for p in reversed(posList):
            print(p)
            s.write(p)
            time.sleep(0.08)
testb(noseServo)
print("resetting to 90 degrees")
noseServo.write(90.0)
"""
Third PCA9685 driver in the system which should allow for easy power delivery and higher quality waves
"""
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
"""    
