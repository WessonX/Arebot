#include "ros/ros.h"
#include "simple_movement/simple_movement.h"

int main(int argc, char *argv[]) {
    ros::init(argc, argv, "simple_movement_node");
    simple_movement::SimpleMovement sm("simple_move_control");
    ros::spin();

    return 0;
}