#include <iostream>
#include "ros/ros.h"
#include "cartographer_ros_msgs/FinishTrajectory.h"
#include "cartographer_ros_msgs/WriteState.h"

int main(int argc, char *argv[]) {

    if (argc == 1) {
        std::cerr << "incorrect arguments: " << argc << std::endl;
        return 1;
    }

    ros::init(argc, argv, "save_carto");
    ros::NodeHandle nHandle;
    ros::ServiceClient finish_client = nHandle.serviceClient<cartographer_ros_msgs::FinishTrajectory>("/finish_trajectory");
    ros::ServiceClient write_client = nHandle.serviceClient<cartographer_ros_msgs::WriteState>("/write_state");

    cartographer_ros_msgs::FinishTrajectory finish_msg;
    finish_msg.request.trajectory_id = 0;

    cartographer_ros_msgs::WriteState write_msg;
    write_msg.request.filename = std::string(argv[1]) + ".pbstream";

    finish_client.call(finish_msg);
    write_client.call(write_msg);

    return 0;
}