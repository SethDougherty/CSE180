#include <rclcpp/rclcpp.hpp> // needed for basic functions
#include <std_msgs/msg/int32.hpp> // to receive integers

rclcpp::Node::SharedPtr nodeh;

// callback function called every time a message is received from the
// topic "intm"
void intCallback(const std_msgs::msg::Int32::SharedPtr msg) {
  // print received integer to the screen
  RCLCPP_INFO(nodeh->get_logger(),"Received integer: %d",msg->data + msg->data-1);
}


int main(int argc,char **argv) {

  rclcpp::init(argc,argv); // initialize ROS subsystem
  rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subi;
  nodeh = rclcpp::Node::make_shared("intsubscribe"); // create node instance
    // subscribe to topic "inttopic" an register the callback function
  subi = nodeh->create_subscription<std_msgs::msg::Int32>
                                         ("inttopic",10,&intCallback);
  rclcpp::spin(nodeh); // wait for messages and process them

  rclcpp::shutdown();
  return 0;

}
