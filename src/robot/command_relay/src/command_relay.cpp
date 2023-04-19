#include "command_relay/Cmd.h"
#include "httplib.h"
#include <ros/ros.h>

int port;

bool relayCallback(command_relay::CmdRequest &req, command_relay::CmdResponse &rsp) {
	httplib::Client cli("localhost", port);
	httplib::Result res = cli.Post(req.api,
								   req.json_data.c_str(),
								   req.json_data.length(),
								   "application/json");

	if (res.error() != httplib::Error(0)) {
		return false;
	}

	rsp.code = res->status;
	rsp.json_data = res->body;
	return true;
}

int main(int argc, char **argv) {
	ros::init(argc, argv, "command_relay_server");

	if (argc > 1) {
		port = atoi(argv[1]);
	}

	ros::NodeHandle node;
	ros::ServiceServer cs = node.advertiseService("/command_relay", relayCallback);

	ROS_INFO("command_relay is on, relaying post-json to localhost:%d", port);
	ros::spin();
	return 0;
}