#ifndef GAZEBOSIMMOVEMENT_H
#define GAZEBOSIMMOVEMENT_H

#include "ros/ros.h"
#include "std_msgs/String.h"
#include "gazebo_msgs/ModelState.h"
#include "geometry_msgs/Point.h"
#include "geometry_msgs/Quaternion.h"
#include "geometry_msgs/PoseArray.h"
#include <visualization_msgs/Marker.h>


#include "gazebo_msgs/GetModelState.h"
#include <tf/transform_datatypes.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>

#include <sstream>
#include <string>
#include <math.h>


//#include "robotcontroller.h"

using namespace std;


class GazeboSimMovement
{
protected:


    //Nombres de los modelos Gazebo
    string gazebo_state_model_name;
    //Nombres de los frames
    string frame_name;
    string reference_frame_name;

    //Servicio GetModelState
    ros::NodeHandle n_client;
    ros::ServiceClient client;
    gazebo_msgs::GetModelState modelstate_msg;

    //Poses del robot principal y del robot acoplado
    geometry_msgs::Pose coupled_pose;
    geometry_msgs::Pose mother_pose;

    //tf::Quaternion tf_pose_orientation;

    //Publicación del topico con la pose y estado del robot
    ros::NodeHandle n_talker;

    geometry_msgs::PoseStamped pose_msg;
    ros::Publisher coupled_pose_pub;

    gazebo_msgs::ModelState model_state_msg;
    ros::Publisher set_state_pub;

    ros::Subscriber sub_pathtopic;


    geometry_msgs::PoseArray original_poses;
    geometry_msgs::PoseArray all_poses;


    //Booleano para crear frame proyectado
    bool projected;


    //TF frames
    tf::TransformBroadcaster br;
    tf::Transform transform;

    tf::TransformBroadcaster br2;
    tf::Transform transform2;

    tf::TransformListener listener_;


    float getThetaFromTwoPoints(float x1, float y1, float x2, float y2);
    geometry_msgs::Pose getPoseInSegment(geometry_msgs::Pose ini, geometry_msgs::Pose end, float dist);



    bool topic_read=false;
    int read_count=0;
    visualization_msgs::Marker aux_marker_msg;
    geometry_msgs::PoseArray aux_array_msg;


    geometry_msgs::PoseArray MarkerMsg2PoseArraymsg(visualization_msgs::Marker marker);

    geometry_msgs::Quaternion q0,q90,q180,q270;
    bool areQuatEqual(geometry_msgs::Quaternion q1, geometry_msgs::Quaternion q2);


public:
    GazeboSimMovement(string gaz_state_model_name, string frame_n, string ref_frame_n);

    void startSimulation();

    void readPoses();

    void addPoseToOriginals(geometry_msgs::Pose p){original_poses.poses.push_back(p);}
    void readPosesFromMarkerTopic(string topic);
    void readPosesFromArrayTopic(string topic);

    void readPosesFromCSV();

    void readPosesFromMarkerTopic_callback(const visualization_msgs::Marker::ConstPtr& msg);
    void readPosesFromArrayTopic_callback(const geometry_msgs::PoseArray::ConstPtr& msg);



    void interpolatePoses(float dist);
    void rotateAllPoses();



};

#endif // GAZEBOSIMMOVEMENT_H
