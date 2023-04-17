#include "ros/ros.h"
#include "std_msgs/String.h"
#include "gazebo_msgs/ModelState.h"
#include "geometry_msgs/Point.h"
#include "geometry_msgs/Quaternion.h"
#include "gazebo_msgs/GetModelState.h"
#include <tf/transform_datatypes.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>

#include "octomap_msgs/BoundingBoxQuery.h"

#include <sstream>
#include <string>

    
using namespace std;


int main(int argc, char **argv)
{
      ros::init(argc, argv, "ClearOctoboxNode");
    
    //Cliente Clear_bbx
    ros::NodeHandle n_client;
    ros::ServiceClient client;
    client= n_client.serviceClient<octomap_msgs::BoundingBoxQuery>("/octomap_server/clear_bbx");

    octomap_msgs::BoundingBoxQuery bbox;
    //geometry_msgs::Point min, max;
    //Dimensiones bbox
    double long_x, long_y, height;
    long_x=6.0;
    long_y=6.0;
    height=3.0;

    double robotx, roboty, robotz;

    tf::TransformListener listener;
    tf::StampedTransform transform;

    ros::Rate r(1);//Se hace una vez por segundo

    robot_frame_name="summit_xl_base_link";
    topic_cmdvel_name= "/summit_xl/cmd_vel";

while(ros::ok())
 	{
        
    listener.waitForTransform("/map",robot_frame_name, ros::Time(0), ros::Duration(20.0));
    listener.lookupTransform("/map",robot_frame_name, ros::Time(0), transform);

    robotx= transform.getOrigin().getX();    
    roboty = transform.getOrigin().getY();
    robotz = transform.getOrigin().getZ();

    
    bbox.request.min.x=robotx-long_x/2;
    bbox.request.min.y=roboty-long_y/2;
    bbox.request.min.z=0.0;

    bbox.request.max.x=robotx+long_x/2;
    bbox.request.max.y=roboty+long_x/2;
    bbox.request.max.z=height;

    /*ROS_INFO("MIN: %f, %f, %f  MAX: %f, %f, %f", bbox.request.min.x, bbox.request.min.y, bbox.request.min.z, 
                                                 bbox.request.max.x, bbox.request.max.y, bbox.request.max.z);*/

    client.call(bbox);


    ros::spinOnce();
    r.sleep();
 				
    }
}
