#! /usr/bin/env python

import rospy
from dynamic_reconfigure.srv import Reconfigure, ReconfigureRequest
from dynamic_reconfigure.msg import BoolParameter, DoubleParameter
from std_msgs.msg import Float64

if __name__ == "__main__":
    rospy.init_node("test", anonymous=False)

    client = rospy.ServiceProxy("/calibrate_linear/set_parameters", Reconfigure)
    client.wait_for_service()

    linear_scale_pub = rospy.Publisher("/set_linear_scale", Float64, queue_size=10)

    #
    test_distance = 1.0
    speed = 0.15
    tolerance = 0.01
    linear_scale = 2.0

    req_config = ReconfigureRequest()
    req_config.config.doubles = [
        DoubleParameter("test_distance", test_distance),
        DoubleParameter("speed", speed),
        DoubleParameter("tolerance", tolerance),
        DoubleParameter("odom_linear_scale_correction", linear_scale)
    ]
    req_config.config.bools = [
        BoolParameter("start_test", True)
    ]

    linear_scale_msg = Float64()
    linear_scale_msg.data = linear_scale

    #
    client.call(req_config)

    linear_scale_pub.publish(linear_scale_msg)
    rospy.set_param("linear_scale", linear_scale)