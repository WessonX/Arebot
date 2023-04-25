#include <ctime>
#include <fstream>
#include <ros/package.h>
#include <ros/ros.h>
#include <sensor_msgs/CompressedImage.h>
#include <std_srvs/Empty.h>

std::string path;
ros::Subscriber subscriber;
bool wait_topic = true;

void callback(const sensor_msgs::CompressedImage::ConstPtr &msg) {
	subscriber.shutdown();
	wait_topic = false;

	std::ofstream os(path + std::to_string(time(NULL)) + ".jpg", std::ios::binary);
	os.write((const char *)msg->data.data(), msg->data.size());
	os.close();
}

int main(int argc, char **argv) {
	ros::init(argc, argv, "camera_shot");

	path = ros::package::getPath("patrolling_task") + "/images/";
	system(std::string("mkdir -p " + path).c_str());

	ros::NodeHandle node;
	subscriber = node.subscribe("/usb_cam/image_raw/compressed", 1, callback);

	while (wait_topic) {
		ros::spinOnce();
		ros::Duration(0.02).sleep();
	}

	ros::service::waitForService("/patrolling_task_done", 2000);
	ros::ServiceClient cs = node.serviceClient<std_srvs::Empty>("/patrolling_task_done");
	std_srvs::Empty srv;
	cs.call(srv);

	return 0;
}