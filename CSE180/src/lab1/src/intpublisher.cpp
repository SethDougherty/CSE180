#include <rclcpp/rclcpp.hpp> // needed for basic functions
#include <std_msgs/msg/int32.hpp> // to publish integers

int main(int argc,char **argv) {

  rclcpp::init(argc,argv); // initialize the ROS subsystem

  rclcpp::Node::SharedPtr nodeh;
  rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr pubi;
  rclcpp::Rate rate(1);

  nodeh = rclcpp::Node::make_shared("intpublish"); // create node
    // create publisher to topic "inttopic" of integers
  pubi = nodeh->create_publisher<std_msgs::msg::Int32>("inttopic",1);

  int value=0;
  std_msgs::msg::Int32 intToSend; // integer message to send

  while (rclcpp::ok()) {
    intToSend.data = value++; // update message to send
    pubi->publish(intToSend); // publish the integer message
    RCLCPP_INFO(nodeh->get_logger(),"Completed iteration  #%d",value);
    rate.sleep(); // wait
  }
  rclcpp::shutdown(); // unreachable in the current form
  return 0;

}
