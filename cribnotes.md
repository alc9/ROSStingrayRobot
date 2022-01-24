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
#check tf data
tf_echo
# memory addresses 
sudo i2cdetect -y -r 1
0x40 (left fin)
0x41 (right fin)
bmp180 0x77
# test imports
python -c "import tf"
# dependencies installed
/opt/ros/melodic/lib
# check exe so libs
ldd executableFile
# undefined reference 
.so is not found in path
# undefined symbol 
multiple .so found in path
# check dynamic-link table
nm -D lib.so
-U is for undefine
# scan for undefined symbol
/opt/ros/melodic/lib$ for x in $(find /opt/ros/melodic/lib/ -name "*.so"); do  nm -D $x | grep _ZN7tf2_ros20TransformBroadcasterC1Ev && echo $x; done
# build fix - only building geometry2 which had a broken dynamic-link table  
catkin_make -DPYTHON_EXECUTABLE:FILEPATH=/usr/bin/python3 -DPYTHON_INCLUDE_DIR=/usr/include/python3.6m -DPYTHON_LIBRARY=/usr/lib/aarch64-linux-gnu/libpython3.6m.so --only-pkg-with-deps geometry2
# black list and whitelist
catkin_make DCATKIN_BLACKLIST_PACKAGES=""
catkin_make DCATKIN_WHITELIST_PACKAGES=""
-DCATKIN_BLACKLIST_PACKAGES="eigen_conversions;geometry;kdl_conversions;tf;tf2;tf2_msgs;tf2_py;tf2_ros;tf_conversions;tf2_bullet;tf2_eigen;test_tf2;tf2_sensor_msgs;tf2_tools;realsense2_camera;realsense2_description;tf2_geometry_msgs;tf2_kdl"
# launch with command line args
roslaunch pkg launch_file.launch args1:="Y" args2:="n" 
#tips on removing bin/libs
Files under /bin , /lib , /sbin or /usr except for /usr/local are under the control of the package manager. Never modify or delete these files manually. To check whether a library under /lib or /usr/lib is in use, first determine which package contains it. On Linux Mint, run dpkg -S /usr/lib/libgme.so.
# check package
dpkg -l | grep librealsense
