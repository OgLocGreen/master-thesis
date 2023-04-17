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

//Clase que permite almacenar los datos referentes a los datos de entrada al problema de FCPP


class FCPPStorage_Service_Class
{
protected:
	
	//Nombres de los frames
	string service_name;
	
	double xmin, xmax, ymin, ymax;

	int n_defectos;

	//Vector de Poligonos
	std::vector<geometry_msgs::Polygon> poly_vector;
	
	ros::NodeHandle n;
	ros::ServiceServer service;


public:
	//Constructor
	FCPPStorage_Service_Class();

	void addPolydefect(geometry_msgs::Polygon poly);

	geometry_msgs::Polygon getPolyDefectAt(int i);

	int getNumberOfDefects(){return poly_vector.size();}
	
	void loop();
	
};