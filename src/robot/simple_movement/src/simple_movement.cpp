#include "simple_movement/simple_movement.h"
#include "geometry_msgs/Twist.h"
#include <cmath>

namespace simple_movement {

void SimpleMovement::executeCallback(const SimpleMovementGoalConstPtr &goal) {
    ROS_INFO("goal received");

    if (goal->distance != 0.0 && goal->angle != 0.0) {
        ROS_ERROR("Cannot move and rotate at the same time!");
        result.final_progress = 0.0;
        action_server.setAborted(result);
    }
    else if (goal->distance == 0.0 && goal->angle == 0.0) {
        ROS_WARN("Invalid arguments: both angle and distance are zero");
        result.final_progress = 0.0;
        action_server.setAborted(result);
    }
    else {
        if (goal->distance != 0) move(goal->distance);
        else rotate(goal->angle);
    }
}

void SimpleMovement::start() {
    // 初始化控制参数
    if (!nh.getParam("odom_topic", odom_topic))
        odom_topic = "/mobile_base_controller/odom";
    if (!nh.getParam("cmd_vel_topic", cmd_vel_topic))
        cmd_vel_topic = "/cmd_vel";
    if (!nh.getParam("linear_speed", linear_speed))
        linear_speed = 0.2;
    if (!nh.getParam("angular_speed", angular_speed))
        angular_speed = 0.3;
    if (!nh.getParam("linear_error", linear_error))
        linear_error = 0.015;
    if (!nh.getParam("angular_error", angular_error))
        angular_error = 5;

    // 初始化odom_sub, twist_pub
    odom_sub = nh.subscribe<nav_msgs::Odometry>(odom_topic, 10, boost::bind(&SimpleMovement::odomSubscribeCallback, this, _1));
    twist_pub = nh.advertise<geometry_msgs::Twist>(cmd_vel_topic, 10);

    // 启动action服务器
    action_server.start();
}

void SimpleMovement::odomSubscribeCallback(const nav_msgs::Odometry::ConstPtr &odom) {
    pose = odom->pose.pose;
}

void SimpleMovement::move(float distance) {
    ros::Rate rate(20);
    bool success = true;

    geometry_msgs::Point start = pose.position;
    // float rest = distance;
    // geometry_msgs::Point last_position = start;
    float cur_distance = 0.0;

    ROS_INFO("Start moving: %f meter", distance);

    while (std::abs(cur_distance - distance) > linear_error) {
        if (action_server.isPreemptRequested() || !ros::ok()) {
            ROS_INFO("%s preempted", action_name.c_str());
            action_server.setPreempted();
            twist_pub.publish(geometry_msgs::Twist());
            success = false;
            break;
        }

        geometry_msgs::Twist twist;
        twist.linear.x = linear_speed;
        twist_pub.publish(twist);
        rate.sleep();

        geometry_msgs::Point cur_position = pose.position;
        float dx = cur_position.x - start.x;
        float dy = cur_position.y - start.y;
        cur_distance = std::sqrt(dx * dx + dy * dy);
        // ROS_INFO("current distance: %f meter", cur_distance);

        feedback.progress = cur_distance;
        action_server.publishFeedback(feedback);
    }

    twist_pub.publish(geometry_msgs::Twist());

    if (success) {
        result.final_progress = cur_distance;
        ROS_INFO("%s succeeded", action_name.c_str());
        action_server.setSucceeded(result);
    }
}

void SimpleMovement::rotate(float angle) {
    
}

}