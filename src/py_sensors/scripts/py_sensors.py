#!/usr/bin/env python
import rospy
from bmp180.bmp180 import bmp180
from grovejetson.grovejetson import grovejetson
from std_msgs.msg import Bool,Float32
from jtop import jtop
# old 0x77 
class PySensors():
    def __init__(self,grovepin = 40, bmpaddress=0x77):
        self.bmp_ = bmp180(bmpaddress)
        self.grove_=grovejetson(grovepin)

        self.grove_pub_=rospy.Publisher("stingray/pysensors/grove_is_dry",Bool,queue_size=1)
        self.bmp_pressure_pub_=rospy.Publisher("stingray/pysensors/pressure",Float32,queue_size=1)
        self.bmp_temp_pub_=rospy.Publisher("stingray/pysensors/temperature",Float32,queue_size=1)
        self.ram_pub_=rospy.Publisher("stingray/pysensors/RAM",Float32,queue_size=1)
        self.gpu_pub_=rospy.Publisher("stingray/pysensors/GPU",Float32,queue_size=1)
        self.jetson_power_pub_=rospy.Publisher("stingray/pysensors/jetson_power",Float32,queue_size=1)
        self.gpu_temp_pub_=rospy.Publisher("stingray/pysensors/GPU_temperature",Float32,queue_size=1)
        self.cpu_temp_pub_=rospy.Publisher("stingray/pysensors/CPU_temperature",Float32,queue_size=1)
        self.cpu_core_avg_pub_=rospy.Publisher("stingray/pysensors/CPU_average_load",Float32,queue_size=1)
        
        self.pressure_=Float32()
        self.temperature_=Float32()
        # dry = true, wet = false
        self.is_dry_ = Bool()
        #jetson nano stats
        self.ram_=Float32()
        self.gpu_=Float32()
        self.jetson_power_=Float32()
        self.gpu_temp_=Float32()
        self.cpu_temp_=Float32()
        self.cpu_core_avg_=Float32()

    
    def setMsgs(self):
        self.pressure_.data = self.bmp_.get_pressure()
        self.temperature_.data = self.bmp_.get_temp()
        self.is_dry_.data = bool(self.grove_.value)
        #jetson stats
        with jtop() as jetson:
            jetsonDict = jetson.stats
            self.ram_.data=jetsonDict["RAM"]/1024/1024
            self.gpu_.data=jetsonDict["GPU"]
            self.jetson_power_.data=jetsonDict["power cur"]/1000
            self.gpu_temp_.data=jetsonDict["Temp GPU"]
            self.cpu_temp_.data=jetsonDict["Temp CPU"]
            self.cpu_core_avg_.data=(jetsonDict["CPU1"]+jetsonDict["CPU2"]+jetsonDict["CPU3"]+jetsonDict["CPU4"])/4.0
             
    def publish(self):
        self.grove_pub_.publish(self.is_dry_)
        self.bmp_temp_pub_.publish(self.temperature_)
        self.bmp_pressure_pub_.publish(self.pressure_)
        self.ram_pub_.publish(self.ram_)
        self.gpu_pub_.publish(self.gpu_)
        self.jetson_power_pub_.publish(self.jetson_power_)
        self.gpu_temp_pub_.publish(self.gpu_temp_)
        self.cpu_temp_pub_.publish(self.cpu_temp_)
        self.cpu_core_avg_pub_.publish(self.cpu_core_avg_)


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
        
