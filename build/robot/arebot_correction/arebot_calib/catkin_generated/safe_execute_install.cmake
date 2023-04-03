execute_process(COMMAND "/home/pi/arebot_ws/build/robot/arebot_correction/arebot_calib/catkin_generated/python_distutils_install.sh" RESULT_VARIABLE res)

if(NOT res EQUAL 0)
  message(FATAL_ERROR "execute_process(/home/pi/arebot_ws/build/robot/arebot_correction/arebot_calib/catkin_generated/python_distutils_install.sh) returned error code ")
endif()
