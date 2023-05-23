cmake_minimum_required(VERSION 2.8.3)

project(arebot_calib)

find_package(catkin REQUIRED COMPONENTS dynamic_reconfigure roscpp roslib)

catkin_python_setup()

generate_dynamic_reconfigure_options(cfg/CalibrateAngular.cfg cfg/CalibrateLinear.cfg)

catkin_package(CATKIN_DEPENDS dynamic_reconfigure)

include_directories(${catkin_INCLUDE_DIRS})

add_executable(${PROJECT_NAME}_save src/arebot_calib_save.cpp)
add_executable(arebot_navi_save src/arebot_navi_save.cpp)

target_link_libraries(${PROJECT_NAME}_save ${catkin_LIBRARIES})
target_link_libraries(arebot_navi_save ${catkin_LIBRARIES})