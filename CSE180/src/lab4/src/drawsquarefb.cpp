#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <geometry_msgs/msg/pose.hpp>
#include <tf2/LinearMath/Quaternion.h>
#include <nav_msgs/msg/odometry.hpp>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

float x;
float y;
float theta;
tf2::Quaternion q;
double roll, pitch, yaw;
bool init;

void poseCallback(const nav_msgs::msg::Odometry::SharedPtr msg) {
 // nav_msgs::msg::Odometry odom_msg;
  x = msg->pose.pose.position.x;
  y = msg->pose.pose.position.y;
  tf2::convert(msg->pose.pose.orientation,q);
  tf2::Matrix3x3 m(q); // quaternion to matrix
  m.getRPY(roll, pitch, yaw); // matrix to roll pitch yaw
  theta = yaw;
  init = true;
}

int main(int argc,char **argv) {

  rclcpp::init(argc,argv);
  rclcpp::Node::SharedPtr nodeh;
  rclcpp::Rate rate(1);

  nodeh = rclcpp::Node::make_shared("drawsquarefb");
  auto pub = nodeh->create_publisher<geometry_msgs::msg::Twist>
    ("p2dx/cmd_vel",1000);
  auto sub = nodeh->create_subscription<nav_msgs::msg::Odometry>
    ("p2dx/odom",1000,&poseCallback);

  //RCLCPP_INFO_STREAM(nodeh->get_logger(), "This is the x value: " << x)

  geometry_msgs::msg::Twist msg;
  init = false;

  bool rotate = false;
  float start_x = x;
  float start_y = y;
  double DIRS[] = {0,M_PI/2,-M_PI,-M_PI/2}; // desired directions
  int direction = 0; // current direction

  while (!init) // wait for at least one sensor reading
    rclcpp::spin_some(nodeh);

  while (rclcpp::ok()) {
    rclcpp::spin_some(nodeh); //get sensor reading, if available

    if (rotate) { // rotating?
      // reached desired heading?
      if ( ( ( direction == 0  ) && ( theta < DIRS[0] ) ) ||
	   ( ( direction == 1  ) && ( theta < DIRS[1] ) ) ||
	   ( ( direction == 2  ) && ( theta  > 0 ) ) ||
	   ( ( direction == 3  ) && ( theta < DIRS[3] ) ) ) {
	msg.linear.x = 0; msg.angular.z = M_PI/8; // no; keep rotating
      }
      else { // yes
	msg.linear.x = 0; msg.angular.z = 0; //stop the robot
	rotate = false; // switch to translating
	start_x = x; start_y = y; // record current location
      }
    }
    else { // translating?
      if (hypotf((x-start_x),(y-start_y))<2) { // moved less than 2 units?
	//RCLCPP_INFO_STREAM(nodeh->get_logger(), "This is the x value: " << x);
	//RCLCPP_INFO_STREAM(nodeh->get_logger(), "This is the y value: " << y);
	msg.linear.x = 0.5; msg.angular.z = 0;  // no, keep moving forward
      }
      else { // moved 2 units
	rotate = true; // switch to rotate
	msg.linear.x = 0; msg.angular.z = 0; // stop the robot
	++direction %= 4; // track next direction
      }
    }
    pub->publish(msg); // send motion command
  }
}
