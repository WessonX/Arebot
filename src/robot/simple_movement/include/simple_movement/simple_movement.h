#ifndef _SIMPLE_MOVEMENT_H
#define _SIMPLE_MOVEMENT_H

#include "ros/ros.h"
#include "actionlib/server/simple_action_server.h"
#include "simple_movement/SimpleMovementAction.h"
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/Pose.h"
#include <string>

namespace simple_movement {

class SimpleMovement {
private:
    ros::NodeHandle nh;
    actionlib::SimpleActionServer<SimpleMovementAction> action_server;
    
    std::string action_name;
    SimpleMovementFeedback feedback;
    SimpleMovementResult result;

    ros::Subscriber odom_sub;
    ros::Publisher twist_pub;
    geometry_msgs::Pose pose;

public:

    SimpleMovement() = default;
    SimpleMovement(std::string name) :
        action_name(name), 
        action_server(nh, name, boost::bind(&SimpleMovement::executeCallback, this, _1), false),
        odom_sub(nh.subscribe<nav_msgs::Odometry>("/odom", 10, boost::bind(&SimpleMovement::odomSubscribeCallback, this, _1))),
        twist_pub(nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10)) {
        action_server.start();
    }

    void executeCallback(const SimpleMovementGoalConstPtr &goal);
    void odomSubscribeCallback(const nav_msgs::Odometry::ConstPtr &odom);

    void move(float distance);
    void rotate(float angle);

};

}

#endif  // _SIMPLE_MOVEMENT_H