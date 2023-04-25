#include "ros/ros.h"
#include <ros/package.h>
#include <fstream>

int main(int argc, char **argv) {

	ros::init(argc, argv, "arebot_patrolling_probelast");

	if (argc < 2) {
		ROS_ERROR("missing map name");
		return 1;
	}

	std::string configName = ros::package::getPath("arebot_patrolling") + "/patrolling.config";
	std::ifstream config(configName);
	if (!config) {
		ROS_ERROR("last config not exsit");
		return 1;
	}

	std::string mapName;
	std::getline(config, mapName);

	if (mapName.compare(argv[1]) != 0) {
		ROS_ERROR("current map differs to last map");
		return 1;
	}

	return 0;
}