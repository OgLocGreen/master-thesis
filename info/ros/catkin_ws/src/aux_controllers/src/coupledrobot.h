#include "ros/ros.h"
#include "std_msgs/String.h"
#include "gazebo_msgs/ModelState.h"
#include "geometry_msgs/Point.h"
#include "geometry_msgs/Quaternion.h"
#include "gazebo_msgs/GetModelState.h"
#include <tf/transform_datatypes.h>
#include <tf/transform_broadcaster.h>

#include <sstream>
#include <string>
#include <math.h>

#include "robotcontroller.h"       
using namespace std;

#define YOUBOT 1
#define MPO700 2
#define PIONEER2DX 3
#define SUMMITXL 4

#define pi 3.14159265359

#define pi2 6.28318530718

//Clase que permite acoplar una herramienta al robot principal
	//Usa el servicio setModelState para fijar la posc de la herramienta
	//Publica pose y estado de la herramienta en topicos
	//Crea un frame en TF de la herramienta y un frame(opcional) de la proyección en el plano de la misma


class CoupledRobot
{
protected:
	
	
	//Nombres de los modelos Gazebo
	string gazebo_state_model_name;
	string gazebo_coupled_model_name;
	//Nombres de los frames
	string mother_frame_name;
	string tf_newframe_name;
	
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
	
	geometry_msgs::PoseStamped coupled_pose_msg;
	ros::Publisher coupled_pose_pub;
	
	gazebo_msgs::ModelState coupled_state_msg;
	ros::Publisher coupled_state_pub;

	//Booleano para crear frame proyectado
	bool projected;


	//TF frames
	tf::TransformBroadcaster br;
	tf::Transform transform;

	tf::TransformBroadcaster br2;
	tf::Transform transform2;


public:
	//Constructor
	CoupledRobot(int model, geometry_msgs::Point vect,
				double roll_rot, double pitch_rot, double yaw_rot,
				string gzbo_coupled_m_n, string new_TFframe_n,
				bool p);
	
	void start();

	geometry_msgs::Pose getMotherPose();
};