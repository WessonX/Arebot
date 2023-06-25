#include "command_relay/Cmd.h"
#include "ros/ros.h"
#include <actionlib/client/simple_action_client.h>
#include <fstream>
#include <move_base_msgs/MoveBaseAction.h>
#include <ros/package.h>
#include <std_srvs/Empty.h>
#include <vector>

bool wait_done = true;
bool task_done_callback(std_srvs::Empty::Request &req, std_srvs::Empty::Response &rsp);
void action_done_cb(const actionlib::SimpleClientGoalState &state, const move_base_msgs::MoveBaseResultConstPtr &result) {}
void action_active_cb() {}
void action_feedback_cb(const move_base_msgs::MoveBaseFeedbackConstPtr &feedback) {}

int main(int argc, char **argv) {
	ros::init(argc, argv, "arebot_patrolling_node");
	ros::NodeHandle node;

	std::string configName = ros::package::getPath("arebot_patrolling") + "/patrolling.config";

	// read config
	std::string mapName;
	int repeatNum;

	std::ifstream config(configName);
	if (!config.is_open()) {
		ROS_ERROR("config not exist");
		return 1;
	}

	std::getline(config, mapName);
	config >> repeatNum;
	if (repeatNum <= 0) {
		repeatNum = INT_MAX;
	}

	std::vector<move_base_msgs::MoveBaseGoal> listGoal;
	std::vector<std::string> listCmd;
	int listNum = 0;

	double x, y, z, w;
	std::string cmd;
	while (config >> x >> y >> z >> w) {
		move_base_msgs::MoveBaseGoal goal;
		goal.target_pose.header.frame_id = "map";
		goal.target_pose.pose.position.x = x;
		goal.target_pose.pose.position.y = y;
		goal.target_pose.pose.position.z = 0;
		goal.target_pose.pose.orientation.x = 0;
		goal.target_pose.pose.orientation.y = 0;
		goal.target_pose.pose.orientation.z = z;
		goal.target_pose.pose.orientation.w = w;

		config.get();
		std::getline(config, cmd);

		listGoal.emplace_back(goal);
		listCmd.emplace_back(cmd);
		listNum++;
	}
	config.close();

	// for (int i = 0; i < listNum; ++i) {
	// 	ROS_INFO("%f %f %f %f",
	// 			 listGoal[i].target_pose.pose.position.x,
	// 			 listGoal[i].target_pose.pose.position.y,
	// 			 listGoal[i].target_pose.pose.orientation.z,
	// 			 listGoal[i].target_pose.pose.orientation.w);
	// 	ROS_INFO(listCmd[i].c_str());
	// }
	// return 0;

	actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> ma("/move_base", true);
	ma.waitForServer();

	ros::service::waitForService("/command_relay");
	ros::ServiceClient cmdSrv = node.serviceClient<command_relay::Cmd>("/command_relay");

	ros::ServiceServer cs = node.advertiseService("/patrolling_task_done", task_done_callback);

	while (repeatNum--) {
		for (int i = 0; i < listNum; ++i) {
			// send goal and wait
			ma.sendGoal(listGoal[i],
						&action_done_cb,
						&action_active_cb,
						&action_feedback_cb);
			ma.waitForResult();

			// do task
			command_relay::Cmd pre_cancel;
			pre_cancel.request.api = "/cancel";
			pre_cancel.request.json_data = "{\"tag\":\"patrolling_task\"}";
			cmdSrv.call(pre_cancel);

			command_relay::Cmd task;
			task.request.api = "/run";
			task.request.json_data = "{"
									 "\"tag\":\"patrolling_task\","
									 "\"command\":\"";
			task.request.json_data += listCmd[i] + "\"}";
			cmdSrv.call(task);

			// wait
			while (wait_done) {
				ros::spinOnce();
				ros::Duration(0.02).sleep();
			}
			wait_done = true;
		}
	}

	return 0;
}

bool task_done_callback(std_srvs::Empty::Request &req, std_srvs::Empty::Response &rsp) {
	wait_done = false;
	return true;
}