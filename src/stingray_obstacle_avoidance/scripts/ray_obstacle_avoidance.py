#!/usr/bin/env python
from __future__ import absolute_import
import numpy as np
import open3d as o3d
#https://github.com/kucars/laser_collision_detection/blob/1b78fe5a95584d135809b1448d33675bb8fee250/src/laser_obstacle_detect.cpp#L252
#TODO: best method is to generate an open3d.geometry.Octree then generate boxes
import fcl
import rospy
#from sensor_msgs.msg import PointCloud2
#from sensor_msgs import point_cloud2
#octomap_msgs   
from octomap_msgs import Octomap,binaryMsgToMap
import octomap
from nav_msgs.msg import Odometry
import tf
from collections import deque
import ros_numpy
#   https://stackoverflow.com/questions/39772424/how-to-effeciently-convert-ros-pointcloud2-to-pcl-point-cloud-and-visualize-it-i
#//github.com/BerkeleyAutomation/python-fcl/blob/master/example/example.py
class CollisionDetector():
    def __init__(self):
        self.collide = False
        self.obstacle_sub_ = rospy.Subscriber("/rtabmap/octomap_binary",Octomap,callback=self.obstacleSubCb,queue_size=1)
        self.obstacle_map_deque_=deque()
        self.collision_pub_=rospy.Publisher("stingray/control/collision")
        self.is_collision_=Bool()
        self.is_collision_.data = False
        self.tf_listener_=tf.TransformListener()
        self.obstacle_map_=None # fcl.Mesh
        t = fcl.Transform(np.array([[1.0,0.0,0.0],[0.0,1.0,0.0],[0.0,0.0,1.0]]),np.array([0.0,0.0,0.0]))
        robot_shape_=fcl.Box(0.6,0.6,0.6)
        self.robot_collision_obj_=fcl.CollisionObject(robot_shape,t)
    
    def obstacleSubCb(self,data):
        if len(self.obstacle_map_deque_) > 3:
            self.obstacle_map_deque_.pop()
        
        self.obstacle_map_deque_.appendleft(data)
    
    def setSyncCollisionObj(self):
        #this can be sped up using make_cropbox()
        #https://github.com/strawlab/python-pcl/blob/master/tests/test_filters.pyelf.obstacle_map_=None
        while len(self.obstacle_map_deque_) > 0:
            pc_tmp = self.obstacle_map_deque_.popleft()
            if self.tf_listener_.canTransform("/map","/camera_link",self.pc_tmp.header.stamp):
                translation,quaternion = self.tf_listener_.lookupTransform("/map","camera_link",self.pc_tmp.header.stamp)
                #self.tf_mat_=self.tf_listener_.fromTranslationRotation(translation,quaternion)
                self.robot_collision_obj_.setTranslation(translation)
                #pc_tmp = ros_numpy.numpify(pc_tmp)
                #bounding volume hierarchy
                #self.obstacle_map_=fcl.BVHModel()
                #points = np.zeros((pc_tmp.shape[0],3))
                #points[:,0]=pc_tmp['x']
                #points[:,1]=pc_tmp['y']
                #points[:,2]=pc_tmp['z']
                #self.obstacle_map_=pcl.PointCloud(np.array(points,dtype=np.float32))
                self.obstacle_map_=fcl.CollisionObject(fcl.OcTree(binaryMsgToMap(pc_tmp),fcl.Transform)) 
                return True
        self.obstacle_map_=None
        return False
    
    def checkCollision(self):
        if self.setSyncCollisionObj():
            request = fcl.CollisionRequest()
            result = fcl.CollisionResult()
            return fcl.collide(self.obstacle_map_,self.robot_collision_obj_,request,result)
        else: 
            return -1
                
def main():
    rospy.init_node('ray_obstacle_avoidance_node')
    collisionDetector = CollisionDetector()
    while not rospy.is_shutdown():
        rospy.spin()
    print("ray_obstacle_avoidance is terminating")
if __name__ =="__main__":
    main()
