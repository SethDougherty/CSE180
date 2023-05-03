#include <rclcpp/rclcpp.hpp> 
#include <nav_msgs/msg/occupancy_grid.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>
#include <geometry_msgs/msg/pose_with_covariance_stamped.hpp>
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/buffer.h>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <iostream>

rclcpp::Node::SharedPtr nodeh;
std::vector<std::pair<float, float>> free_space_coords;
double x_pose;
double y_pose;
float x_trans;
float y_trans;
std::vector<int8_t> global_map;	


void amclPoseCallback(const geometry_msgs::msg::PoseWithCovarianceStamped::SharedPtr amclmsg) {
  // Get the pose information from the message
  geometry_msgs::msg::Pose pose = amclmsg->pose.pose;

  // Extract the position and orientation information from the pose
  x_pose = pose.position.x;
  y_pose = pose.position.y;
 
 	//debugging
  //RCLCPP_INFO(nodeh->get_logger(), "Robot position: x=%f, y=%f, z=%f", x_pose, y_pose, z_pose);
}


void mapCallback(const nav_msgs::msg::OccupancyGrid::SharedPtr msg) {
    
    
    for(int w = 0; w < msg->info.width; ++w){
    	for(int h = 0; h < msg->info.height; ++h){
    		const int index = h * msg->info.width + w;
    		if(msg->data[index] >= 0 || msg->data[index] < 0.175){
    			const float x = (w * msg->info.resolution) + (msg->info.resolution/2);
    			const float y = (h * msg->info.resolution) + (msg->info.resolution/2) - 10;
    			//RCLCPP_INFO(nodeh->get_logger(), "occupied space: x=%f, y=%f", x, y);
    			free_space_coords.emplace_back(x,y);
    		}
    	}
    }

}


void laserCallback(const sensor_msgs::msg::LaserScan::SharedPtr scanmsg) {

tf2_ros::Buffer buffer(nodeh->get_clock());
tf2_ros::TransformListener listener(buffer);
geometry_msgs::msg::TransformStamped transform;

while(rclcpp::ok()){
	try
  	{
  		transform = buffer.lookupTransform("base_link", scanmsg->header.frame_id, tf2::TimePointZero); 
  	}
  	
  	catch (tf2::TransformException& ex)
  	{
  		RCLCPP_ERROR(nodeh->get_logger(), "Failed to lookup transform: %d", ex.what());
  		continue;
  	}
  	
  	x_trans = transform.transform.translation.x;
  	y_trans = transform.transform.translation.y;
  	auto coord = std::make_pair(x_trans, y_trans);
  	
  	for(int i = 0; i < free_space_coords.size(); ++i){
  		if(free_space_coords[i] == coord){
  			RCLCPP_INFO(nodeh->get_logger(), "Object detected at (%f, %f)", x_trans + x_pose, y_trans + y_pose);
  		}
  	}
  	   //RCLCPP_INFO(nodeh->get_logger(), "Object detected at (%f, %f)", transform.transform.translation.x + x_pose, transform.transform.translation.y + y_pose);
  }
}

int main(int argc,char **argv) {
 
  rclcpp::init(argc,argv); // initialize ROS
  nodeh = rclcpp::Node::make_shared("subscriber");
  //buffer = std::make_shared<tf2_ros::Buffer>(nodeh->get_clock());
  
  auto sub = nodeh->create_subscription<nav_msgs::msg::OccupancyGrid>
                                  ("/map",10,&mapCallback);
                                  
  auto subpose = nodeh->create_subscription<geometry_msgs::msg::PoseWithCovarianceStamped>
                                  ("/amcl_pose",10,&amclPoseCallback); 
                                  
  auto subl = nodeh->create_subscription<sensor_msgs::msg::LaserScan>
  				   ("/scan", 10,&laserCallback);
  				   			
                                  
  rclcpp::spin(nodeh);

  // complete here....
  
  rclcpp::shutdown(); // shutdown ROS
  return 0;
}
