#include "ros/ros.h"
#include <aux_controllers/SetFrame.h>
#include "../../aux_controllers/src/frameservice.h"


int main(int argc, char **argv)
{
  ros::init(argc, argv, "inspectionframe_server");

  FrameService frame("inspection_frame", "world", tf::Vector3(0,0,0), tf::Quaternion(0,0,0,1), "frame_service");

  frame.loop();


  return 0;
}
