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
    std::string action_name;
    actionlib::SimpleActionServer<SimpleMovementAction> action_server;
    
    // action服务器回传信息
    SimpleMovementFeedback feedback;
    SimpleMovementResult result;

    // 相关话题的订阅和发布
    ros::Subscriber odom_sub;
    ros::Publisher twist_pub;
    geometry_msgs::Pose pose;

    // 控制参数
    std::string odom_topic;     // 里程计话题名
    std::string cmd_vel_topic;  // 速度话题名
    float linear_speed;         // 线速度   m/s
    float angular_speed;        // 角速度   rad/s
    float linear_error;         // 距离误差 m
    float angular_error;        // 角度误差 度


public:

    SimpleMovement() = default;
    SimpleMovement(ros::NodeHandle nh, std::string name) :
        nh(nh),
        action_name(name), 
        action_server(nh, name, boost::bind(&SimpleMovement::executeCallback, this, _1), false) {}

    // 启动服务
    void start();

    // action服务器执行回调
    void executeCallback(const SimpleMovementGoalConstPtr &goal);

    // 里程计消息订阅的回调函数
    void odomSubscribeCallback(const nav_msgs::Odometry::ConstPtr &odom);

    // 移动和旋转控制
    void move(float distance);
    void rotate(float angle);

};

}

#endif  // _SIMPLE_MOVEMENT_H