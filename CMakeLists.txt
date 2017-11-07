cmake_minimum_required(VERSION 2.8.3)
project(image_classifier)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages

find_package(catkin REQUIRED COMPONENTS
  message_generation
  rospy
  sensor_msgs
)

################################################
## Declare ROS messages, services and actions ##
################################################

add_service_files(
        FILES
        Classify.srv
)

## Generate added messages and services with any dependencies listed here
generate_messages(
        DEPENDENCIES
)

###################################################
## Declare things to be passed to other projects ##
###################################################

## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package()

###########
## Build ##
###########

## Specify additional locations of header files
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

#############
## Install ##
#############
