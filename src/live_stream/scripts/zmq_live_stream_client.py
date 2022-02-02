#!/usr/bin/env python
# -*- coding: utf-8 -*-
import base64
import zmq
import time
import rospy
from sensor_msgs.msg import Image as msg_Image
import ros_numpy
import cv2

class LiveStreamClient():
    def __init__(self):
        self.rgb_sub_=rospy.Subscriber("/camera/color/image_raw",msg_Image, callback=self.rgbCb,queue_size=1)#,buff_size=2**21)
        self.client_=None
        self.context_ = zmq.Context()
        self.client_ = self.context_.socket(zmq.PUB)
        self.client_.connect("tcp://192.168.0.54:5555") 
    
    def rgbCb(self,img):
        assert isinstance(img,msg_Image)
        if self.client_:
            c,img = cv2.imencode('.jpg',ros_numpy.numpify(img))
            self.client_.send(img)
            return
        else:
            print("TCP_client initialize fail")

def main():
    rospy.init_node('live_stream_node')
    client = LiveStreamClient()
    rospy.spin()

if __name__ == "__main__":
    main()
