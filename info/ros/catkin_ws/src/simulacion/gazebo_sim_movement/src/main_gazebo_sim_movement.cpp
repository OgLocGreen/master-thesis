#include <ros/ros.h>
#include "gazebosimmovement.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "main_gazebo_sim_movement");
    ros::NodeHandle nh;


    GazeboSimMovement sim("summit_xl_a", "summit_xl_a_baselink","world");
    ROS_INFO("Creado simulador");


    geometry_msgs::Pose inicio;
    inicio.position.x=2; inicio.position.y=2;
    inicio.orientation.w= 0.707;
    inicio.orientation.z= 0.707;


    sim.addPoseToOriginals(inicio);
    //sim.readPosesFromMarkerTopic("/topic_pathherr_zone0");
    sim.readPosesFromArrayTopic("/topic_msg_ordered_path");
    ROS_INFO("Finalizada lectura del mensaje!");
    sim.interpolatePoses(0.1);//0.025);
    ROS_INFO("Poses intermedias generadas!");
    ROS_INFO("Inicio de simulacion!");
    sim.startSimulation();


}
