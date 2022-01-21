cmake_minimum_required(VERSION 3.10.2)
#cmake_minimum_required(VERSION 3.14.2)
project(object_detection)
#set(CMAKE_PREFIX_PATH="/usr/local/bin/cmake")
#set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
## Compile as C++11, supported in ROS Kinetic and newer
#add_compile_options(-std=c++14) #'pkg-config opencv --cflags libs')

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
#option(BUILD_WITH_OPENMP "Use OpenMP" OFF)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  sensor_msgs
  std_msgs
  message_generation
  image_transport
  cv_bridge
  tf
)
find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenCV REQUIRED)
#find_package(Torch REQUIRED)
#catkin_package(INCLUDE_DIRS include)

#include_directories(${catkin_INCLUDE_DIRS})

#set(SOURCES src/object_localize.cpp)

#add_executable(bottle_localization_node)

#include_directories(${catkin_INCLUDE_DIRS})

#target_link_libraries(bottle_localization_server_node ${catkin_LIBRARIES})

#install(
#    TARGETS bottle_localization_node
#    ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#    LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#    RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION}
#    )


 add_message_files(
   FILES
   GoalPos.msg
   GoalPositions.msg
 )

## Generate services in the 'srv' folder
 add_service_files(
   FILES
   Localization.srv
 )

 generate_messages(
   DEPENDENCIES
   std_msgs
   sensor_msgs
 )

#add_executable(object_detection_server_node src/object_detection_server.cpp)

#catkin_package(
#   INCLUDE_DIRS include
#  CATKIN_DEPENDS roscpp
#                 rospy
#                 sensor_msgs
#                 std_msgs
#                 cv_bridge
#                 image_transport
#)

#add_executable(object_detection_server_node src/object_detection_server.cpp)

#include_directories(
#  ${catkin_INCLUDE_DIRS}
#  ${OpenCV_INCLUDE_DIRS}
  #${TORCH_INCLUDE_DIRS}
  #)
#add_executable(object_detection_server_node src/object_detection_server.cpp)
#add_dependencies(object_detection ${${PROJECT_NAME}_EXPORTED_TARGETS}) #${TORCH_EXPORTED_TARGETS})

#target_link_libraries(object_detection_server_node ${catkin_LIBRARIES} ${OpenCV_LIBRARIES}) #"${TORCH_LIBRARIES}") #"${lCUDA_cublas_device_LIBRARIES}")

#set_property(TARGET object_detection_server_node PROPERTY CXX_STANDARD 14)

#install(
#    TARGETS object_detection_server_node
#    ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#    LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#    RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION}
#    )


