#include "cmd_vel_calib/cmd_vel_calib.h"

CmdVelCalib::CmdVelCalib(ros::NodeHandle nh){
    this->nh = nh;

    // init params
    if (!nh.getParam("/angular_scale", angular_scale))
        angular_scale = 1.0;
    if (!nh.getParam("/linear_scale", linear_scale))
        linear_scale = 1.0;

    // init and register callbacks
    cmd_vel_subscriber = nh.subscribe<geometry_msgs::Twist>("/cmd_vel", 10, 
        boost::bind(&CmdVelCalib::cmdVelSubCallback, this, _1));

    calibed_cmd_vel_publisher = nh.advertise<geometry_msgs::Twist>("/calibed_cmd_vel", 10);

    angular_scale_subscriber = nh.subscribe<std_msgs::Float64>("/set_angular_scale", 10, 
        boost::bind(&CmdVelCalib::angularScaleSetCallback, this, _1));

    linear_scale_subscriber = nh.subscribe<std_msgs::Float64>("/set_linear_scale", 10, 
        boost::bind(&CmdVelCalib::linearScaleSetCallback, this, _1));
}

void CmdVelCalib::cmdVelSubCallback(const geometry_msgs::Twist::ConstPtr& twist) {
    geometry_msgs::Twist new_twist;
    new_twist.linear.x = twist->linear.x / linear_scale;
    new_twist.linear.y = twist->linear.y / linear_scale;
    new_twist.angular.z = twist->angular.z / angular_scale;

    calibed_cmd_vel_publisher.publish(new_twist);
}

void CmdVelCalib::angularScaleSetCallback(const std_msgs::Float64::ConstPtr& new_scale) {
    angular_scale = new_scale->data;
    ros::param::set("/angular_scale", angular_scale);
    ROS_INFO("angular_scale is set to %f", angular_scale);
}

void CmdVelCalib::linearScaleSetCallback(const std_msgs::Float64::ConstPtr& new_scale) {
    linear_scale = new_scale->data;
    ros::param::set("/linear_scale", linear_scale);
    ROS_INFO("linear_scale is set to %f", linear_scale);
}