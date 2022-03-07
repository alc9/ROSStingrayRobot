#!/usr/bin/env python
import rospy
from std_msgs.msg import Bool,Float32
import time
import busio
import board
import adafruit_ina260
class InaSensor():
    def __init__(self):
        self.i2c_=busio.I2C(board.SCL,board.SDA)
        self.ina_=adafruit_ina260.INA260(self.i2c_,address=0x45)
        self.ina_power_pub_=rospy.Publisher("stingray/pysensors/power",Float32,queue_size=1)
        self.servo_power_=Float32()
    def setMsgs(self):
        self.servo_power_.data=self.ina_.power
    def publish(self):
        self.ina_power_pub_.publish(self.servo_power_)
if __name__=="__main__":
    rospy.init_node("ina_node")
    pysensors  = InaSensor()
    pysensors.setMsgs()
    pysensors.publish()
    r = rospy.Rate(100)
    while not rospy.is_shutdown():
        pysensors.setMsgs()
        pysensors.publish()
        r.sleep()
 
