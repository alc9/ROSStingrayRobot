# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "action_server: 7 messages, 0 services")

set(MSG_I_FLAGS "-Iaction_server:/home/stingray/stingray_ws/devel/share/action_server/msg;-Iactionlib_msgs:/opt/ros/melodic/share/actionlib_msgs/cmake/../msg;-Istd_msgs:/opt/ros/melodic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(action_server_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/stingray/stingray_ws/devel/share/action_server/msg/defAction.msg" NAME_WE)
add_custom_target(_action_server_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "action_server" "/home/stingray/stingray_ws/devel/share/action_server/msg/defAction.msg" "action_server/defActionGoal:action_server/defActionResult:action_server/defActionFeedback:std_msgs/Header:actionlib_msgs/GoalID:action_server/defResult:action_server/defFeedback:actionlib_msgs/GoalStatus:action_server/defGoal"
)

get_filename_component(_filename "/home/stingray/stingray_ws/devel/share/action_server/msg/defActionGoal.msg" NAME_WE)
add_custom_target(_action_server_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "action_server" "/home/stingray/stingray_ws/devel/share/action_server/msg/defActionGoal.msg" "action_server/defGoal:actionlib_msgs/GoalID:std_msgs/Header"
)

get_filename_component(_filename "/home/stingray/stingray_ws/devel/share/action_server/msg/defActionResult.msg" NAME_WE)
add_custom_target(_action_server_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "action_server" "/home/stingray/stingray_ws/devel/share/action_server/msg/defActionResult.msg" "actionlib_msgs/GoalID:action_server/defResult:std_msgs/Header:actionlib_msgs/GoalStatus"
)

get_filename_component(_filename "/home/stingray/stingray_ws/devel/share/action_server/msg/defActionFeedback.msg" NAME_WE)
add_custom_target(_action_server_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "action_server" "/home/stingray/stingray_ws/devel/share/action_server/msg/defActionFeedback.msg" "actionlib_msgs/GoalID:action_server/defFeedback:std_msgs/Header:actionlib_msgs/GoalStatus"
)

get_filename_component(_filename "/home/stingray/stingray_ws/devel/share/action_server/msg/defGoal.msg" NAME_WE)
add_custom_target(_action_server_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "action_server" "/home/stingray/stingray_ws/devel/share/action_server/msg/defGoal.msg" ""
)

get_filename_component(_filename "/home/stingray/stingray_ws/devel/share/action_server/msg/defResult.msg" NAME_WE)
add_custom_target(_action_server_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "action_server" "/home/stingray/stingray_ws/devel/share/action_server/msg/defResult.msg" ""
)

get_filename_component(_filename "/home/stingray/stingray_ws/devel/share/action_server/msg/defFeedback.msg" NAME_WE)
add_custom_target(_action_server_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "action_server" "/home/stingray/stingray_ws/devel/share/action_server/msg/defFeedback.msg" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(action_server
  "/home/stingray/stingray_ws/devel/share/action_server/msg/defAction.msg"
  "${MSG_I_FLAGS}"
  "/home/stingray/stingray_ws/devel/share/action_server/msg/defActionGoal.msg;/home/stingray/stingray_ws/devel/share/action_server/msg/defActionResult.msg;/home/stingray/stingray_ws/devel/share/action_server/msg/defActionFeedback.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/stingray/stingray_ws/devel/share/action_server/msg/defResult.msg;/home/stingray/stingray_ws/devel/share/action_server/msg/defFeedback.msg;/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/home/stingray/stingray_ws/devel/share/action_server/msg/defGoal.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/action_server
)
_generate_msg_cpp(action_server
  "/home/stingray/stingray_ws/devel/share/action_server/msg/defActionGoal.msg"
  "${MSG_I_FLAGS}"
  "/home/stingray/stingray_ws/devel/share/action_server/msg/defGoal.msg;/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/action_server
)
_generate_msg_cpp(action_server
  "/home/stingray/stingray_ws/devel/share/action_server/msg/defActionResult.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/stingray/stingray_ws/devel/share/action_server/msg/defResult.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/action_server
)
_generate_msg_cpp(action_server
  "/home/stingray/stingray_ws/devel/share/action_server/msg/defActionFeedback.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/stingray/stingray_ws/devel/share/action_server/msg/defFeedback.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/action_server
)
_generate_msg_cpp(action_server
  "/home/stingray/stingray_ws/devel/share/action_server/msg/defGoal.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/action_server
)
_generate_msg_cpp(action_server
  "/home/stingray/stingray_ws/devel/share/action_server/msg/defResult.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/action_server
)
_generate_msg_cpp(action_server
  "/home/stingray/stingray_ws/devel/share/action_server/msg/defFeedback.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/action_server
)

### Generating Services

### Generating Module File
_generate_module_cpp(action_server
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/action_server
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(action_server_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(action_server_generate_messages action_server_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/stingray/stingray_ws/devel/share/action_server/msg/defAction.msg" NAME_WE)
add_dependencies(action_server_generate_messages_cpp _action_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/stingray/stingray_ws/devel/share/action_server/msg/defActionGoal.msg" NAME_WE)
add_dependencies(action_server_generate_messages_cpp _action_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/stingray/stingray_ws/devel/share/action_server/msg/defActionResult.msg" NAME_WE)
add_dependencies(action_server_generate_messages_cpp _action_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/stingray/stingray_ws/devel/share/action_server/msg/defActionFeedback.msg" NAME_WE)
add_dependencies(action_server_generate_messages_cpp _action_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/stingray/stingray_ws/devel/share/action_server/msg/defGoal.msg" NAME_WE)
add_dependencies(action_server_generate_messages_cpp _action_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/stingray/stingray_ws/devel/share/action_server/msg/defResult.msg" NAME_WE)
add_dependencies(action_server_generate_messages_cpp _action_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/stingray/stingray_ws/devel/share/action_server/msg/defFeedback.msg" NAME_WE)
add_dependencies(action_server_generate_messages_cpp _action_server_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(action_server_gencpp)
add_dependencies(action_server_gencpp action_server_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS action_server_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(action_server
  "/home/stingray/stingray_ws/devel/share/action_server/msg/defAction.msg"
  "${MSG_I_FLAGS}"
  "/home/stingray/stingray_ws/devel/share/action_server/msg/defActionGoal.msg;/home/stingray/stingray_ws/devel/share/action_server/msg/defActionResult.msg;/home/stingray/stingray_ws/devel/share/action_server/msg/defActionFeedback.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/stingray/stingray_ws/devel/share/action_server/msg/defResult.msg;/home/stingray/stingray_ws/devel/share/action_server/msg/defFeedback.msg;/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/home/stingray/stingray_ws/devel/share/action_server/msg/defGoal.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/action_server
)
_generate_msg_eus(action_server
  "/home/stingray/stingray_ws/devel/share/action_server/msg/defActionGoal.msg"
  "${MSG_I_FLAGS}"
  "/home/stingray/stingray_ws/devel/share/action_server/msg/defGoal.msg;/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/action_server
)
_generate_msg_eus(action_server
  "/home/stingray/stingray_ws/devel/share/action_server/msg/defActionResult.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/stingray/stingray_ws/devel/share/action_server/msg/defResult.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/action_server
)
_generate_msg_eus(action_server
  "/home/stingray/stingray_ws/devel/share/action_server/msg/defActionFeedback.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/stingray/stingray_ws/devel/share/action_server/msg/defFeedback.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/action_server
)
_generate_msg_eus(action_server
  "/home/stingray/stingray_ws/devel/share/action_server/msg/defGoal.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/action_server
)
_generate_msg_eus(action_server
  "/home/stingray/stingray_ws/devel/share/action_server/msg/defResult.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/action_server
)
_generate_msg_eus(action_server
  "/home/stingray/stingray_ws/devel/share/action_server/msg/defFeedback.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/action_server
)

### Generating Services

### Generating Module File
_generate_module_eus(action_server
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/action_server
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(action_server_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(action_server_generate_messages action_server_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/stingray/stingray_ws/devel/share/action_server/msg/defAction.msg" NAME_WE)
add_dependencies(action_server_generate_messages_eus _action_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/stingray/stingray_ws/devel/share/action_server/msg/defActionGoal.msg" NAME_WE)
add_dependencies(action_server_generate_messages_eus _action_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/stingray/stingray_ws/devel/share/action_server/msg/defActionResult.msg" NAME_WE)
add_dependencies(action_server_generate_messages_eus _action_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/stingray/stingray_ws/devel/share/action_server/msg/defActionFeedback.msg" NAME_WE)
add_dependencies(action_server_generate_messages_eus _action_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/stingray/stingray_ws/devel/share/action_server/msg/defGoal.msg" NAME_WE)
add_dependencies(action_server_generate_messages_eus _action_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/stingray/stingray_ws/devel/share/action_server/msg/defResult.msg" NAME_WE)
add_dependencies(action_server_generate_messages_eus _action_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/stingray/stingray_ws/devel/share/action_server/msg/defFeedback.msg" NAME_WE)
add_dependencies(action_server_generate_messages_eus _action_server_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(action_server_geneus)
add_dependencies(action_server_geneus action_server_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS action_server_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(action_server
  "/home/stingray/stingray_ws/devel/share/action_server/msg/defAction.msg"
  "${MSG_I_FLAGS}"
  "/home/stingray/stingray_ws/devel/share/action_server/msg/defActionGoal.msg;/home/stingray/stingray_ws/devel/share/action_server/msg/defActionResult.msg;/home/stingray/stingray_ws/devel/share/action_server/msg/defActionFeedback.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/stingray/stingray_ws/devel/share/action_server/msg/defResult.msg;/home/stingray/stingray_ws/devel/share/action_server/msg/defFeedback.msg;/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/home/stingray/stingray_ws/devel/share/action_server/msg/defGoal.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/action_server
)
_generate_msg_lisp(action_server
  "/home/stingray/stingray_ws/devel/share/action_server/msg/defActionGoal.msg"
  "${MSG_I_FLAGS}"
  "/home/stingray/stingray_ws/devel/share/action_server/msg/defGoal.msg;/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/action_server
)
_generate_msg_lisp(action_server
  "/home/stingray/stingray_ws/devel/share/action_server/msg/defActionResult.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/stingray/stingray_ws/devel/share/action_server/msg/defResult.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/action_server
)
_generate_msg_lisp(action_server
  "/home/stingray/stingray_ws/devel/share/action_server/msg/defActionFeedback.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/stingray/stingray_ws/devel/share/action_server/msg/defFeedback.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/action_server
)
_generate_msg_lisp(action_server
  "/home/stingray/stingray_ws/devel/share/action_server/msg/defGoal.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/action_server
)
_generate_msg_lisp(action_server
  "/home/stingray/stingray_ws/devel/share/action_server/msg/defResult.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/action_server
)
_generate_msg_lisp(action_server
  "/home/stingray/stingray_ws/devel/share/action_server/msg/defFeedback.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/action_server
)

### Generating Services

### Generating Module File
_generate_module_lisp(action_server
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/action_server
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(action_server_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(action_server_generate_messages action_server_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/stingray/stingray_ws/devel/share/action_server/msg/defAction.msg" NAME_WE)
add_dependencies(action_server_generate_messages_lisp _action_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/stingray/stingray_ws/devel/share/action_server/msg/defActionGoal.msg" NAME_WE)
add_dependencies(action_server_generate_messages_lisp _action_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/stingray/stingray_ws/devel/share/action_server/msg/defActionResult.msg" NAME_WE)
add_dependencies(action_server_generate_messages_lisp _action_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/stingray/stingray_ws/devel/share/action_server/msg/defActionFeedback.msg" NAME_WE)
add_dependencies(action_server_generate_messages_lisp _action_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/stingray/stingray_ws/devel/share/action_server/msg/defGoal.msg" NAME_WE)
add_dependencies(action_server_generate_messages_lisp _action_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/stingray/stingray_ws/devel/share/action_server/msg/defResult.msg" NAME_WE)
add_dependencies(action_server_generate_messages_lisp _action_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/stingray/stingray_ws/devel/share/action_server/msg/defFeedback.msg" NAME_WE)
add_dependencies(action_server_generate_messages_lisp _action_server_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(action_server_genlisp)
add_dependencies(action_server_genlisp action_server_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS action_server_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(action_server
  "/home/stingray/stingray_ws/devel/share/action_server/msg/defAction.msg"
  "${MSG_I_FLAGS}"
  "/home/stingray/stingray_ws/devel/share/action_server/msg/defActionGoal.msg;/home/stingray/stingray_ws/devel/share/action_server/msg/defActionResult.msg;/home/stingray/stingray_ws/devel/share/action_server/msg/defActionFeedback.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/stingray/stingray_ws/devel/share/action_server/msg/defResult.msg;/home/stingray/stingray_ws/devel/share/action_server/msg/defFeedback.msg;/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/home/stingray/stingray_ws/devel/share/action_server/msg/defGoal.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/action_server
)
_generate_msg_nodejs(action_server
  "/home/stingray/stingray_ws/devel/share/action_server/msg/defActionGoal.msg"
  "${MSG_I_FLAGS}"
  "/home/stingray/stingray_ws/devel/share/action_server/msg/defGoal.msg;/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/action_server
)
_generate_msg_nodejs(action_server
  "/home/stingray/stingray_ws/devel/share/action_server/msg/defActionResult.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/stingray/stingray_ws/devel/share/action_server/msg/defResult.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/action_server
)
_generate_msg_nodejs(action_server
  "/home/stingray/stingray_ws/devel/share/action_server/msg/defActionFeedback.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/stingray/stingray_ws/devel/share/action_server/msg/defFeedback.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/action_server
)
_generate_msg_nodejs(action_server
  "/home/stingray/stingray_ws/devel/share/action_server/msg/defGoal.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/action_server
)
_generate_msg_nodejs(action_server
  "/home/stingray/stingray_ws/devel/share/action_server/msg/defResult.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/action_server
)
_generate_msg_nodejs(action_server
  "/home/stingray/stingray_ws/devel/share/action_server/msg/defFeedback.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/action_server
)

### Generating Services

### Generating Module File
_generate_module_nodejs(action_server
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/action_server
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(action_server_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(action_server_generate_messages action_server_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/stingray/stingray_ws/devel/share/action_server/msg/defAction.msg" NAME_WE)
add_dependencies(action_server_generate_messages_nodejs _action_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/stingray/stingray_ws/devel/share/action_server/msg/defActionGoal.msg" NAME_WE)
add_dependencies(action_server_generate_messages_nodejs _action_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/stingray/stingray_ws/devel/share/action_server/msg/defActionResult.msg" NAME_WE)
add_dependencies(action_server_generate_messages_nodejs _action_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/stingray/stingray_ws/devel/share/action_server/msg/defActionFeedback.msg" NAME_WE)
add_dependencies(action_server_generate_messages_nodejs _action_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/stingray/stingray_ws/devel/share/action_server/msg/defGoal.msg" NAME_WE)
add_dependencies(action_server_generate_messages_nodejs _action_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/stingray/stingray_ws/devel/share/action_server/msg/defResult.msg" NAME_WE)
add_dependencies(action_server_generate_messages_nodejs _action_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/stingray/stingray_ws/devel/share/action_server/msg/defFeedback.msg" NAME_WE)
add_dependencies(action_server_generate_messages_nodejs _action_server_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(action_server_gennodejs)
add_dependencies(action_server_gennodejs action_server_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS action_server_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(action_server
  "/home/stingray/stingray_ws/devel/share/action_server/msg/defAction.msg"
  "${MSG_I_FLAGS}"
  "/home/stingray/stingray_ws/devel/share/action_server/msg/defActionGoal.msg;/home/stingray/stingray_ws/devel/share/action_server/msg/defActionResult.msg;/home/stingray/stingray_ws/devel/share/action_server/msg/defActionFeedback.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/stingray/stingray_ws/devel/share/action_server/msg/defResult.msg;/home/stingray/stingray_ws/devel/share/action_server/msg/defFeedback.msg;/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/home/stingray/stingray_ws/devel/share/action_server/msg/defGoal.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/action_server
)
_generate_msg_py(action_server
  "/home/stingray/stingray_ws/devel/share/action_server/msg/defActionGoal.msg"
  "${MSG_I_FLAGS}"
  "/home/stingray/stingray_ws/devel/share/action_server/msg/defGoal.msg;/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/action_server
)
_generate_msg_py(action_server
  "/home/stingray/stingray_ws/devel/share/action_server/msg/defActionResult.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/stingray/stingray_ws/devel/share/action_server/msg/defResult.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/action_server
)
_generate_msg_py(action_server
  "/home/stingray/stingray_ws/devel/share/action_server/msg/defActionFeedback.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/stingray/stingray_ws/devel/share/action_server/msg/defFeedback.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/action_server
)
_generate_msg_py(action_server
  "/home/stingray/stingray_ws/devel/share/action_server/msg/defGoal.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/action_server
)
_generate_msg_py(action_server
  "/home/stingray/stingray_ws/devel/share/action_server/msg/defResult.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/action_server
)
_generate_msg_py(action_server
  "/home/stingray/stingray_ws/devel/share/action_server/msg/defFeedback.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/action_server
)

### Generating Services

### Generating Module File
_generate_module_py(action_server
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/action_server
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(action_server_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(action_server_generate_messages action_server_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/stingray/stingray_ws/devel/share/action_server/msg/defAction.msg" NAME_WE)
add_dependencies(action_server_generate_messages_py _action_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/stingray/stingray_ws/devel/share/action_server/msg/defActionGoal.msg" NAME_WE)
add_dependencies(action_server_generate_messages_py _action_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/stingray/stingray_ws/devel/share/action_server/msg/defActionResult.msg" NAME_WE)
add_dependencies(action_server_generate_messages_py _action_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/stingray/stingray_ws/devel/share/action_server/msg/defActionFeedback.msg" NAME_WE)
add_dependencies(action_server_generate_messages_py _action_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/stingray/stingray_ws/devel/share/action_server/msg/defGoal.msg" NAME_WE)
add_dependencies(action_server_generate_messages_py _action_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/stingray/stingray_ws/devel/share/action_server/msg/defResult.msg" NAME_WE)
add_dependencies(action_server_generate_messages_py _action_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/stingray/stingray_ws/devel/share/action_server/msg/defFeedback.msg" NAME_WE)
add_dependencies(action_server_generate_messages_py _action_server_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(action_server_genpy)
add_dependencies(action_server_genpy action_server_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS action_server_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/action_server)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/action_server
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET actionlib_msgs_generate_messages_cpp)
  add_dependencies(action_server_generate_messages_cpp actionlib_msgs_generate_messages_cpp)
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(action_server_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/action_server)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/action_server
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET actionlib_msgs_generate_messages_eus)
  add_dependencies(action_server_generate_messages_eus actionlib_msgs_generate_messages_eus)
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(action_server_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/action_server)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/action_server
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET actionlib_msgs_generate_messages_lisp)
  add_dependencies(action_server_generate_messages_lisp actionlib_msgs_generate_messages_lisp)
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(action_server_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/action_server)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/action_server
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET actionlib_msgs_generate_messages_nodejs)
  add_dependencies(action_server_generate_messages_nodejs actionlib_msgs_generate_messages_nodejs)
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(action_server_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/action_server)
  install(CODE "execute_process(COMMAND \"/usr/bin/python3\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/action_server\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/action_server
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET actionlib_msgs_generate_messages_py)
  add_dependencies(action_server_generate_messages_py actionlib_msgs_generate_messages_py)
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(action_server_generate_messages_py std_msgs_generate_messages_py)
endif()
