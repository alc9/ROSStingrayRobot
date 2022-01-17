#check for multiple installs of a library
ldconfig -v | grep [library name]
#compile with python3 
catkin build --cmake-args -DPYTHON_VERSION=3.6
#search for modules
pip --list
#location - replace with command
which cmake 
#env get
printenv
#print diagnostics 
ros echo /diagnostics
#available hardware configurations
rs-enumerate-devices
#frequency of operation
rostopic hz /camera/depth/color/points
#make with python3 
-DPYTHON_EXECUTABLE=/usr/bin/python3
#undefined symbol: _ZN2cvMatC1Env
delete the librealsense2_camera.so file in /home/xxx/stingray_ws/devel/lib/path
#debug error
I am also encountering this issue, and I believe I can contribute in the debugging of it: I think that the pointcloud filter is doing something similar to the align_depth filter. That filter runs at around 2-3 FPS on a raspberry pi, and as a result, we see the queue backing up & preventing the system from making progress as @doronhi commented above.
#full build flags
catkin_make -DPYTHON_EXECUTABLE=/usr/bin/python3 -DCATKIN_ENABLE_TESTING=False -DCMAKE_BUILD_TYPE=Release
catkin_make -DPYTHON_EXECUTABLE=/usr/bin/python3
#SLAM with D435i
intel opensource slam depends on madgwick, rtabmap, and robot_localization
Madgwick fuses angular velocities, accelerations and magnetic readings into an orientation.RTAB is an RGB-D slam approach which can create 3D point clouds or 2D occupancy maps, robot localization is a collection of state estimation nodes which provides an estimate for the position and orientation. 
#check motion module with 
rs-motion
