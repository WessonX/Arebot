#include "ros/ros.h"
#include "sensor_msgs/Image.h"
#include "image_transport/image_transport.h"
#include "atlas_cam/net_server.h"
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <vector>

int main(int argc, char *argv[]) {
    ros::init(argc, argv, "atlas_cam");
    ros::NodeHandle nHandle;

    image_transport::ImageTransport it(nHandle);
    image_transport::Publisher image_pub = it.advertise("/atlas_cam/image_raw", 1);

    ros::Rate rate(1);

    Server server;
    server.Start();

    while (ros::ok()) {
        int size = server.GetSize();
        if (size == -1) return -1;

        unsigned char *buf = new unsigned char[size];
        server.Receive(buf, size);

        std::vector<unsigned char> data(buf, buf + size);
        // verify jpg data
        if (!(data[0] == 0xFF && data[1] == 0xD8 && data[2] == 0xFF)) {
            data.insert(data.begin(), 0xFF);
            data.insert(data.begin(), 0xD8);
            data.insert(data.begin(), 0xFF);
        }
        cv::Mat image = cv::imdecode(data, cv::ImreadModes::IMREAD_COLOR);
        sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", image).toImageMsg();

        image_pub.publish(msg);
        ros::spinOnce();
        
        delete buf;
    }
}