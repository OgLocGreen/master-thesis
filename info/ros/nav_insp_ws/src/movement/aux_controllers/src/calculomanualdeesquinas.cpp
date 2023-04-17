#include "ros/ros.h"
#include "geometry_msgs/Pose2D.h"
#include "geometry_msgs/Point.h"

struct corners_struct
{
  geometry_msgs::Point A;
  geometry_msgs::Point B;
  geometry_msgs::Point C;
  geometry_msgs::Point D;
};



corners_struct getRectangleCorners(geometry_msgs::Pose2D pose, float ch_long, float ch_width)
{
 	corners_struct corners;

/* 	corners.A.x=   0.5*ch_long;    corners.A.y=   0.5*ch_width;
  corners.B.x=   0.5*ch_long;    corners.B.y= - 0.5*ch_width;
  corners.C.x= - 0.5*ch_long;    corners.C.y= - 0.5*ch_width;	
  corners.D.x= - 0.5*ch_long;    corners.D.y=   0.5*ch_width;*/

  corners.A.x=   0;             corners.A.y=   0;
  corners.B.x=   0;              corners.B.y= 1*ch_width;
  corners.C.x= 1*ch_long;      corners.C.y= 1*ch_width; 
  corners.D.x= 1*ch_long;    corners.D.y=   0;



  corners_struct rot_corners;

	rot_corners.A.x = (corners.A.x*cos(pose.theta) - corners.A.y*sin(pose.theta)) + pose.x; 
	rot_corners.A.y = (corners.A.y*cos(pose.theta) + corners.A.x*sin(pose.theta)) + pose.y;

  rot_corners.B.x = (corners.B.x*cos(pose.theta) - corners.B.y*sin(pose.theta)) + pose.x; 
  rot_corners.B.y = (corners.B.y*cos(pose.theta) + corners.B.x*sin(pose.theta)) + pose.y;

  rot_corners.C.x = (corners.C.x*cos(pose.theta) - corners.C.y*sin(pose.theta)) + pose.x; 
  rot_corners.C.y = (corners.C.y*cos(pose.theta) + corners.C.x*sin(pose.theta)) + pose.y;

  rot_corners.D.x = (corners.D.x*cos(pose.theta) - corners.D.y*sin(pose.theta)) + pose.x; 
  rot_corners.D.y = (corners.D.y*cos(pose.theta) + corners.D.x*sin(pose.theta)) + pose.y;
    


    //}

  	return rot_corners;
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "funcion_para_mirar_esquinas");
  ros::NodeHandle n;

  corners_struct esquinas;
  geometry_msgs::Pose2D pose;
      pose.x =9.3541;
      pose.y =6.005440;
      pose.theta=1.510061;

  esquinas = getRectangleCorners(pose,8.0,3.0);

  ROS_INFO("CoordA: x=%f   y=%f", esquinas.A.x, esquinas.A.y);
  ROS_INFO("CoordB: x=%f   y=%f", esquinas.B.x, esquinas.B.y);
  ROS_INFO("CoordC: x=%f   y=%f", esquinas.C.x, esquinas.C.y);
  ROS_INFO("CoordD: x=%f   y=%f", esquinas.D.x, esquinas.D.y);
  

  return 0;
}