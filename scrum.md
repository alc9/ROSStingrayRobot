______
TODO:
configure launch file
compute resource monitor node
temperature/pressure node
water leakage node
power supply testing
servo power monitor node
actuator_left(update left actuator to include nose)
actionserver(control flow searching for object,control flow found object)
Test optional load goals state from cache

______
In progress:
perform IMU calibration 
adjust settings for opensource tracking
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
