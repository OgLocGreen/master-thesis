#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Point.h"
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/Quaternion.h"
#include <tf2/transform_datatypes.h>
#include <tf2/LinearMath/Matrix3x3.h>
#include <tf2_ros/transform_listener.h>

#include <sstream>
#include <string>
#include <math.h>       
using namespace std;

#define YOUBOT 1
#define MPO700 2
#define PIONEER2DX 3
#define SUMMIT_XL_A 4

#define DEFINED_ANGLES 0
#define DEFINED_INITIAL_ANGLE 1
#define DEFINED_FINAL_ANGLE 2
#define DEFAULT_INITIAL_AND_FINAL_ANGLE 3

#define pi 3.14159265359

#define pi2 6.28318530718

class RobotController
{
protected:
	//Parámetros dependientes del modelo elegido
	string robot_frame_name;
	string default_reference_frame;

	string topic_cmdvel_name;
	int dir_rot;

	//Nodo publicador cmd_vel
	ros::NodeHandle n_talker;
	ros::Publisher cmd_vel_pub;
	geometry_msgs::Twist command;
	
	
	//Cliente para el servicio SetModelState
	ros::NodeHandle n_client_s;
	ros::ServiceClient client_s;

	//Función que determina la dirección de giro más corta para llegar a un ángulo 
	int shortest_rot_dir(float theta_f, float theta_0);

	


public:
	//Constructor
    RobotController(int model, string default_frame="world");


	//Setter y getter de la pose del robot
	geometry_msgs::Pose getPose(string reference_frame_name);
		geometry_msgs::Pose getPose();
	float getEulerYaw(string reference_frame_name);
		float getEulerYaw();
	float getThetaFromTwoPoints(float x1, float y1,float x2, float y2);
	

	//Mov relativo robot
	void move(float x, float y, float vel, string reference_frame_name, float theta1=0, float theta2=0, int ANGLE_MODE=DEFAULT_INITIAL_AND_FINAL_ANGLE);
		void move(float x, float y, float vel, float theta1=0, float theta2=0, int ANGLE_MODE=DEFAULT_INITIAL_AND_FINAL_ANGLE);

	void turn(float theta, float w, string reference_frame_name, bool shortest_path=true, int sign=1);
		void turn(float theta, float w, bool shortest_path=true, int sign=1);
	void turn_rel(float theta_rel, float w, string reference_frame_name);
		void turn_rel(float theta_rel, float w);
	void stop();

	double Quaternion2EulerYaw(geometry_msgs::Quaternion q);//Dado el quaternion devuelve el yaw del robot
	//Función para dividir un segmento en steps de una distancia dada;
	geometry_msgs::Point getPointInSegment(geometry_msgs::Point ini, geometry_msgs::Point end, float dist=1);

};
