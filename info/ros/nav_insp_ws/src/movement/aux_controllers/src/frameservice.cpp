#include "frameservice.h"


FrameService::FrameService(string name_auxframe, string name_motherframe, tf::Vector3 origin_v, tf::Quaternion rotation_q, string name_service)
{
	//Asignacion de nombres
	auxframe_name = name_auxframe;
	mother_frame_name = name_motherframe;
	service_name = name_service;

	origin_ini = origin_v;
		origin = origin_ini;
	
	rotation_ini = rotation_q;
		rotation= rotation_ini;
}

void FrameService::loop()
{

	service = n.advertiseService(service_name, &FrameService::changePosOr, this);
	while (ros::ok())
	{
		
		ros::spinOnce();
	
	

		transform.setOrigin(origin);
    	transform.setRotation(rotation);
    	br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), mother_frame_name, auxframe_name));
	}

}

bool FrameService::changePosOr(aux_controllers::SetFrame::Request  &req,
	          				   aux_controllers::SetFrame::Response &res)
{
	if (req.ini == true)
	{
		origin = origin_ini;
		rotation= rotation_ini;
	}

	else
	{
		origin.setX(req.origin_x);
		origin.setY(req.origin_y);
		origin.setZ(req.origin_z);

		rotation.setRPY(req.rotation_roll, req.rotation_pitch, req.rotation_yaw);
	}

	return true;
} 