#!/usr/bin/env python

import rospy
from std_msgs.msg import Empty
from object_detection.msg import GoalPos, GoalPositions
from object_detection.srv import Localization

def testingResponse(serviceObject,serviceName="localize"):
    #check that service is available
    rospy.wait_for_service(serviceName)
    try:
        #create object to communicate with the server
        fProxy=rospy.ServiceProxy(serviceName,Localization)
        #call the server
        fProxy()
        return "done"
    except rospy.ServiceException as e:
        print("service failed")

if __name__=="__main__":
    print("requesting response")
    localObject=Localization()
    req=testingResponse(localObject)
    print(req)
