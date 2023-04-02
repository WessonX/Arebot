# generated from catkin/cmake/template/pkg.context.pc.in
CATKIN_PACKAGE_PREFIX = ""
PROJECT_PKG_CONFIG_INCLUDE_DIRS = "${prefix}/include".split(';') if "${prefix}/include" != "" else []
PROJECT_CATKIN_DEPENDS = "hardware_interface;joint_state_controller;nodelet;roscpp;arebot_bus_proto".replace(';', ' ')
PKG_CONFIG_LIBRARIES_WITH_PREFIX = "-larebot_base".split(';') if "-larebot_base" != "" else []
PROJECT_NAME = "arebot_base"
PROJECT_SPACE_DIR = "/home/pi/arebot_ws/install"
PROJECT_VERSION = "0.0.0"
