cmake_minimum_required(VERSION 2.8.3)
project(check_latency)
add_compile_options(-std=c++11)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs genmsg)

## Declare ROS messages and services
add_message_files(FILES 
Num.msg
timemsg.msg
)
##add_service_files(FILES AddTwoInts.srv)

## Generate added messages and services
generate_messages(DEPENDENCIES std_msgs)

## Declare a catkin package
catkin_package()

## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(receiver src/receiver.cpp)
target_link_libraries(receiver ${catkin_LIBRARIES})
add_dependencies(receiver check_latency_generate_messages_cpp)

add_executable(transmitter src/transmitter.cpp)
target_link_libraries(transmitter ${catkin_LIBRARIES})
add_dependencies(transmitter check_latency_generate_messages_cpp)