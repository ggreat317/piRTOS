cmake_minimum_required(VERSION 3.8)
project(hello_drone_cpp)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

add_executable(heartbeat src/heartbeat.cpp)
target_link_libraries(heartbeat rclcpp::rclcpp ${std_msgs_TARGETS})

# ros2 run looks in lib/<package>/ for executables
install(TARGETS heartbeat DESTINATION lib/${PROJECT_NAME})

ament_package()
