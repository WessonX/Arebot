#include <fstream>
#include <ros/package.h>
#include <ros/ros.h>

const int PARAMS_NUM = 5;
double params[PARAMS_NUM] = {0};
const std::string paramsName[PARAMS_NUM] = {
	"/move_base/TebLocalPlannerROS/xy_goal_tolerance",
	"/move_base/TebLocalPlannerROS/xy_goal_tolerance",
	"/move_base/TebLocalPlannerROS/min_obstacle_dist",
	"/move_base/global_costmap/inflation_layer/inflation_radius",
	"/move_base/local_costmap/inflation_layer/inflation_radius",
};

int main(int argc, char **argv) {
	ros::init(argc, argv, "arebot_navi_save_node");
	ros::NodeHandle node;

	for (int i = 0; i + 1 < argc && i < PARAMS_NUM; ++i) {
		params[i] = atof(argv[i + 1]);
		node.setParam(paramsName[i], params[i]);
	}

	std::string pre = ros::package::getPath("arebot_navigation");

	std::ofstream osPlaner(pre + "/params/planner/teb_local_planner_params_optimizing.yaml", std::ios::trunc);
	std::ofstream osCostmap(pre + "/params/costmap/costmap_common_params_optimizing.yaml", std::ios::trunc);

	osPlaner << "TebLocalPlannerROS:"
			 << "\n  xy_goal_tolerance: " << params[0]
			 << "\n  yaw_goal_tolerance: " << params[1]
			 << "\n  min_obstacle_dist: " << params[2];

	osCostmap << "inflation_layer:"
			  << "\n  inflation_radius: " << params[3]
			  << "\n  cost_scaling_factor: " << params[4];

	osPlaner.close();
	osCostmap.close();
	return 0;
}