#include <fstream>
#include <ros/package.h>
#include <ros/ros.h>

void parse2cout(std::ifstream &is) {
	static bool needPreComma = false;
	std::string name;
	double d;
	is >> name;
	while (is >> name >> d) {
		if (needPreComma) {
			std::cout << ',';
		}
		needPreComma = true;
		std::cout << "\"" << name.substr(0, name.length() - 1) << "\":" << d;
	}
}

int main(int argc, char **argv) {
	ros::init(argc, argv, "arebot_navi_get_node");
	ros::NodeHandle node;

	std::string pre = ros::package::getPath("arebot_navigation");
	std::ifstream isPlaner(pre + "/params/planner/teb_local_planner_params_optimizing.yaml");
	std::ifstream isCostmap(pre + "/params/costmap/costmap_common_params_optimizing.yaml");

	if (!isPlaner.is_open()) {
		std::cerr << "fail to open teb_local_planner_params_optimizing.yaml" << std::endl;
		exit(1);
	}
	if (!isCostmap.is_open()) {
		std::cerr << "fail to open costmap_common_params_optimizing.yaml" << std::endl;
		exit(1);
	}

	std::cout << "{";
	parse2cout(isPlaner);
	parse2cout(isCostmap);
	std::cout << "}";

	isPlaner.close();
	isCostmap.close();
	return 0;
}