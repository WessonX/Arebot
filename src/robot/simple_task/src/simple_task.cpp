#include "simple_task/simple_task.h"
#include "geometry_msgs/Twist.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"
#include "tf2/LinearMath/Matrix3x3.h"
#include <cmath>

namespace simple_task {

void SimpleTask::executeCallback(const SimpleTaskGoalConstPtr &goal) {
    ROS_INFO("goal received");

    std::string task_name = goal->task_name;
    if (task_name == "move") move(goal->args);
    else if (task_name == "rotate") rotate(goal->args);
    else {
        ROS_ERROR("Invalid task name: %s", task_name.c_str());
        result.final_progress = 0.0;
        action_server.setAborted(result);
    }
}

void SimpleTask::start() {
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

    // 暂时先把任务列表写死，以后可以改用更灵活的方式
    task_list.insert("move");
    task_list.insert("rotate");

    // 初始化odom_sub, twist_pub
    odom_sub = nh.subscribe<nav_msgs::Odometry>(odom_topic, 10, boost::bind(&SimpleTask::odomSubscribeCallback, this, _1));
    twist_pub = nh.advertise<geometry_msgs::Twist>(cmd_vel_topic, 10);

    // 初始化task_list_server
    task_list_server = nh.advertiseService<simple_task::TaskList::Request, simple_task::TaskList::Response>
                                           ("get_task_list", boost::bind(&SimpleTask::taskListCallback, this, _1, _2));

    // 启动action服务器
    action_server.start();
}

void SimpleTask::odomSubscribeCallback(const nav_msgs::Odometry::ConstPtr &odom) {
    pose = odom->pose.pose;
}

void SimpleTask::move(float distance) {
    ros::Rate rate(20);
    bool success = true;
    float dir = distance > 0 ? 1 : -1;

    geometry_msgs::Point start = pose.position;
    float cur_distance = 0.0;

    ROS_INFO("Start moving: %.3f meter", distance);

    while (std::abs(cur_distance - distance) > linear_error) {
        if (action_server.isPreemptRequested() || !ros::ok()) {
            ROS_INFO("%s preempted", action_name.c_str());
            action_server.setPreempted();
            twist_pub.publish(geometry_msgs::Twist());
            success = false;
            break;
        }

        // 发布速度话题
        geometry_msgs::Twist twist;
        twist.linear.x = linear_speed * dir;
        twist_pub.publish(twist);
        rate.sleep();

        // 计算当前移动距离
        geometry_msgs::Point cur_position = pose.position;
        float dx = cur_position.x - start.x;
        float dy = cur_position.y - start.y;
        cur_distance = std::sqrt(dx * dx + dy * dy) * dir;
        // ROS_INFO("current distance: %f meter", cur_distance);

        feedback.progress = cur_distance;
        action_server.publishFeedback(feedback);
    }

    // 停止运动
    twist_pub.publish(geometry_msgs::Twist());

    if (success) {
        result.final_progress = cur_distance;
        ROS_INFO("%s succeeded", action_name.c_str());
        action_server.setSucceeded(result);
    }
}

void SimpleTask::rotate(float angle) {
    if (angle < -360.0 || angle > 360.0) {
        ROS_ERROR("The rotation angle is limited to between -360.0 and 360.0");
        result.final_progress = 0.0;
        action_server.setAborted(result);
        return;
    }

    ros::Rate rate(20);
    bool success = true;
    float dir = angle > 0 ? 1 : -1;

    float start = getRotation();
    float cur_angle = 0.0;

    ROS_INFO("Start rotating: %.3f degree", angle);

    while (std::abs(cur_angle - angle) > angular_error) {
        if (action_server.isPreemptRequested() || !ros::ok()) {
            ROS_INFO("%s preempted", action_name.c_str());
            action_server.setPreempted();
            twist_pub.publish(geometry_msgs::Twist());
            success = false;
            break;
        }

        // 发布速度话题
        geometry_msgs::Twist twist;
        twist.angular.z = angular_speed * dir;
        twist_pub.publish(twist);
        rate.sleep();

        // 计算当前旋转角度
        cur_angle = getRotation() - start;
        if (cur_angle * dir < 0) cur_angle += 360.0 * dir;

        feedback.progress = cur_angle;
        action_server.publishFeedback(feedback);
    }

    // 停止运动
    twist_pub.publish(geometry_msgs::Twist());

    if (success) {
        result.final_progress = cur_angle;
        ROS_INFO("%s succeeded", action_name.c_str());
        action_server.setSucceeded(result);
    }
}

float SimpleTask::getRotation() {
    double roll, pitch, yaw;
    tf2::Quaternion q;
    tf2::fromMsg(pose.orientation, q);
    tf2::Matrix3x3(q).getRPY(roll, pitch, yaw);
    return yaw * 180.0 / 3.1415;
}

bool SimpleTask::taskListCallback(simple_task::TaskList::Request &req, simple_task::TaskList::Response &resp) {
    ROS_INFO("received request, sending task list");
    for (auto task : task_list) {
        resp.tasks.push_back(task);
    }

    return true;
}

}