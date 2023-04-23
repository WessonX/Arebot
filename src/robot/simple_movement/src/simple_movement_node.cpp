#include "ros/ros.h"
#include "simple_movement/simple_movement.h"

int main(int argc, char *argv[]) {
    ros::init(argc, argv, "simple_movement_node");

    ros::NodeHandle nh("~");
    simple_movement::SimpleMovement sm(nh, "simple_movement");
    sm.start();
    
    ros::spin();

    return 0;
}