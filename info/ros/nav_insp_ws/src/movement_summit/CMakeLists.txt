cmake_minimum_required(VERSION 3.0.2)
project(movement_summit)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED
    geometry_msgs
    roscpp
    rospy
    tf
    tf2
    geometry_msgs
    )


## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES movement_summit
#  CATKIN_DEPENDS other_catkin_pkg
#  DEPENDS system_lib
)
catkin_package(
    CATKIN_DEPENDS geometry_msgs roscpp
    )

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
 include
 ${catkin_INCLUDE_DIRS}
)

add_executable(movement_summit movement_summit.cpp)
target_link_libraries(movement_summit ${catkin_LIBRARIES})

set(CMAKE_BUILD_TYPE DEBUG)

