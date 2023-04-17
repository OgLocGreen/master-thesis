cmake_minimum_required(VERSION 2.8.3)
project(irobot_inspection_pckg)

## Compile as C++11, supported in ROS Kinetic and newer
 add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED
    geometry_msgs
    roscpp
    rospy
    std_msgs
    message_generation
    actionlib_msgs
    actionlib
    tf
    tf2
    pcl_ros
    gazebo_msgs
    cv_bridge)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenCV REQUIRED)
find_package(PCL REQUIRED)


## Uncomment this if the package has a setup.py. This macro ensures
## modules and global scripts declared therein get installed
## See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
# catkin_python_setup()

################################################
## Declare ROS messages, services and actions ##
################################################

## To declare and build messages, services or actions from within this
## package, follow these steps:
## * Let MSG_DEP_SET be the set of packages whose message types you use in
##   your messages/services/actions (e.g. std_msgs, actionlib_msgs, ...).
## * In the file package.xml:
##   * add a build_depend tag for "message_generation"
##   * add a build_depend and a exec_depend tag for each package in MSG_DEP_SET
##   * If MSG_DEP_SET isn't empty the following dependency has been pulled in
##     but can be declared for certainty nonetheless:
##     * add a exec_depend tag for "message_runtime"
## * In this file (CMakeLists.txt):
##   * add "message_generation" and every package in MSG_DEP_SET to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * add "message_runtime" and every package in MSG_DEP_SET to
##     catkin_package(CATKIN_DEPENDS ...)
##   * uncomment the add_*_files sections below as needed
##     and list every .msg/.srv/.action file to be processed
##   * uncomment the generate_messages entry below
##   * add every package in MSG_DEP_SET to generate_messages(DEPENDENCIES ...)

## Generate messages in the 'msg' folder
 add_message_files(
 DIRECTORY
   msg
   FILES
   polygonArray.msg
)

## Generate services in the 'srv' folder
# add_service_files(
#   FILES
#   Service1.srv
#   Service2.srv
# )

## Generate actions in the 'action' folder
 add_action_files(
 DIRECTORY
   action
   FILES
   getPolygons.action
   getPartialPanorama.action
   getImages.action
   getCompletePanorama.action
 )

## Generate added messages and services with any dependencies listed here
generate_messages(
  DEPENDENCIES
  std_msgs geometry_msgs std_msgs actionlib_msgs# Or other packages containing msgs
)

################################################
## Declare ROS dynamic reconfigure parameters ##
################################################

## To declare and build dynamic reconfigure parameters within this
## package, follow these steps:
## * In the file package.xml:
##   * add a build_depend and a exec_depend tag for "dynamic_reconfigure"
## * In this file (CMakeLists.txt):
##   * add "dynamic_reconfigure" to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * uncomment the "generate_dynamic_reconfigure_options" section below
##     and list every .cfg file to be processed

## Generate dynamic reconfigure parameters in the 'cfg' folder
# generate_dynamic_reconfigure_options(
#   cfg/DynReconf1.cfg
#   cfg/DynReconf2.cfg
# )

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(DEPENDS OpenCV)
catkin_package(
    CATKIN_DEPENDS actionlib_msgs message_runtime geometry_msgs roscpp std_msgs
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

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${PCL_INCLUDE_DIRS})


add_executable(getpolygon_actionserver src/getpolygon_actionserver.cpp)
target_link_libraries(getpolygon_actionserver   ${catkin_LIBRARIES}     opencv_stitching opencv_superres opencv_videostab opencv_aruco
                                                                        opencv_bgsegm opencv_bioinspired opencv_ccalib opencv_dnn opencv_dpm
                                                                        opencv_fuzzy opencv_line_descriptor opencv_optflow opencv_plot
                                                                        opencv_reg opencv_saliency opencv_stereo opencv_structured_light
                                                                        opencv_rgbd opencv_surface_matching opencv_tracking opencv_datasets
                                                                        opencv_text opencv_face opencv_xfeatures2d opencv_shape opencv_video
                                                                        opencv_ximgproc opencv_calib3d opencv_features2d opencv_flann opencv_xobjdetect
                                                                        opencv_objdetect opencv_ml opencv_xphoto opencv_highgui opencv_videoio
                                                                        opencv_imgcodecs opencv_photo opencv_imgproc opencv_core ${EXTERNAL_LIBS})
add_dependencies(getpolygon_actionserver getpolygon_actionserver_generate_messages_cpp)


add_executable(getpartialpanorama_actionserver src/getpartialpanorama_actionserver.cpp)
target_link_libraries(getpartialpanorama_actionserver   ${catkin_LIBRARIES}     opencv_stitching opencv_superres opencv_videostab opencv_aruco
                                                                        opencv_bgsegm opencv_bioinspired opencv_ccalib opencv_dnn opencv_dpm
                                                                        opencv_fuzzy opencv_line_descriptor opencv_optflow opencv_plot
                                                                        opencv_reg opencv_saliency opencv_stereo opencv_structured_light
                                                                        opencv_rgbd opencv_surface_matching opencv_tracking opencv_datasets
                                                                        opencv_text opencv_face opencv_xfeatures2d opencv_shape opencv_video
                                                                        opencv_ximgproc opencv_calib3d opencv_features2d opencv_flann opencv_xobjdetect
                                                                        opencv_objdetect opencv_ml opencv_xphoto opencv_highgui opencv_videoio
                                                                        opencv_imgcodecs opencv_photo opencv_imgproc opencv_core ${EXTERNAL_LIBS})
add_dependencies(getpartialpanorama_actionserver getpartialpanorama_actionserver_generate_messages_cpp)

add_executable(getimages_actionserver src/getimages_actionserver.cpp)
target_link_libraries(getimages_actionserver   ${catkin_LIBRARIES} ${PCL_LIBRARIES}     opencv_stitching opencv_superres opencv_videostab opencv_aruco
                                                                        opencv_bgsegm opencv_bioinspired opencv_ccalib opencv_dnn opencv_dpm
                                                                        opencv_fuzzy opencv_line_descriptor opencv_optflow opencv_plot
                                                                        opencv_reg opencv_saliency opencv_stereo opencv_structured_light
                                                                        opencv_rgbd opencv_surface_matching opencv_tracking opencv_datasets
                                                                        opencv_text opencv_face opencv_xfeatures2d opencv_shape opencv_video
                                                                        opencv_ximgproc opencv_calib3d opencv_features2d opencv_flann opencv_xobjdetect
                                                                        opencv_objdetect opencv_ml opencv_xphoto opencv_highgui opencv_videoio
                                                                        opencv_imgcodecs opencv_photo opencv_imgproc opencv_core ${EXTERNAL_LIBS})
target_link_libraries(getimages_actionserver pcl_filters pcl_io pcl_visualization pcl_tracking pcl_common pcl_surface pcl_kdtree pcl_keypoints pcl_octree pcl_registration pcl_sample_consensus pcl_search pcl_segmentation pcl_surface pcl_features)
add_dependencies(getimages_actionserver getimages_actionserver_generate_messages_cpp)

add_executable(getcompletepanorama_actionserver src/getcompletepanorama_actionserver.cpp)
target_link_libraries(getcompletepanorama_actionserver   ${catkin_LIBRARIES}     opencv_stitching opencv_superres opencv_videostab opencv_aruco
                                                                        opencv_bgsegm opencv_bioinspired opencv_ccalib opencv_dnn opencv_dpm
                                                                        opencv_fuzzy opencv_line_descriptor opencv_optflow opencv_plot
                                                                        opencv_reg opencv_saliency opencv_stereo opencv_structured_light
                                                                        opencv_rgbd opencv_surface_matching opencv_tracking opencv_datasets
                                                                        opencv_text opencv_face opencv_xfeatures2d opencv_shape opencv_video
                                                                        opencv_ximgproc opencv_calib3d opencv_features2d opencv_flann opencv_xobjdetect
                                                                        opencv_objdetect opencv_ml opencv_xphoto opencv_highgui opencv_videoio
                                                                        opencv_imgcodecs opencv_photo opencv_imgproc opencv_core ${EXTERNAL_LIBS})
add_dependencies(getcompletepanorama_actionserver getcompletepanorama_actionserver_generate_messages_cpp)

set(CMAKE_BUILD_TYPE DEBUG)


## Declare a C++ library
# add_library(${PROJECT_NAME}
#   src/${PROJECT_NAME}/irobot_inspection_pckg.cpp
# )

## Add cmake target dependencies of the library
## as an example, code may need to be generated before libraries
## either from message generation or dynamic reconfigure
# add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Declare a C++ executable
## With catkin_make all packages are built within a single CMake context
## The recommended prefix ensures that target names across packages don't collide
# add_executable(${PROJECT_NAME}_node src/irobot_inspection_pckg_node.cpp)

## Rename C++ executable without prefix
## The above recommended prefix causes long target names, the following renames the
## target back to the shorter version for ease of user use
## e.g. "rosrun someones_pkg node" instead of "rosrun someones_pkg someones_pkg_node"
# set_target_properties(${PROJECT_NAME}_node PROPERTIES OUTPUT_NAME node PREFIX "")

## Add cmake target dependencies of the executable
## same as for the library above
# add_dependencies(${PROJECT_NAME}_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
# target_link_libraries(${PROJECT_NAME}_node
#   ${catkin_LIBRARIES}
# )

#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# install(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark executables and/or libraries for installation
# install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}_node
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark cpp header files for installation
# install(DIRECTORY include/${PROJECT_NAME}/
#   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#   FILES_MATCHING PATTERN "*.h"
#   PATTERN ".svn" EXCLUDE
# )

## Mark other files for installation (e.g. launch and bag files, etc.)
# install(FILES
#   # myfile1
#   # myfile2
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
# )

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_irobot_inspection_pckg.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)
