#include <rclcpp/rclcpp.hpp>
#include <turtlesim/msg/pose.hpp>
#include <geometry_msgs/msg/twist.hpp>

class Replicate : public rclcpp::Node {
public:
  Replicate() : Node("replicateoop") {
  sub = this->create_subscription<turtlesim::msg::Pose>
                                  ("turtle1/pose",10,std::bind(&Replicate::poseReceived,this,std::placeholders::_1));
  pub = this->create_publisher<geometry_msgs::msg::Twist>
				  ("/p2dx/cmd_vel",100);
  }



//private:

  void poseReceived(turtlesim::msg::Pose::SharedPtr msg) {
	geometry_msgs::msg::Twist pioneer_vel;
	pioneer_vel.linear.x = msg->linear_velocity;
	pioneer_vel.angular.z = msg->angular_velocity;
	pub->publish(pioneer_vel);
  }

private:
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr pub;
  rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr sub;

};

int main(int argc,char **argv) {

  rclcpp::init(argc,argv); // initialize the ROS subsystem
  rclcpp::spin(std::make_shared<Replicate>()); // create node
  rclcpp::shutdown(); // shutdown ROS
  return 0;
}
