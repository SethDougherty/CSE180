#include <rclcpp/rclcpp.hpp>
#include <turtlesim/msg/pose.hpp>
#include <geometry_msgs/msg/twist.hpp>
//#include <tf2/LinearMath/Quaternion.h>
//#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

float linear_x;
float angular_z;
bool valid;

void poseReceived(const turtlesim::msg::Pose::SharedPtr msg) {
   linear_x = msg->linear_velocity;
   angular_z = msg->angular_velocity;
   valid = true;
}

int main(int argc,char ** argv) {

  rclcpp::init(argc,argv);
  rclcpp::Node::SharedPtr nodeh;
  nodeh = rclcpp::Node::make_shared("Replicate");

  auto sub = nodeh->create_subscription<turtlesim::msg::Pose>
                                  ("turtle1/pose",10,&poseReceived);
  auto pub = nodeh->create_publisher<geometry_msgs::msg::Twist>("/p2dx/cmd_vel",1000);
    
  geometry_msgs::msg::Twist pioneer_vel;
  //tf2::Quaternion q;
  valid = false;
  
  while (rclcpp::ok()) {
    rclcpp::spin_some(nodeh);
    if (valid) {
      pioneer_vel.linear.x = linear_x;
      pioneer_vel.linear.y = 0;
      pioneer_vel.linear.z = 0;
      //q.setRPY(0,0,theta);
      pioneer_vel.angular.x = 0;
      pioneer_vel.angular.y = 0;
      pioneer_vel.angular.z = angular_z;
      //RCLCPP_INFO_STREAM(nodeh->get_logger(), "test z: " << angular_z);
      //poseToPublish.orientation = tf2::toMsg(q);   
      pub->publish(pioneer_vel);
      valid = false;
    }
  }
}
