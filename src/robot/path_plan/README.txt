功能：记录小车路径&小车将记录路径作为全局规划

path_plan为ros功能包；
依赖：Eigen3库，安装命令：sudo apt-get install libeigen3-dev
重要文件在src文件夹中：
pathRecord_node.cpp为记录路径的节点文件，其将小车路径记录为path.txt文件，供全局路径规划器读取；
path_planner.cpp为全局路径规划器（插件形式），将move_base的参数"base_global_planner"改为"path_planner/GlobalPlanner"即可使用；
附演示视频show_video.mp4；
存在问题：当路径存在间隔较小或交叉的部分时，小车会重新导航至先前的路径中，从而陷入局部循环，详见 问题.mp4；


具体使用流程：
先分别将bringup.launch和move_base.launch中的参数（全局路径文件的路径）"path"修改为想要保存的路径

启动gazebo仿真环境
roslaunch path_plan test_world.launch

启动slam,move_base和pathRecord_node节点
roslaunch path_plan bringup.launch

开始记录路径
rosservice call /recordStart 1

操控机器人走动
rosrun teleop_twist_keyboard teleop_twist_keyboard.py 

结束记录路径
rosservice call /recordStart 0

操控小车回到路径起点附近，指定任意目标点开始导航，小车会将记录路径作为全局路径进行导航；
