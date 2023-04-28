#include "ros/ros.h"
#include <fstream>


int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "");
	ros::init(argc, argv, "multiplier_reset");
	ros::NodeHandle n;

	// //获取乘数文件路径
	std::string filePath;
	n.getParam("multiplier_reset/path", filePath);

	n.setParam("mobile_base_controller/wheel_radius_multiplier", 1.0f);
	n.setParam("mobile_base_controller/wheel_separation_multiplier", 1.0f);

	// 将间距乘数写进文件
	std::ofstream outfile(filePath);
	if (!outfile) {
		ROS_ERROR("Failed to open file!");
		return false;
	}
	outfile << "mobile_base_controller:\n"
			<< "  wheel_radius_multiplier: "
			<< 1
			<< "\n  wheel_separation_multiplier: "
			<< 1
			<< "\n  temp_multiplier: "
			<< 1;

	outfile.close();
	return 0;
}