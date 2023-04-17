#include "ros/ros.h"
#include "std_msgs/String.h"

#include "aux_controllers/SetFrame.h"

#include <tf/transform_datatypes.h>
#include <tf/transform_broadcaster.h>


#include <sstream>
#include <string>
#include <math.h>
   
using namespace std;


#define pi 3.14159265359

#define pi2 6.28318530718

//Clase que permite generar un frame cuya posición y orientación es modificable mediante un servicio


class FrameService
{
protected:
	
	//Nombres de los frames
	string mother_frame_name;
	string auxframe_name;
	string service_name;
	
	tf::Vector3 origin_ini;
	tf::Quaternion rotation_ini;

	tf::Vector3 origin;
	tf::Quaternion rotation;

	//Servicio
	ros::NodeHandle n;
	ros::ServiceServer service;

	//TF frames
	tf::TransformBroadcaster br;
	tf::Transform transform;



public:
	//Constructor
	FrameService(string name_auxframe, string name_motherframe, tf::Vector3 origin_v, tf::Quaternion rotation_q, string name_service);
	
	void loop();

	bool changePosOr(aux_controllers::SetFrame::Request  &req,
	          		 aux_controllers::SetFrame::Response &res);

	
};