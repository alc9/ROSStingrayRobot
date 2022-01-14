import rospy
from std_msgs import Bool, Int8,Float32
from nav_msgs import Odometry
from geometry_msgs import Twist,Pose,PoseStamped
from sensor_msgs import Imu
import numpy as np
import math

class ActuatorControl():
    def __init__(kp = 0.05,fNom= 1.4):
        #set subscribers 
        self.gt_odom_sub_=rospy.Subscriber("odom/sample",Odometry,callback=self.subscriberOdomCb,queue_size=1)
        #self.gt_imu_sub_=rospy.Subscriber("/")
        #set publishers
        self.frequency_left_pub_=rospy.Publisher("stingray/control/frequency_left",Float32,queue_size=1)
        self.frequency_right_pub_=rospy.Publisher("stingray/control/frequency_right",Float32,queue_size=1)
        self.emergency_stop_severity_level_pub_=rospy.Publisher("/stingray/control/emergency_stop_level",Int8,queue_size=1)
        self.emergency_stop_flag_pub_=rospy.Publisher("/stingray/control/emergency_stop_flag",Bool,queue_size=1)
        self.pause_flag_pub_=rospy.Publisher("/stingray/control/pause_flag",Bool,queue_size=1)
        #setup member variables
        self.f_left_ = Float32()
        self.f_right_= Float32()
        #initial position is taken as zero
        self.initial_x_=0.0
        self.initial_y_=0.0
        self.initial_z_=0.0
        # gp is handles internally by deproject to pixel point 
        # which provides a point in 3D world coordinates
        self.gp_x_=0.0
        self.gp_y_=0.0
        self.gp_z_=0.6
        self.x_=None
        self.y_=None
        self.z_=None
        self.x0_=None
        self.y0_=None
        self.z0_=None
        #self.error_ = None
        self.kp_ = kp #hz/deg
        self.nomf_ =fNom #nominal frequency
        self.deltaf_=None
        self.yaw_ref_=None
        self.yaw_measured_=None
        self.setYawRef2D()

    def subscriberOdomCb(info): 
        self.x_=info.pose.pose.position.x
        self.y_=info.pose.pose.position.y
        self.z_=info.pose.pose.position.z
        self.x0_=info.pose.pose.orientation.x
        self.y0_=info.pose.pose.orientation.y
        sely.z0_=info.pose.pose.orientation.z 
    
    def refAngle3D(xOrigin = 0.0, yOrigin=0.0, zOrigin=0.0):
        #yaw ref in 2D
        #ab is the line to initial position
        ABx = self.initial_x_ - self.xOrigin
        ABy = self.initial_y_ - self.yOrigin
        ABz = self.initial_z_ - self.zOrigin
        #ac is the line to the goal position
        BCx = self.gp_x_ -self.xOrigin
        BCy = self.gp_y_ - self.YOrigin
        BCz = self.gp_z_ - self.ZOrigin
        #dot product of lines AB and BC
        dotProduct = (ABx * BCx + 
                ABy * BCy + 
                ABz * BCz)

        magAB = (ABx * ABx +
                ABy * ABx +
                ABz* ABz)

        magBC = (BCx * BCx +
                BCy * BCy + 
                BCz * BCz)
        
        angle = dotProduct
        angle /=mat.sqrt(magAB * magBC)
        #angle = (angle * 180)/math.pi
        return angle

    def setYawRef2D(xOrigin = 0.0,yOrigin=0.0):
        """
        TODO: Add projection
        """
        #yaw ref in 2D
        #ab is the line to initial position
        ABx = self.initial_x_ - self.xOrigin
        ABy = self.initial_z_ - self.zOrigin
        #ac is the line to the goal position
        BCx = self.gp_x_ -self.xOrigin
        BCy = self.gp_z_ - self.zOrigin
        #dot product of lines AB and BC
        dotProduct = (ABx * BCx + 
                ABz * BCz)
        magAB = (ABx * ABx +
                ABz * ABz)
        magBC = (BCx * BCx +
                BCz * BCz)
        angle = dotProduct
        angle /=mat.sqrt(magAB * magBC)
        #angle = (angle * 180)/math.pi
        self.yaw_ref_ = angle

    def setYawMeasured():
        self.yaw_measured_=self.y0_

    def actuatorControlMain():
        if self.x_ is None:
            print("actuatorcontrol is waiting on  odom sub")
            return
        self.setYawMeasured()
        self.deltaf_ = self.Kp_ * (self.yaw_ref_ - self.yaw_measured_)
        self.f_left_.data=self.nomf-self.deltaf_
        self.f_right_.data=self.nomf+self.deltaf_
        frequency_left_pub_.publish(self.f_left_)
        frequency_right_pub_.publish(self.f_right_)

def main():
    rospy.init_node('testing_bottle_control_node')
    controller =ActuatorController()
    while rospy.ok():
        controller.actuatorControlMain()
if __name__ == "__main__":
    main()

