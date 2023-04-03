# generated from catkin/cmake/template/pkg.context.pc.in
CATKIN_PACKAGE_PREFIX = ""
PROJECT_PKG_CONFIG_INCLUDE_DIRS = "${prefix}/include".split(';') if "${prefix}/include" != "" else []
PROJECT_CATKIN_DEPENDS = "nodelet;roscpp;sensor_msgs;arebot_control".replace(';', ' ')
PKG_CONFIG_LIBRARIES_WITH_PREFIX = "-lszar_ultrasonic".split(';') if "-lszar_ultrasonic" != "" else []
PROJECT_NAME = "szar_ultrasonic"
PROJECT_SPACE_DIR = "/home/pi/arebot_ws/install"
PROJECT_VERSION = "0.0.0"
