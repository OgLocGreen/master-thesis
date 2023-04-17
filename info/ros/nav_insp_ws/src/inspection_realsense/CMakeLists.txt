cmake_minimum_required(VERSION 2.8.3)
project(inspection_realsense)

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
    cv_bridge
    tf2_ros)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenCV REQUIRED)
find_package(PCL REQUIRED)

## Generate actions in the 'action' folder
 add_action_files(
 DIRECTORY
   action
   FILES
   findInitialPose.action
   moveForward.action
   moveBackward.action
   checkNewScanBackward.action
   moveLeftStep.action
   captureImages.action

 )

add_message_files(
  DIRECTORY
      msg
      FILES
      Twist_inspection.msg
)

generate_messages(
  DEPENDENCIES actionlib_msgs std_msgs geometry_msgs  # Or other packages containing msgs
)



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

add_executable(findinitialpose_actionserver src/findinitialpose_server.cpp)
TARGET_LINK_LIBRARIES(findinitialpose_actionserver  ${catkin_LIBRARIES})
TARGET_LINK_LIBRARIES(findinitialpose_actionserver opencv_stitching opencv_superres opencv_videostab opencv_aruco opencv_bgsegm opencv_bioinspired opencv_ccalib opencv_dnn opencv_dpm opencv_fuzzy opencv_line_descriptor opencv_optflow opencv_plot opencv_reg opencv_saliency opencv_stereo opencv_structured_light opencv_rgbd opencv_surface_matching opencv_tracking opencv_datasets opencv_text opencv_face opencv_xfeatures2d opencv_shape opencv_video opencv_ximgproc opencv_calib3d opencv_features2d opencv_flann opencv_xobjdetect opencv_objdetect opencv_ml opencv_xphoto opencv_highgui opencv_videoio opencv_imgcodecs opencv_photo opencv_imgproc opencv_core ${EXTERNAL_LIBS})
TARGET_LINK_LIBRARIES(findinitialpose_actionserver pcl_filters pcl_io pcl_visualization pcl_tracking pcl_common pcl_surface pcl_kdtree pcl_keypoints 							pcl_octree pcl_registration pcl_sample_consensus pcl_search pcl_segmentation pcl_surface pcl_features)
add_dependencies(findinitialpose_actionserver findinitialpose_actionserver_generate_messages_cpp)

add_executable(moveforward_actionserver src/moveForward_actionserver.cpp)
TARGET_LINK_LIBRARIES(moveforward_actionserver  ${catkin_LIBRARIES})
TARGET_LINK_LIBRARIES(moveforward_actionserver opencv_stitching opencv_superres opencv_videostab opencv_aruco opencv_bgsegm opencv_bioinspired opencv_ccalib opencv_dnn opencv_dpm opencv_fuzzy opencv_line_descriptor opencv_optflow opencv_plot opencv_reg opencv_saliency opencv_stereo opencv_structured_light opencv_rgbd opencv_surface_matching opencv_tracking opencv_datasets opencv_text opencv_face opencv_xfeatures2d opencv_shape opencv_video opencv_ximgproc opencv_calib3d opencv_features2d opencv_flann opencv_xobjdetect opencv_objdetect opencv_ml opencv_xphoto opencv_highgui opencv_videoio opencv_imgcodecs opencv_photo opencv_imgproc opencv_core ${EXTERNAL_LIBS})
TARGET_LINK_LIBRARIES(moveforward_actionserver pcl_filters pcl_io pcl_visualization pcl_tracking pcl_common pcl_surface pcl_kdtree pcl_keypoints 							pcl_octree pcl_registration pcl_sample_consensus pcl_search pcl_segmentation pcl_surface pcl_features)
add_dependencies(moveforward_actionserver moveforward_actionserver_generate_messages_cpp)

add_executable(movebackward_actionserver src/moveBackward_actionserver.cpp)
TARGET_LINK_LIBRARIES(movebackward_actionserver  ${catkin_LIBRARIES})
TARGET_LINK_LIBRARIES(movebackward_actionserver opencv_stitching opencv_superres opencv_videostab opencv_aruco opencv_bgsegm opencv_bioinspired opencv_ccalib opencv_dnn opencv_dpm opencv_fuzzy opencv_line_descriptor opencv_optflow opencv_plot opencv_reg opencv_saliency opencv_stereo opencv_structured_light opencv_rgbd opencv_surface_matching opencv_tracking opencv_datasets opencv_text opencv_face opencv_xfeatures2d opencv_shape opencv_video opencv_ximgproc opencv_calib3d opencv_features2d opencv_flann opencv_xobjdetect opencv_objdetect opencv_ml opencv_xphoto opencv_highgui opencv_videoio opencv_imgcodecs opencv_photo opencv_imgproc opencv_core ${EXTERNAL_LIBS})
TARGET_LINK_LIBRARIES(movebackward_actionserver pcl_filters pcl_io pcl_visualization pcl_tracking pcl_common pcl_surface pcl_kdtree pcl_keypoints 							pcl_octree pcl_registration pcl_sample_consensus pcl_search pcl_segmentation pcl_surface pcl_features)
add_dependencies(movebackward_actionserver movebackward_actionserver_generate_messages_cpp)

add_executable(checkNewScanBackward_actionserver src/checkNewScanBackward_actionserver.cpp)
TARGET_LINK_LIBRARIES(checkNewScanBackward_actionserver  ${catkin_LIBRARIES})
TARGET_LINK_LIBRARIES(checkNewScanBackward_actionserver opencv_stitching opencv_superres opencv_videostab opencv_aruco opencv_bgsegm opencv_bioinspired opencv_ccalib opencv_dnn opencv_dpm opencv_fuzzy opencv_line_descriptor opencv_optflow opencv_plot opencv_reg opencv_saliency opencv_stereo opencv_structured_light opencv_rgbd opencv_surface_matching opencv_tracking opencv_datasets opencv_text opencv_face opencv_xfeatures2d opencv_shape opencv_video opencv_ximgproc opencv_calib3d opencv_features2d opencv_flann opencv_xobjdetect opencv_objdetect opencv_ml opencv_xphoto opencv_highgui opencv_videoio opencv_imgcodecs opencv_photo opencv_imgproc opencv_core ${EXTERNAL_LIBS})
TARGET_LINK_LIBRARIES(checkNewScanBackward_actionserver pcl_filters pcl_io pcl_visualization pcl_tracking pcl_common pcl_surface pcl_kdtree pcl_keypoints 							pcl_octree pcl_registration pcl_sample_consensus pcl_search pcl_segmentation pcl_surface pcl_features)
add_dependencies(checkNewScanBackward_actionserver checkNewScanBackward_actionserver_generate_messages_cpp)

add_executable(moveleftstep_actionserver src/moveLeftStep_actionserver.cpp)
TARGET_LINK_LIBRARIES(moveleftstep_actionserver  ${catkin_LIBRARIES})
TARGET_LINK_LIBRARIES(moveleftstep_actionserver opencv_stitching opencv_superres opencv_videostab opencv_aruco opencv_bgsegm opencv_bioinspired opencv_ccalib opencv_dnn opencv_dpm opencv_fuzzy opencv_line_descriptor opencv_optflow opencv_plot opencv_reg opencv_saliency opencv_stereo opencv_structured_light opencv_rgbd opencv_surface_matching opencv_tracking opencv_datasets opencv_text opencv_face opencv_xfeatures2d opencv_shape opencv_video opencv_ximgproc opencv_calib3d opencv_features2d opencv_flann opencv_xobjdetect opencv_objdetect opencv_ml opencv_xphoto opencv_highgui opencv_videoio opencv_imgcodecs opencv_photo opencv_imgproc opencv_core ${EXTERNAL_LIBS})
TARGET_LINK_LIBRARIES(moveleftstep_actionserver pcl_filters pcl_io pcl_visualization pcl_tracking pcl_common pcl_surface pcl_kdtree pcl_keypoints 							pcl_octree pcl_registration pcl_sample_consensus pcl_search pcl_segmentation pcl_surface pcl_features)
add_dependencies(moveleftstep_actionserver moveleftstep_actionserver_generate_messages_cpp)

add_executable(captureimages_actionserver src/captureImages_actionserver.cpp)
TARGET_LINK_LIBRARIES(captureimages_actionserver  ${catkin_LIBRARIES})
TARGET_LINK_LIBRARIES(captureimages_actionserver opencv_stitching opencv_superres opencv_videostab opencv_aruco opencv_bgsegm opencv_bioinspired opencv_ccalib opencv_dnn opencv_dpm opencv_fuzzy opencv_line_descriptor opencv_optflow opencv_plot opencv_reg opencv_saliency opencv_stereo opencv_structured_light opencv_rgbd opencv_surface_matching opencv_tracking opencv_datasets opencv_text opencv_face opencv_xfeatures2d opencv_shape opencv_video opencv_ximgproc opencv_calib3d opencv_features2d opencv_flann opencv_xobjdetect opencv_objdetect opencv_ml opencv_xphoto opencv_highgui opencv_videoio opencv_imgcodecs opencv_photo opencv_imgproc opencv_core ${EXTERNAL_LIBS})
TARGET_LINK_LIBRARIES(captureimages_actionserver pcl_filters pcl_io pcl_visualization pcl_tracking pcl_common pcl_surface pcl_kdtree pcl_keypoints 							pcl_octree pcl_registration pcl_sample_consensus pcl_search pcl_segmentation pcl_surface pcl_features)
add_dependencies(captureimages_actionserver moveleftstep_actionserver_generate_messages_cpp)

add_executable(repub_cmd_vel src/repub_cmd_vel.cpp)
TARGET_LINK_LIBRARIES(repub_cmd_vel  ${catkin_LIBRARIES})
add_dependencies(repub_cmd_vel repub_cmd_vel_generate_messages_cpp)

set(CMAKE_BUILD_TYPE DEBUG)


