______
TODO:
configure launch files
compute resource monitor node
servo power monitor node
actuator_left(update left actuator to include nose)
perform IMU calibration 
adjust settings for opensource tracking
test pipeline 
______
In progress:
Test optional load goals state from cache
______
Finished:
finish writing action_server (integrate python control into c++ code)
Test actuator control and commander c++ class
Add commander for left actuator
Write action_publisher python script for testing actuator control
Testing goal client class within action_client 
Add optional goal locations and pose load from file and optional save goal locations and pose to file (testing speed increase and crash recovery)
adding client class within action_client for communicating with object_detection_server_node
configuring xml for realsense2_camera node(improved connection quality)
object_detection.py
testing object_localization (gpu/runtime tests)
configuring cuda gpu for object_localization
adding emergencyStop(), smoothTransition(), reverse() to stingray
adding default action client
updating servo default orientation and testing actuation
