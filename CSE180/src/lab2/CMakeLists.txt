cmake_minimum_required(VERSION 3.5)
project(lab2)
# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(turtlesim REQUIRED)

add_executable(moveturtle src/moveturtle.cpp)
add_executable(posesensor src/posesensor.cpp)
ament_target_dependencies(moveturtle rclcpp geometry_msgs turtlesim)
ament_target_dependencies(posesensor rclcpp geometry_msgs turtlesim)

install(TARGETS moveturtle DESTINATION lib/${PROJECT_NAME})
install(TARGETS posesensor DESTINATION lib/${PROJECT_NAME})
install(DIRECTORY include DESTINATION share/${PROJECT_NAME})


ament_package()
