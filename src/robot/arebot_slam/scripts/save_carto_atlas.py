#! /usr/bin/python3

import rospy
from cartographer_ros_msgs.srv import FinishTrajectory, FinishTrajectoryRequest, WriteState, WriteStateRequest
import sys
import os

if __name__ == "__main__":
    
    remote_path = "/home/HwHiAiUser/ros-ws/maps"
    map_path = "/home/pi/arebot_ws/src/robot/arebot_navigation/maps"
    map_name = "carto_map"

    if len(sys.argv) > 1:
        map_name = sys.argv[1]

    rospy.init_node("save_carto")

    # rosservice call /finish_trajectory 0
    finish_client = rospy.ServiceProxy("/finish_trajectory", FinishTrajectory)
    finish_client.wait_for_service()

    req = FinishTrajectoryRequest()
    req.trajectory_id = 0
    response = finish_client.call(req)

    # write pbstream
    write_client = rospy.ServiceProxy("/write_state", WriteState)
    write_client.wait_for_service()

    req = WriteStateRequest()
    req.filename = f"{remote_path}/{map_name}.pbstream"
    response = write_client.call(req)

    # get pbstream file from atlas
    os.system(f"sshpass -p atlas scp atlas:{remote_path}/{map_name}.pbstream {map_path}")

    # convert pbstream to yaml+pgm
    os.system(f"rosrun cartographer_ros cartographer_pbstream_to_ros_map -map_filestem={map_path}/{map_name} -pbstream_filename={map_path}/{map_name}.pbstream -resolution=0.05")