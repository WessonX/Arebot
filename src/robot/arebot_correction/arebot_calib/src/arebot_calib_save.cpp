#include <fstream>
#include <ros/package.h>
#include <ros/ros.h>


int main(int argc, char **argv) {
	ros::init(argc, argv, "arebot_calib_save_node");

	ros::NodeHandle node;
	float l = 1, a = 1;
	if (!node.getParam("linear_scale", l)) {
		ROS_ERROR("can not get param linear_scale");
		return 1;
	}
	if (!node.getParam("angular_scale", a)) {
		ROS_ERROR("can not get param angular_scale");
		return 1;
	}


	std::string pre = ros::package::getPath("arebot_base");
	std::string fullPath = pre + "/params/calib.yaml";
	ROS_INFO("output file: %s", fullPath.c_str());

	std::ofstream os(fullPath, std::ios::trunc);

	os << "linear_scale: " << l << std::endl;
	os << "angular_scale: " << a;

	os.close();
	return 0;
}