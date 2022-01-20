#!/usr/bin/env python
import rospy
from bmp180.bmp180 import bmp180
from grovejetson.grovejetson import grovejetson
from std_msgs.msg import Bool,Float32
class PySensors():
    def __init__(self,grovepin = 40, bmpaddress=0x77):
        self.bmp_ = bmp180(bmpaddress)
        self.grove_=grovejetson(grovepin)
        self.grove_pub_=rospy.Publisher("stingray/pysensors/grove_is_dry",Bool,queue_size=1)
        self.bmp_pressure_pub_=rospy.Publisher("stingray/pysensors/pressure",Float32,queue_size=1)
        self.bmp_temp_pub_=rospy.Publisher("stingray/pysensors/temperature",Float32,queue_size=1)
        #msgs
        self.pressure_=Float32()
        self.temperature_=Float32()
        # dry = true, wet = false
        self.is_dry_ = Bool()
    
    def setMsgs(self):
        self.pressure_.data = self.bmp_.get_pressure()
        self.temperature_.data = self.bmp_.get_temp()
        self.is_dry_.data = bool(self.grove_.value)
    
    def publish(self):
        self.grove_pub_.publish(self.is_dry_)
        self.bmp_temp_pub_.publish(self.temperature_)
        self.bmp_pressure_pub_.publish(self.pressure_)

if __name__=="__main__":
    rospy.init_node("pysensors_node")
    pysensors  = PySensors()
    pysensors.setMsgs()
    pysensors.publish()
    r = rospy.Rate(100)
    while not rospy.is_shutdown():
        pysensors.setMsgs()
        pysensors.publish()
        r.sleep()
        
