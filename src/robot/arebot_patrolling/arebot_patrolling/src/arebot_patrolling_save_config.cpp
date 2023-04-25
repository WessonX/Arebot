#include <fstream>
#include <ros/package.h>
#include <ros/ros.h>

int main(int argc, char **argv) {
	ros::init(argc, argv, "arebot_patrolling_save_config");
	ros::NodeHandle node;

	std::string configName = ros::package::getPath("arebot_patrolling") + "/patrolling.config";
	if (argc < 2) {
		ROS_ERROR("missing arg");
		return 1;
	}

	std::ofstream config(configName, std::ios::trunc);
	for (int i = 1; i < argc; ++i) {
		config << argv[i] << " ";
	}
	config.close();
	return 0;
}