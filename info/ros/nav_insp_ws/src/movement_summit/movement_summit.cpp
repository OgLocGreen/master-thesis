#include "ros/ros.h"
#include <geometry_msgs/Twist.h>
#include <stdlib.h>
#include <ros/publisher.h>

#include <tf/transform_listener.h>
#include <tf/transform_datatypes.h>

#include <geometry_msgs/Pose.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "movement_summit");
    ros::NodeHandle nh;

    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("/summit_xl/cmd_vel", 30);

    ros::Rate loop_rate(10);
    double vel = 0.15;
    geometry_msgs::Twist msg;
    bool llego_x = false, llego_y=false;

    static tf::TransformListener tf_listener2;
    tf::StampedTransform tS;
    geometry_msgs::TransformStamped tS_g;
    try{
        tf_listener2.waitForTransform("inspection_frame","summit_xl_odom_estimated",ros::Time(0), ros::Duration(3.0));
        tf_listener2.lookupTransform("inspection_frame","summit_xl_odom_estimated",ros::Time(0),tS);
        tf::transformStampedTFToMsg(tS,tS_g);

    }
    catch (tf2::TransformException &ex) {
      ROS_WARN("%s",ex.what());
    }
    geometry_msgs::Point p_i;
    p_i.x = tS_g.transform.translation.x;
    p_i.y = tS_g.transform.translation.y;

    geometry_msgs::Point posc_f;
                         posc_f.x=1.5;
                         posc_f.y=1.5;

    while (ros::ok())
    {

        while(fabs(p_i.x-posc_f.x)>0.15 ||  fabs(p_i.y-posc_f.y)>0.15)
        {
            //comando vel, sleep
            msg.angular.z=0;

            if (posc_f.x > (p_i.x-0.3) && posc_f.x < (p_i.x+0.3))
            {
                msg.linear.x=0;
                llego_x = true;
            }
            else if (posc_f.x > p_i.x)
                msg.linear.x=vel;
            else if (posc_f.x < p_i.x )
                msg.linear.x=-vel;

            if (posc_f.y > (p_i.y-0.3) && posc_f.y < (p_i.y+0.3))
            {
                msg.linear.y=0;
                llego_y = true;
            }
            else if (posc_f.y > p_i.y)
                msg.linear.y=vel;
            else if (posc_f.y < p_i.y )
                msg.linear.y=-vel;


            try{
                tf_listener2.waitForTransform("inspection_frame","summit_xl_odom_estimated",ros::Time(0), ros::Duration(3.0));
                tf_listener2.lookupTransform("inspection_frame","summit_xl_odom_estimated",ros::Time(0),tS);
                tf::transformStampedTFToMsg(tS,tS_g);

            }
            catch (tf2::TransformException &ex) {
              ROS_WARN("%s",ex.what());
            }

            p_i.x = tS_g.transform.translation.x;
            p_i.y = tS_g.transform.translation.y;

            ROS_INFO("Position: x:%f, y:%f", p_i.x, p_i.y);



            pub.publish(msg);
            loop_rate.sleep();


        }

        ROS_INFO("LLEGOOO");
        /*
        geometry_msgs::Twist msg;
        msg.linear.x=-0.2;

        //Publish the message
        pub.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
*/
    }

    return 0;
}
