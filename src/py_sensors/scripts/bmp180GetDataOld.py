#!/usr/bin/env python
# https://github.com/m-rtijn/bmp180/blob/master/bmp180/bmp180.py
import rospy
from bmp180 import bmp180
#rospy.loginfo("BMP180 init error", e)

from sensor_msgs.msg import Temperature,FluidPressure
rospy.init_node('bmp180_node')
rate=rospy.Rate(10)
#sudo i2cdetect -y -a 2
address=0x57
bmp = bmp180(address)
pubPressure=rospy.Publisher('bmp180Pressure',FluidPressure,queue_size=1)
pubTemp=rospy.Publisher('bmp180Temperature',Temperature,queue_size=1)

def makeTempMsg():
    tempMsg=Temperature()
    tempMsg.header.stamp = rospy.Time.now()
    tempMsg.temperature=float(bmp.get_temp())
    msg.variance=0.0
    return makeTempMsg
def makePressureMsg():
    pressureMsg=FluidPressure()
    pressureMsg.header.stamp=rospy.Time.now()
    pressureMsg.fluid_pressure=float(bmp.get_pressure())
    pressureMsg.variance=0.0
    return pressureMsg

def publishData():
    self.pubTemp(makeTempMsg()) 
    self.pubPressure(makePressureMsg())
while not rospy.is_shutdown():
    publishData()
    rate.sleep()
