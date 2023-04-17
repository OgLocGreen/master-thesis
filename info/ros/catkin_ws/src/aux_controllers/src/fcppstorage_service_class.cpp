#include "fcppstorage_service_class.h"


FCPPStorage_Service_Class::FCPPStorage_Service_Class(string name_auxframe, string name_motherframe, tf::Vector3 origin_v, tf::Quaternion rotation_q, string name_service)
{
	//Asignacion de nombres
	service_name = name_service;
}

void FCPPStorage_Service_Class::loop()
{

	service = n.advertiseService(service_name, &FrameService::changePosOr, this);
	while (ros::ok())
	{
		
		ros::spinOnce();
	}

}