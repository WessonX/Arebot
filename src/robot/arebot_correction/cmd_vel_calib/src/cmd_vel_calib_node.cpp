#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "cmd_vel_calib/cmd_vel_calib.h"

int main(int argc, char *argv[]) {
    ros::init(argc, argv, "cmd_vel_calib_node");
    ros::NodeHandle nh;

    CmdVelCalib cmd_vel_calib(nh);
    ros::spin();
    return 0;
}