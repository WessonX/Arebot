#!/bin/bash



rosservice call /finish_trajectory 0
rosservice call /write_state "filename: '/home/HwHiAiUser/ros-ws/maps/test.pbstream'"
sshpass -p atlas scp atlas:/home/HwHiAiUser/ros-ws/maps/test.pbstream /home/pi/arebot_ws/src/robot/arebot_navigation/maps/test.pbstream
rosrun cartographer_ros cartographer_pbstream_to_ros_map -map_filestem=/home/pi/arebot_ws/src/robot/arebot_navigation/maps/test -pbstream_filename=/home/pi/arebot_ws/src/robot/arebot_navigation/maps/test.pbstream -resolution=0.05

