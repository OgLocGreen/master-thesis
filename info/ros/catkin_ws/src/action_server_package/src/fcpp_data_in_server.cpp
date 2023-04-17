#include "ros/ros.h"
#include "action_server_package/FCPP_in.h"
#include "geometry_msgs/Point.h"
#include "geometry_msgs/Pose2D.h"

bool fcpp_in_params(action_server_package::FCPP_in::Request  &req,
         action_server_package::FCPP_in::Response &res)
{
  
  res.number_of_chapas=1;

  float pos_ini_robot_x=6.0;
  float pos_ini_robot_y=4.0;

  float xc=10.0;
  float yc=19.0;

  float deg15=0.261799;

  switch(req.id_chapa)
  {
      ///Mi mundo##############################################################################
      res.number_of_chapas=2;
      case 0:
              //res.coordA=geometry_msgs::Point(-1.0, 0.0,   0.0);
              res.coordA.x=-1; res.coordA.y= 0;
              res.coordB.x=-3; res.coordB.y= 2;
              res.coordC.x= 0; res.coordC.y= 5;
              res.coordD.x= 2; res.coordD.y= 3;

              //SUSTITUIR POR UNA FUNCIÓN QUE CALCULE DADAS LAS COORDENADAS
              res.long_chapa=4.242640687;//sqrt(18)
              res.width_chapa=2.828427125;//sqrt(8)

              break;
      case 1:
              
              res.coordA.x=-3; res.coordA.y=-11;              
              res.coordB.x=-5; res.coordB.y=-11;
              res.coordC.x=-5; res.coordC.y=-6;
              res.coordD.x=-3; res.coordD.y=-6;


              /*res.coordA=Point(-5,-11,   0);
              res.coordB=Point(-5,-6,   0);
              res.coordC=Point(-3,-6,   0);
              res.coordD=Point(-3,-11,   0);
              */

              //SUSTITUIR POR UNA FUNCIÓN QUE CALCULE DADAS LAS COORDENADAS
              res.long_chapa=5;
              res.width_chapa=2;

              break;
      default:
              res.coordA.x=0; res.coordA.y=0;
              res.coordB.x=0; res.coordB.y=0;
              res.coordC.x=0; res.coordC.y=0;
              res.coordD.x=0; res.coordD.y=0;       
              res.long_chapa=0;
              res.width_chapa=0;
              break;
  } 
/*  res.sum = req.a + req.b;
  ROS_INFO("request: x=%ld, y=%ld", (long int)req.a, (long int)req.b);
  ROS_INFO("sending back response: [%ld]", (long int)res.sum);*/
  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "fcpp_data_in_server");
  ros::NodeHandle n;

  ros::ServiceServer service = n.advertiseService("fcpp_data_in_server", fcpp_in_params);
  ROS_INFO("FCPP (data IN) server is ready");
  ros::spin();

  return 0;
}