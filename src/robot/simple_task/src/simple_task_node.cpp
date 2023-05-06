#include "ros/ros.h"
#include "simple_task/simple_task.h"

int main(int argc, char *argv[]) {
    ros::init(argc, argv, "simple_task_node");

    ros::NodeHandle nh("~");
    simple_task::SimpleTask st(nh, "simple_task");
    st.start();
    
    ros::spin();

    return 0;
}