#!/bin/bash
screen -dmS roscoreScreen bash -c "cd /home/stingray/stingray_ws; roscore; exec bash -i"
screen -dmS serverScreen bash -c "cd /home/stingray/stingray_ws; roslaunch action_server as_launch.launch; exec bash -i"
screen -dmS pysensorScreen bash -c "cd /home/stingray/stingray_ws/src/pysensors/scripts; python3 py_sensors.py; exec bash -i"
screen -dmS inaScreen bash -c "cd /home/stingray/stingray_ws/src/pysensors/scripts; python3.7 ina_sensor.py; exec bash -i"
screen -dmS safetyScreen bash -c "cd /home/stingray/stingray_ws; roslaunch safety_action_client sac_launch.launch; exec bash -i"
if [ $# -eq 0 ]
then
  screen -dmS goalScreen bash -c "cd /home/stingray/stingray_ws/; roslaunch action_client gc_launch.launch; exec bash -i"
else
  if [ "$1" == "-c"]; then
    screen -dmS objScreen bash -c "cd /home/stingray/stingray_ws/src/object_detection/scripts; python3 object_detection_node.py; exec bash -i"
    screen -dmS localizationScreen bash -c "cd /home/stingray/stingray_ws/; roslaunch realsense2_camera opensource_tracking.launch; exec bash -i"
    screen -dmS goalScreen bash -c "cd /home/stingray/stingray_ws/; roslaunch action_client gc_launch.launch args1:="Y"; exec bash -i"
  else
   screen -dmS localizationScreen bash -c "cd /home/stingray/stingray_ws/; roslaunch realsense2_camera opensource_tracking.launch; exec bash -i"
   screen -dmS goalScreen bash -c "cd /home/stingray/stingray_ws/; roslaunch action_client gc_launch.launch; exec bash -i" 
  fi
fi
screen -dmS liveStream bash -c "cd /home/stingray/stingray_ws/src/live_stream/scripts; python3 zmq_live_stream_client.py; exec bash -i"
