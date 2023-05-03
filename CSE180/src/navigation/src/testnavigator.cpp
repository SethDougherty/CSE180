#include <rclcpp/rclcpp.hpp> 
#include <navigation/navigation.hpp>
#include <nav_msgs/msg/occupancy_grid.hpp>
#include <iostream>

rclcpp::Node::SharedPtr nodeh;
std::vector<std::pair<float, float>> free_space_coords;


int main(int argc,char **argv) {
 
  rclcpp::init(argc,argv); // initialize ROS
  Navigator navigator(true,false); // create node with debug info but not verbose


  // first: it is mandatory to initialize the pose of the robot
  geometry_msgs::msg::Pose::SharedPtr init = std::make_shared<geometry_msgs::msg::Pose>();
  init->position.x = -2;
  init->position.y = -0.5;
  init->orientation.w = 1;
  navigator.SetInitialPose(init);
  // wait for navigation stack to become operationale
  navigator.WaitUntilNav2Active();
  
  
  geometry_msgs::msg::Pose::SharedPtr goal_pos = std::make_shared<geometry_msgs::msg::Pose>();
  goal_pos->position.x = -1.5;
  goal_pos->position.y = 0.5;
  goal_pos->orientation.w = 1;
  // move to new pose
  navigator.GoToPose(goal_pos);
  while ( ! navigator.IsTaskComplete() ) {
    
  }
  
  goal_pos->position.x = -0.5;
  goal_pos->position.y = 0.5;
  goal_pos->orientation.w = 1;
  // move to new pose
  navigator.GoToPose(goal_pos);
  while ( ! navigator.IsTaskComplete() ) {
    
  }
  
  goal_pos->position.x = -0.5;
  goal_pos->position.y = 1.5;
  goal_pos->orientation.w = 1;
  navigator.GoToPose(goal_pos);
  // move to new pose
  while ( ! navigator.IsTaskComplete() ) {
    
  }
  
  goal_pos->position.x = 0.5;
  goal_pos->position.y = 1.5;
  goal_pos->orientation.w = 1;
  navigator.GoToPose(goal_pos);
  // move to new pose
  while ( ! navigator.IsTaskComplete() ) {
    
  }
  
  goal_pos->position.x = 0.5;
  goal_pos->position.y = 0.5;
  goal_pos->orientation.w = 1;
  navigator.GoToPose(goal_pos);
  // move to new pose
  while ( ! navigator.IsTaskComplete() ) {
    
  }
  
  goal_pos->position.x = 1.5;
  goal_pos->position.y = 0.5;
  goal_pos->orientation.w = 1;
  navigator.GoToPose(goal_pos);
  // move to new pose
  while ( ! navigator.IsTaskComplete() ) {
    
  }
  
  goal_pos->position.x = 1.5;
  goal_pos->position.y = -0.5;
  goal_pos->orientation.w = 1;
  navigator.GoToPose(goal_pos);
  // move to new pose
  while ( ! navigator.IsTaskComplete() ) {
    
  }
  
  goal_pos->position.x = 0.5;
  goal_pos->position.y = -0.5;
  goal_pos->orientation.w = 1;
  navigator.GoToPose(goal_pos);
  // move to new pose
  while ( ! navigator.IsTaskComplete() ) {
    
  }
  
  goal_pos->position.x = 0.5;
  goal_pos->position.y = -1.5;
  goal_pos->orientation.w = 1;
  navigator.GoToPose(goal_pos);
  // move to new pose
  while ( ! navigator.IsTaskComplete() ) {
    
  }
  
  goal_pos->position.x = -0.5;
  goal_pos->position.y = -1.5;
  goal_pos->orientation.w = 1;
  navigator.GoToPose(goal_pos);
  // move to new pose
  while ( ! navigator.IsTaskComplete() ) {
    
  }
  
  goal_pos->position.x = -0.5;
  goal_pos->position.y = -0.5;
  goal_pos->orientation.w = 1;
  navigator.GoToPose(goal_pos);
  // move to new pose
  while ( ! navigator.IsTaskComplete() ) {
    
  }

  // complete here....
  
  rclcpp::shutdown(); // shutdown ROS
  return 0;
}
