#include "command_relay/Cmd.h"
#include <ros/ros.h>



int main(int argc, char **argv) {
	ros::init(argc, argv, "command_relay_test");

	ros::NodeHandle node;

	ros::service::waitForService("/command_relay");
	ros::ServiceClient sc = node.serviceClient<command_relay::Cmd>("/command_relay");

	command_relay::Cmd cmd;
	cmd.request.api = "/runSync";
	cmd.request.json_data = "{\"command\":\"ls\"}";

	if (sc.call(cmd)) {
		ROS_INFO("code:%d\ndata:%s", cmd.response.code, cmd.response.json_data.c_str());
	} else {
		ROS_ERROR("call service fail");
	}

	return 0;
}