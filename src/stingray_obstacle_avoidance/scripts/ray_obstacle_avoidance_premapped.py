#!/usr/bin/env python
from __future__ import absolute_import
import numpy as np
import open3d as o3d
import fcl
import rospy
from nav_msgs.msg import Odometry
import tf

class CollisionDetector():
    def __init__(self):
        self.collide = False
        self.collision_pub_=rospy.Publisher("stingray/control/collision")
        self.is_collision_=Bool()
        self.is_collision_.data = False
        self.tf_listener_=tf.TransformListener()
        self.obstacle_map_=None # fcl.Mesh
        t = fcl.Transform(np.array([[1.0,0.0,0.0],[0.0,1.0,0.0],[0.0,0.0,1.0]]),np.array([0.0,0.0,0.0]))
        robot_shape_=fcl.Box(0.6,0.6,0.6)
        self.robot_collision_obj_=fcl.CollisionObject(robot_shape,t)
        self.collision_box_=[]
        #array n,d
        #if the normal vector is unit length, then the constant term of the plane equation, d becomes the distance from the origin, no plane on lid
        #xyz: right,below,infront of camera
        # ahead, behind, left, right , underneath
        # d = -ax0-by0-cz0
        # origins
        #0.0,1.0,1.5 - ahead
        #0.0 1.0 -0.5 - behind
        #-1.0, 1.0, 1.5 - left*
        #1.0, 1.0 1.5 - right*
        #0.0, 2.0, 0.5 - underneath
        # https://mathworld.wolfram.com/Plane.html
        planeList = [[np.array([0.0,0.0,1.0]),-1.5],
        [np.array([0.0,0.0,1.0]),0.5],
        [np.array([1.0,0.0,0.0]),1.0],
        [np.array([1.0,0.0,0.0]),-1.0],
        [np.array([0.0, 1.0, 0.0]),-2.0]]
        for plane in planeList:
            self.collision_box_.append(fcl.Plane(plane[0],plane[1]))

    def setSyncCollisionObj(self):
        #this can be sped up using make_cropbox()
        #https://github.com/strawlab/python-pcl/blob/master/tests/test_filters.pyelf.obstacle_map_=None
        translation,quaternion = self.tf_listener_.lookupTransform("/map","camera_link")
        self.robot_collision_obj_.setTranslation(translation)
        return True
          
    def checkCollision(self):
        if self.setSyncCollisionObj():
            request = fcl.CollisionRequest()
            result = fcl.CollisionResult()
            for plane in collision_box_:
                if fcl.collide(plane,self.robot_collision_obj_,request,result) is False:
                    return False 
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
