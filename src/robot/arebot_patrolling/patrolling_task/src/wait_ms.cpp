#include <ctime>
#include <fstream>
#include <ros/ros.h>
#include <std_srvs/Empty.h>

int main(int argc, char **argv) {
	ros::init(argc, argv, "wait_ms");
	long ms = 20;

	if (argc < 2) {
		ROS_ERROR("missing arg");
		return 1;
	}

	ms = atol(argv[1]);

	ros::NodeHandle node;
	ros::Duration(ms / 1000.).sleep();

	ros::service::waitForService("/patrolling_task_done", 2000);
	ros::ServiceClient cs = node.serviceClient<std_srvs::Empty>("/patrolling_task_done");
	std_srvs::Empty srv;
	cs.call(srv);

	return 0;
}