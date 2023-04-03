#! /usr/bin/env python

import rospy
from dynamic_reconfigure.srv import Reconfigure, ReconfigureRequest
from dynamic_reconfigure.msg import BoolParameter, DoubleParameter
from std_msgs.msg import Float64

if __name__ == "__main__":
    rospy.init_node("test", anonymous=False)

    client = rospy.ServiceProxy("/calibrate_angular/set_parameters", Reconfigure)
    client.wait_for_service()

    angular_scale_pub = rospy.Publisher("/set_angular_scale", Float64, queue_size=10)

    #
    test_angle = 360.0
    speed = 0.4
    tolerance = 1.0
    angular_scale = 1.0

    req_config = ReconfigureRequest()
    req_config.config.doubles = [
        DoubleParameter("test_angle", test_angle),
        DoubleParameter("speed", speed),
        DoubleParameter("tolerance", tolerance),
        DoubleParameter("odom_angular_scale_correction", angular_scale)
    ]
    req_config.config.bools = [
        BoolParameter("start_test", True)
    ]

    angular_scale_msg = Float64()
    angular_scale_msg.data = angular_scale
    
    #
    client.call(req_config)

    angular_scale_pub.publish(angular_scale_msg)
    rospy.set_param("/angular_scale", angular_scale)