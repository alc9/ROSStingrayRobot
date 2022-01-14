cmake_minimum_required(VERSION 3.0.2)

project(left_fin_actuator)

add_compile_options(-std=c++11 -li2c)

find_package(catkin REQUIRED COMPONENTS roscpp std_msgs)
#find_package(sys)
#find_package(linux)

catkin_package(INCLUDE_DIRS include)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
#include_directories(include ${catkin_INCLUDE_DIRS} ${sys_INCLUDE_DIRS} ${linux_INCLUDE_DIRS})
include_directories(include ${catkin_INCLUDE_DIRS})

set(SOURCES src/actuator.cpp src/PCA9685.cpp src/Servo.cpp)

#set(LIBPATH /usr/local /usr/local/include/)
add_executable(left_fin_actuator_node ${SOURCES})

include_directories(${catkin_INCLUDE_DIRS})

target_link_libraries(left_fin_actuator_node ${catkin_LIBRARIES})
#target_link_libraries(pectoral_fin_actuators_node ${catkin_INCLUDE_LIBRARIES})
#target_link_libraries(pectoral_fin_actuators_node sys::stat sys::ioctl linux::i2c-dev ${catkin_LIBRARIES})

install(
  TARGETS left_fin_actuator_node
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION}
)

#install(
#  DIRECTORY include/${PROJECT_NAME}/
#  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#)

