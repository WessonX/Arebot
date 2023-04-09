/** include the libraries you need in your planner here */
 /** for global path planner interface */
 #include <ros/ros.h>
 #include <costmap_2d/costmap_2d_ros.h>
 #include <costmap_2d/costmap_2d.h>
 #include <nav_core/base_global_planner.h>
 #include <geometry_msgs/PoseStamped.h>
 #include <angles/angles.h>
 #include <base_local_planner/world_model.h>
 #include <base_local_planner/costmap_model.h>
 #include <pluginlib/class_loader.h>
 #include "nav_msgs/Path.h"

 using std::string;

 #ifndef GLOBAL_PLANNER_CPP
 #define GLOBAL_PLANNER_CPP

 namespace path_planner {

 class GlobalPlanner : public nav_core::BaseGlobalPlanner {
 public:

  ros::NodeHandle nh;
  ros::Subscriber path_subscriber;

  boost::shared_ptr<nav_core::BaseGlobalPlanner> navfn_planner;
  nav_msgs::Path custom_path;
  bool use_custom_path;

  GlobalPlanner();
  GlobalPlanner(std::string name, costmap_2d::Costmap2DROS* costmap_ros);

  /** overridden classes from interface nav_core::BaseGlobalPlanner **/
  void initialize(std::string name, costmap_2d::Costmap2DROS* costmap_ros);
  bool makePlan(const geometry_msgs::PoseStamped& start,
                const geometry_msgs::PoseStamped& goal,
                std::vector<geometry_msgs::PoseStamped>& plan
               );

  void customPathCallback(const nav_msgs::Path::ConstPtr &custom_path_msg);

  };

 };
 #endif