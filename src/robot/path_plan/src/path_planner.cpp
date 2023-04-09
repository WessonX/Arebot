 #include <pluginlib/class_list_macros.h>
 #include <tf/transform_datatypes.h>
 #include <fstream>
 #include <boost/regex.hpp>
 #include <boost/bind.hpp>
 #include "path_planner.h"

 //register this planner as a BaseGlobalPlanner plugin
 PLUGINLIB_EXPORT_CLASS(path_planner::GlobalPlanner, nav_core::BaseGlobalPlanner)

 using namespace std;

 //Default Constructor
 namespace path_planner {

 GlobalPlanner::GlobalPlanner (){
   
 }
 
 vector<string> split(string str, string s) {
    boost::regex reg(s.c_str());
    vector<std::string> vec;
    boost::sregex_token_iterator it(str.begin(),str.end(),reg,-1);
    boost::sregex_token_iterator end;
    while(it!=end)
    {
        vec.push_back(*it++);
    }
    return vec;
 }

 GlobalPlanner::GlobalPlanner(std::string name, costmap_2d::Costmap2DROS* costmap_ros){
   initialize(name, costmap_ros);

 }


 void GlobalPlanner::initialize(std::string name, costmap_2d::Costmap2DROS* costmap_ros){
   ROS_WARN("initialize-------");

   try{
      pluginlib::ClassLoader<nav_core::BaseGlobalPlanner> navfn_planner_loader("nav_core", "nav_core::BaseGlobalPlanner");
      navfn_planner = navfn_planner_loader.createInstance("navfn/NavfnROS");
      navfn_planner->initialize("navfn/NavfnROS", costmap_ros);
   } catch (const pluginlib::PluginlibException& ex) {
      ROS_FATAL("Failed to create the navfn/NavfnROS planner, are you sure it is properly registered and that the containing library is built? Exception: %s", ex.what());
      exit(1);
   }

   nh = ros::NodeHandle("~");
   path_subscriber = nh.subscribe<nav_msgs::Path>("custom_path", 10, boost::bind(&GlobalPlanner::customPathCallback, this, _1));
   use_custom_path = false;
 }

 bool GlobalPlanner::makePlan(const geometry_msgs::PoseStamped& start, const geometry_msgs::PoseStamped& goal, std::vector<geometry_msgs::PoseStamped>& plan){
   ROS_WARN("makePlan-------");

   if (!use_custom_path) {
      navfn_planner->makePlan(start, goal, plan);
      return true;
   }

   use_custom_path = false;

   // ros::NodeHandle nh;
   // string pathAddress;
   // nh.getParam("move_base/path", pathAddress);

   // //读取路径文件
   // ifstream infile;
   // infile.open(pathAddress, ios::in | ios::binary);
   // if(!infile) {
   //    ROS_WARN("Failed to open file!");
   //    return false;
   // }
   // string s;
   // vector<string> data;
   // while(getline(infile, s)) {
   //    data.push_back(s.c_str());
   // }

   plan.push_back(start);
   //将路径点导入plan
   for(int i = 0; i < custom_path.poses.size(); i++) {
      geometry_msgs::PoseStamped pos = custom_path.poses[i];
      pos.header.frame_id = start.header.frame_id;

      // double x = atof(split(data[i], " ")[0].c_str());
      // double y = atof(split(data[i], " ")[1].c_str());
      // double ox = atof(split(data[i], " ")[2].c_str());
      // double oy = atof(split(data[i], " ")[3].c_str());
      // double oz = atof(split(data[i], " ")[4].c_str());
      // double ow = atof(split(data[i], " ")[5].c_str());
      // // ROS_INFO("x:%f, y:%f", x, y);

      // pos.pose.position.x = x;
      // pos.pose.position.y = y;
      // pos.pose.position.z = 0;
      // pos.pose.orientation.x = ox;
      // pos.pose.orientation.y = oy;
      // pos.pose.orientation.z = oz;
      // pos.pose.orientation.w = ow;

      plan.push_back(pos);
   }

   // infile.close();
   return true;
 }

 void GlobalPlanner::customPathCallback(const nav_msgs::Path::ConstPtr & custom_path_msg) {
   use_custom_path = true;
   custom_path.header.frame_id = custom_path_msg->header.frame_id;
   custom_path.poses = custom_path_msg->poses;
   ROS_INFO("received a custom path");
 }
 };
