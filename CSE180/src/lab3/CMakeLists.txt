cmake_minimum_required(VERSION 3.5)
project(lab3)
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

add_executable(Replicate src/Replicate.cpp)
ament_target_dependencies(Replicate rclcpp geometry_msgs turtlesim)

install(TARGETS Replicate DESTINATION lib/${PROJECT_NAME})
install(DIRECTORY include DESTINATION share/${PROJECT_NAME})


ament_package()
