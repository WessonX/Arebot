#ifndef _CMD_VEL_CALIB
#define _CMD_VEL_CALIB

#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "std_msgs/Float64.h"

class CmdVelCalib {
public:
    ros::NodeHandle nh;

    CmdVelCalib(ros::NodeHandle nh);

    // origin /cmd_vel topic subcriber
    ros::Subscriber cmd_vel_subscriber;

    // new /calibed_cmd_vel topic publisher
    ros::Publisher calibed_cmd_vel_publisher;

    // subscriber for angular_scale and linear_scale
    ros::Subscriber angular_scale_subscriber;
    ros::Subscriber linear_scale_subscriber;

    // param
    double angular_scale;
    double linear_scale;

    // callback functions
    void cmdVelSubCallback(const geometry_msgs::Twist::ConstPtr& twist);

    void angularScaleSetCallback(const std_msgs::Float64::ConstPtr& new_scale);

    void linearScaleSetCallback(const std_msgs::Float64::ConstPtr& new_scale);
};


#endif  // _CMD_VEL_CALIB