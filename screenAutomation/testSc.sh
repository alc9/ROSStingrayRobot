#!/bin/bash
if [ $# -eq 0 ]
then
  screen -dmS goalScreen bash -c "cd /home/stingray/stingray_ws/; roslaunch action_client gc_launch.launch args1:="n"; exec bash -i"
else
  if [ "$1" == "-c"]; then
  screen -dmS goalScreen bash -c "cd /home/stingray/stingray_ws/; roslaunch action_client gc_launch.launch args1:="Y"; exec bash -i"
  else
   screen -dmS goalScreen bash -c "cd /home/stingray/stingray_ws/; roslaunch action_client gc_launch.launch args1:="n"; exec bash -i" 
  fi
fi
