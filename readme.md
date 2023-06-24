## Install

项目依赖于以下ROS Package，请确保机器人端安装好依赖项
- rosbridge
- tf2_web_republisher
- web_video_server
- yocs_virtual_sensor
- compressed_image_transport
执行以下代码安装
```sh
sudo apt-get install ros-$ROS_DISTRO-rosbridge-suite ros-$ROS_DISTRO-tf2-web-republisher ros-$ROS_DISTRO-web-video-server ros-$ROS_DISTRO-yocs-virtual-sensor ros-$ROS_DISTRO-compressed-image-transport
```

## Usage

这个仓库是机器人端的ROS代码。拿到代码后，先执行

```
catkin_make
```

编译后，在仓库根目录下执行

```
source ./devel/setup.bash
```

刷新环境变量后，执行

```
roslaunch arebot_bringup arebot.launch
```

## Others
相关代码链接
- command_relay功能包
`arebot_ws/src/robot/command_relay/CommandServer`是[另一项目](https://git.scut.mcurobot.com/haojie/commandserver)的编译产物