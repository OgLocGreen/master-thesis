#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "rosgraph_msgs/Log.h"

#include "tf/transform_listener.h"

#include <inspection_realsense/Twist_inspection.h>

ros::Publisher *pub_vel;
geometry_msgs::Twist vel;
bool isPublishing = false;
bool isNew =false;

float long_sheet=3.76, width_sheet=2.51;
float long_robot=0.71, width_robot=0.58;
float dist=200;

bool goSlow = false;

void chatterCallback(const inspection_realsense::Twist_inspection &msg)
{


    vel.linear.x = msg.linear.x;
    vel.linear.y = msg.linear.y;
    vel.angular.z = msg.angular.z;
    dist = msg.distance_left;

    if (dist < 0.30)
    {
       // ROS_INFO("GO_SLOW");
        goSlow = true;
        pub_vel->publish(vel);

    }
    else
        goSlow = false;


    isPublishing = true;
    isNew = true;
}

void publishCallback(const rosgraph_msgs::Log::ConstPtr& msg)
{
    if (!isPublishing || goSlow)
    {
     //   ROS_INFO("RETORNO RETORNO RETORNO");
        return;
    }



    geometry_msgs::Twist new_vel;
    new_vel.linear.x = vel.linear.x;
    new_vel.linear.y = vel.linear.y;
    if (isNew)
        new_vel.angular.z = vel.angular.z;
    else
        new_vel.angular.z = 0;



    pub_vel->publish(new_vel);
    isNew = false;

}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "repub_cmd_vel");
    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe("/cmd_vel_robot", 1000, chatterCallback);
    ros::Subscriber sub2 = nh.subscribe("/rosout", 1000, publishCallback);

    pub_vel = new ros::Publisher(nh.advertise<geometry_msgs::Twist>("/summit_xl/cmd_vel", 1));


    ros::spin();

    return 0;
}
