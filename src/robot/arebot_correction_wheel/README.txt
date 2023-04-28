arebot_correction2为标定车轮半径及间距的功能包；
必须先标定车轮半径再标定车轮间距；

//运行半径标定节点
roslaunch arebot_correction2 radius_multiplier.launch

//通过话题传递实际测量距离
rosrun arebot_correction2 pub_dist_for_test

//运行间距标定节点
roslaunch arebot_correction2 separation_multiplier.launch

运行完毕后，车轮半径和间距的乘数依次保存在multiplier.txt中；
