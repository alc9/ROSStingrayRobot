import rospy
from std_msgs.msg import Bool, Int8,Float32
from nav_msgs.msg import Odometry
from geometry_msgs.msg import Twist,Pose,PoseStamped
from sensor_msgs.msg import Imu
import numpy as np
import math
import time

# TODO: add fall back if sub broken https://www.reddit.com/r/ROS/comments/j29oz5/is_it_possible_to_change_a_subscribed_topic_on/ 
class ActuatorController():
    def __init__(self,kp = 0.05,fNom= 1.4):
        #set subscribers 
        #self.gt_odom_sub_=rospy.Subscriber("",Odometry,callback=self.subscriberOdomCb,queue_size=1)
        
        #self.gt_odom_backup_sub_=rospy.Subscriber("odometry/filtered",Odometry,callback=self.subscriberOdomBackupCb,queue_size=1)

        self.gt_odom_sub_=rospy.Subscriber("rtabmap/odom",Odometry,callback=self.subscriberOdomCb,queue_size=1)
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
        # gp is handles internally by deproject to pixel point 
        # which provides a point in 3D world coordinates
        self.gp_x_=0.0
        self.gp_y_=0.0
        self.gp_z_=0.86
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

    def subscriberOdomCb(self,info):
        self.x_=info.pose.pose.position.x
        self.z_=info.pose.pose.position.y
        self.y_=info.pose.pose.position.z
        self.x0_=info.pose.pose.orientation.x
        self.y0_=info.pose.pose.orientation.z
        self.z0_=info.pose.pose.orientation.y
	
    def setYawRef2D(self):
        #yaw ref in 2D
        #ab is the line to initial position
        # z is out of the camera through the line of the nose, x is to the left hand side of the camera
        nextX = self.z_ + 1 * math.cos(self.yaw_measured_)
        nextZ=self.x_ + 1*math.sin(self.yaw_measured_)
        ABx = nextX - self.x_
        ABz = nextZ - self.z_
        #ac is the line to the goal position
        BCx = self.gp_x_ -self.x_
        BCz = self.gp_z_ - self.z_
        #dot product of lines AB and BC
        dotProduct = (ABx * BCx + 
                ABz * BCz)
        magAB = (ABx * ABx +
                ABz * ABz)
        magBC = (BCx * BCx +
                BCz * BCz)
        angle = dotProduct
        angle /=math.sqrt(magAB * magBC)
        #angle = (angle * 180)/math.pi
        self.yaw_ref_ = angle

    def setYawMeasured(self):
        self.yaw_measured_=self.y0_
        """
        if self.y0_ < 0:
            self.yaw_measured_=abs(self.y0_)
            print("yaw negative ",self.yaw_measured_)
            return
        self.yaw_measured_=2*math.pi-self.y0_
        print("yaw positive",self.yaw_measured_)
        """
    def actuatorControlMain(self):
        if self.x_ is None:
            #print("pose is None")
            return
        self.setYawMeasured()
        self.setYawRef2D()
        self.deltaf_ = self.kp_ * (180.0/math.pi)*(self.yaw_ref_ - self.yaw_measured_)
        self.f_left_.data=self.nomf_ - self.deltaf_
        self.f_right_.data=self.nomf_ + self.deltaf_
        self.frequency_left_pub_.publish(self.f_left_)
        self.frequency_right_pub_.publish(self.f_right_)

def main():
    rospy.init_node('testing_bottle_control_node')
    controller =ActuatorController()
    while not rospy.is_shutdown():
        time.sleep(2)
        controller.actuatorControlMain()
if __name__ == "__main__":
    main()

