#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
import struct
#sys.path.remove('/opt/ros/melodic/lib/python2.7/dist-packages')
#sys.path.add(/)
#print(sys.path)
import rospy
import pandas as pd
from sensor_msgs.msg import Image as msg_Image
from sensor_msgs.msg import PointCloud2
from sensor_msgs import point_cloud2
import sys
import os.path
from os import path
#TORCH_PATH="/lib/aarch64-linux-gnu/ld-2.27.so"
#import importlib.util
#spec = importlib.util.spec_from_file_location("module.cv_bridge","/opt/ros/")
#from cv_bridge import CvBridge,CvBridgeError
import numpy as np
#cimport numpy
import cv2
from std_srvs.srv import Empty
from std_srvs.srv import EmptyResponse
from std_msgs.msg import String, Float32MultiArray,Time
#defined messages
from object_detection.msg import GoalPos as gp
from object_detection.msg import GoalPositions as gps
from object_detection.srv import Localization,LocalizationResponse
import torch
import torch.nn as nn
import torch.optim as optim
import collections
#import yolo
import os
import ros_numpy
#from rospy.numpy_msg import numpy_msg
#import pyrealsense2 as rs
#roslaunch realsense2_camera rs_camera.launch align_depth:=true
# roslaunch realsense2_camera rs_camera.launch enable_pointcloud:=true
# roslaunch realsense2_camera rs_camera.launch enable_pointcloud:=true align_depth:=true
# roslaunch realsense2_camera rs_camera.launch ordered_pc:=true
# roslaunch realsense2_camera rs_camera.launch initial_reset:=true
# roslaunch realsense2_camera rs_camera.launch filters:=pointcloud initial_reset:=true ordered_pc:=true align_depth:=true color_width:=424 color_height:=240 enable_sync:=true depth_fps:=6 color_fps:=6
# roslaunch realsense2_camera rs_camera.launch filters:pointcloud initial_reset:=true ordered_pc:=true color_width:=424 color_height:=240 depth_fps:=6 color_fps:=6 depth_width:=424 depth_height:=240
"""
-------------------------------------------------------------------------------------
Main class code
------------------------------------------------------------------------------------
"""
class BottleLocalizer():
    def __init__(self,scoreThreshold):
        #run for 1:30 or until found
        #cv bridge is very iffy
        #self.bridge_=CvBridge()
        #subscribers have synchronized data from realsense2 implementation
        #TODO: also need to keep an eye on the realtime or work in absolute coordinates for the depth image
        #aligned_depth_to_color / depth
        # "/camera/depth/color/points"
        self.depth_sub_=rospy.Subscriber("/camera/depth/color/points",PointCloud2,callback=self.depthCb,queue_size=1)#,buff_size=2**21)
        self.rgb_sub_=rospy.Subscriber("/camera/color/image_raw",msg_Image,callback=self.rgbCb,queue_size=1)#,buff_size=2**21)
        self.point_cloud_=None
        self.rgb_image_=None
        self.row_step_=None
        self.point_step_=None
        self.cloud_width_=None
        BESTMODELPATH="/home/stingray/stingray_ws/src/object_detection/weights/weights.pt"
        MODELPATH='ultralytics/yolov5'
        
        #setup gpu
        self.device_ = torch.device("cuda" if torch.cuda.is_available() else "cpu")
        print("using - ",self.device_)
        #get model setup
        self.model_=torch.hub.load(MODELPATH,'custom',path=BESTMODELPATH,force_reload=True)#,source='local')#classes=2)
        dummyImage = np.zeros((320,180,3),np.uint8)
        print("inputting dummy image...")
        self.model_(dummyImage)
        self.score_threshold_=scoreThreshold
        print("object detection service initialized")
    
    def depthCb(self,data):
        assert isinstance(data,PointCloud2)
        self.point_cloud_=data.data#point_cloud2.read_points(data)
        #assert istype() None # assert data is type byte and not none
        self.row_step_=data.row_step
        self.point_step_=data.point_step
        self.cloud_width_=data.width
    
    def rgbCb(self,data):
        assert isinstance(data,msg_Image)
        self.rgb_image_=ros_numpy.numpify(data)
        #numer of rows
        self.pixels_per_row_=self.rgb_image_.shape[0]//data.height
        self.pixels_per_column_=self.rgb_image_.shape[1]//data.width

    def saveVisual(self,numpyImage,resultsDf,show=False,uniqueId=False):
        import matplotlib.pyplot as plt
        import matplotlib.patches as patches 
        fix,ax = plt.subplots()
        ax.imshow(numpyImage)
        for index,row in resultsDf.iterrows():
            xLen=row['xmax']-row['xmin']
            yLen=row['ymax']-row['ymin']
            rect=patches.Rectangle((row['xmin'],row['ymin']),xLen,yLen,linewidth=1,edgecolor='r',facecolor='none')
            ax.add_patch(rect)
        plt.savefig("objDetection.jpg")

    def localize(self,req):
        #TODO: add error handling (see aruco detector)
        #request is empty
        #process all objects and let the action client handle them
        print("localize being called...")
        startTime=rospy.Time.now().to_sec()
        objsDf=self.model_(self.rgb_image_).pandas().xyxy[0] 
        print("time taken: ",rospy.Time.now().to_sec()-startTime)
        #filter databelow threshold
        print(objsDf)
        objsDf=objsDf[(objsDf[["confidence"]]>=self.score_threshold_).all(1)]
        #just for testing atm 
        #objsDf in form xmin,ymin,ymin,ymax,confidence,class,name
        if len(objsDf.index)==0:
            #let the client know of the failure
            return
        x=np.divide(np.add(objsDf["xmin"],objsDf["xmax"]),2.0).to_numpy()
        y=np.divide(np.add(objsDf["ymin"],objsDf["ymax"]),2.0).to_numpy()
        #apply function to each coordinate
        pixCoordArray=np.concatenate((x,y))
        depthArray=[]
        for i,j in zip(x,y):
            print("i,j = ",i,",",j)
            pixelRow = j//self.pixels_per_row_
            pixelCol = i//self.pixels_per_column_
            #should be between max and min of image
            print("pixelrow: ",pixelRow)
            print("pixelcolumn:",pixelCol)
            index = (pixelRow*self.row_step_)+(pixelCol*self.point_step_)
            #x,y,z in realworld coords - x is positive towards the right of the camera,y goes positive down from the centre, z goes positive out twards what the camera is looking at
            #fmt is float32
            (X,Y,Z)=struct.unpack_from('fff',self.point_cloud_,offset=int(index))
            depthArray.append([X,Y,Z])
        print(depthArray) 
        self.saveVisual(self.rgb_image_,objsDf)
        pData=gp()
        pDatas=gps() 
        for pixLocation in depthArray:
            pData.X=pixLocation[0]
            pData.Y=pixLocation[1]
            pData.Z=pixLocation[2]
            #take a copy of pData
            pDatas.Coords.append(pData)
        return LocalizationResponse(Coords=pDatas)

def main():
    #this script outputs the pixel coordinates 
    #TODO:synchronize pose with camera to use global coordinates
    # https://support.intelrealsense.com/hc/en-us/community/posts/360052359633-D435i-real-world-coordinates  
    rospy.init_node('bottle_localization_node')
    scoreThreshold=0.25
    #time limit handled by client
    bottleLocalizer=BottleLocalizer(scoreThreshold)
    localize=rospy.Service('stingray/localize',Localization,bottleLocalizer.localize)
    rospy.spin()
if __name__ == "__main__":
    main()
