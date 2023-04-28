#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include <fstream>
#include <geometry_msgs/Twist.h>
#include <ros/package.h>
#include <sensor_msgs/Imu.h>

double ideal_angular_v = 0;
double actual_angular_v = 0;

bool only_show_once = true;
void saveIdealAngular(const geometry_msgs::Twist::ConstPtr &msg) {
	ideal_angular_v = msg->angular.z;
	if (only_show_once) {
		ROS_INFO("ideal_angular_v: %f", ideal_angular_v);
		only_show_once = false;
	}
}

void saveActualAngular(const std_msgs::Float64::ConstPtr &msg) {
	actual_angular_v = msg->data;
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "");
	ros::init(argc, argv, "multiplier_separation");
	ros::NodeHandle n;

	ros::Subscriber ideal_angular_sub = n.subscribe<geometry_msgs::Twist>("/cmd_vel", 1, saveIdealAngular);
	ros::Subscriber actual_angular_sub = n.subscribe<std_msgs::Float64>("/arebot_correction_wheel/mean_angular_v", 1, saveActualAngular);

	ROS_INFO("please start spinning in place!");

	// 订阅理论速度和实际速度
	while (n.ok()) {
		ros::spinOnce();
		if (ideal_angular_v != 0 && actual_angular_v != 0)
			break;
	}

	// //获取乘数文件路径
	std::string filePath;
	n.getParam("multiplier_separation/path", filePath);

	// 从临时参数取值
	double radius_multiplier = 1.0;
	n.getParam("mobile_base_controller/temp_multiplier", radius_multiplier);

	// 计算车轮间距乘数
	double separation_multiplier = radius_multiplier * (ideal_angular_v / actual_angular_v);
	ROS_INFO("the wheel's separation multiplier is:%f", separation_multiplier);

	if (!finite(separation_multiplier)) {
		ROS_ERROR("the wheel's separation multiplier is not finit, set 1");
		separation_multiplier = 1;
	}

	n.setParam("mobile_base_controller/wheel_radius_multiplier", radius_multiplier);
	n.setParam("mobile_base_controller/wheel_separation_multiplier", separation_multiplier);

	// 将间距乘数写进文件
	std::ofstream outfile(filePath);
	if (!outfile) {
		ROS_WARN("Failed to open file!");
		return false;
	}
	outfile << "mobile_base_controller:\n"
			<< "  wheel_radius_multiplier: "
			<< radius_multiplier
			<< "\n  wheel_separation_multiplier: "
			<< separation_multiplier
			<< "\n  temp_multiplier: "
			<< 1;

	outfile.close();
	return 0;
}