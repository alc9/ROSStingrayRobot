#!/bin/bash
screen -dmS roscoreScreen bash -c "cd /home/stingray/stingray_ws; roscore; exec bash -i"
sleep 10s
screen -dmS objScreen bash -c "cd /home/stingray/stingray_ws/src/object_detection/scripts; python3 object_detection_node.py; exec bash -i"
screen -dmS localizationScreen bash -c "cd /home/stingray/stingray_ws/; roslaunch realsense2_camera opensource_tracking.launch; exec bash -i"
sleep 20s
screen -dmS clientScreen bash -c "cd /home/stingray/stingray_ws/src/object_detection/testing; python3 askService.py; exec bash -i"

