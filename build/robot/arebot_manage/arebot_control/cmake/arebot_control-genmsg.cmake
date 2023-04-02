# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "arebot_control: 0 messages, 1 services")

set(MSG_I_FLAGS "")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(arebot_control_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/pi/arebot_ws/src/robot/arebot_manage/arebot_control/srv/BusOp.srv" NAME_WE)
add_custom_target(_arebot_control_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "arebot_control" "/home/pi/arebot_ws/src/robot/arebot_manage/arebot_control/srv/BusOp.srv" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages

### Generating Services
_generate_srv_cpp(arebot_control
  "/home/pi/arebot_ws/src/robot/arebot_manage/arebot_control/srv/BusOp.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/arebot_control
)

### Generating Module File
_generate_module_cpp(arebot_control
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/arebot_control
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(arebot_control_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(arebot_control_generate_messages arebot_control_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/pi/arebot_ws/src/robot/arebot_manage/arebot_control/srv/BusOp.srv" NAME_WE)
add_dependencies(arebot_control_generate_messages_cpp _arebot_control_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(arebot_control_gencpp)
add_dependencies(arebot_control_gencpp arebot_control_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS arebot_control_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages

### Generating Services
_generate_srv_eus(arebot_control
  "/home/pi/arebot_ws/src/robot/arebot_manage/arebot_control/srv/BusOp.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/arebot_control
)

### Generating Module File
_generate_module_eus(arebot_control
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/arebot_control
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(arebot_control_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(arebot_control_generate_messages arebot_control_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/pi/arebot_ws/src/robot/arebot_manage/arebot_control/srv/BusOp.srv" NAME_WE)
add_dependencies(arebot_control_generate_messages_eus _arebot_control_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(arebot_control_geneus)
add_dependencies(arebot_control_geneus arebot_control_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS arebot_control_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages

### Generating Services
_generate_srv_lisp(arebot_control
  "/home/pi/arebot_ws/src/robot/arebot_manage/arebot_control/srv/BusOp.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/arebot_control
)

### Generating Module File
_generate_module_lisp(arebot_control
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/arebot_control
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(arebot_control_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(arebot_control_generate_messages arebot_control_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/pi/arebot_ws/src/robot/arebot_manage/arebot_control/srv/BusOp.srv" NAME_WE)
add_dependencies(arebot_control_generate_messages_lisp _arebot_control_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(arebot_control_genlisp)
add_dependencies(arebot_control_genlisp arebot_control_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS arebot_control_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages

### Generating Services
_generate_srv_nodejs(arebot_control
  "/home/pi/arebot_ws/src/robot/arebot_manage/arebot_control/srv/BusOp.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/arebot_control
)

### Generating Module File
_generate_module_nodejs(arebot_control
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/arebot_control
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(arebot_control_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(arebot_control_generate_messages arebot_control_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/pi/arebot_ws/src/robot/arebot_manage/arebot_control/srv/BusOp.srv" NAME_WE)
add_dependencies(arebot_control_generate_messages_nodejs _arebot_control_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(arebot_control_gennodejs)
add_dependencies(arebot_control_gennodejs arebot_control_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS arebot_control_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages

### Generating Services
_generate_srv_py(arebot_control
  "/home/pi/arebot_ws/src/robot/arebot_manage/arebot_control/srv/BusOp.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/arebot_control
)

### Generating Module File
_generate_module_py(arebot_control
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/arebot_control
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(arebot_control_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(arebot_control_generate_messages arebot_control_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/pi/arebot_ws/src/robot/arebot_manage/arebot_control/srv/BusOp.srv" NAME_WE)
add_dependencies(arebot_control_generate_messages_py _arebot_control_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(arebot_control_genpy)
add_dependencies(arebot_control_genpy arebot_control_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS arebot_control_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/arebot_control)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/arebot_control
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/arebot_control)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/arebot_control
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/arebot_control)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/arebot_control
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/arebot_control)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/arebot_control
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/arebot_control)
  install(CODE "execute_process(COMMAND \"/usr/bin/python2\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/arebot_control\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/arebot_control
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
