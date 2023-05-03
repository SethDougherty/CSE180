#include <rclcpp/rclcpp.hpp>
#include <turtlesim/msg/pose.hpp>
#include <geometry_msgs/msg/pose.hpp>

float x;
float y;
float theta;
bool valid;
rclcpp::Node::SharedPtr nodeh;



void poseReceived(const turtlesim::msg::Pose::SharedPtr msg) {
   x = msg->x;
   y = msg->y;
   theta = msg->theta;
   //RCLCPP_INFO_STREAM(nodeh->get_logger(), "This is the x value: " << x);
   //RCLCPP_INFO_STREAM(nodeh->get_logger(), "This is the y value: " << y);
   //RCLCPP_INFO_STREAM(nodeh->get_logger(), "This is the theta value: " << theta);
   valid = true;
}

int main(int argc,char ** argv) {

  rclcpp::init(argc,argv);

  rclcpp::Rate rate(1);
  nodeh = rclcpp::Node::make_shared("republishpose");

  auto sub = nodeh->create_subscription<turtlesim::msg::Pose>
                                  ("turtle1/pose",10,&poseReceived);
  
  while (rclcpp::ok()) {
    rclcpp::spin_some(nodeh);
    if(valid){
	RCLCPP_INFO_STREAM(nodeh->get_logger(), "This is the x value: " << x);
	RCLCPP_INFO_STREAM(nodeh->get_logger(), "This is the y value: " << y);
	RCLCPP_INFO_STREAM(nodeh->get_logger(), "This is the theta value: " << theta);
	rate.sleep();
    }
  }
}
