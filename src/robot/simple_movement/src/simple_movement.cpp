#include "simple_movement/simple_movement.h"
#include "geometry_msgs/Twist.h"
#include <cmath>

namespace simple_movement {

void SimpleMovement::executeCallback(const SimpleMovementGoalConstPtr &goal) {
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

    while (std::abs(cur_distance - distance) > 0.03) {
        if (action_server.isPreemptRequested() || !ros::ok()) {
            ROS_INFO("%s preempted", action_name.c_str());
            action_server.setPreempted();
            twist_pub.publish(geometry_msgs::Twist());
            success = false;
            break;
        }

        geometry_msgs::Twist twist;
        twist.linear.x = 0.5;
        twist_pub.publish(twist);
        rate.sleep();

        geometry_msgs::Point cur_position = pose.position;
        float dx = cur_position.x - start.x;
        float dy = cur_position.y - start.y;
        cur_distance = std::sqrt(dx * dx + dy * dy);

        feedback.progress = cur_distance;
        action_server.publishFeedback(feedback);
    }

    if (success) {
        result.final_progress = distance;
        ROS_INFO("%s succeeded", action_name.c_str());
        action_server.setSucceeded(result);
    }
}

void SimpleMovement::rotate(float angle) {
    
}

}