#include "ros/ros.h"
#include "gazebo_msgs/GetModelState.h"
#include "geometry_msgs/Point.h"
#include "geometry_msgs/PoseArray.h"
#include <tf/transform_datatypes.h>
#include <math.h>


#include <sstream>
#include <string>
using namespace std;

#define YOUBOT 1
#define MPO700 2
#define PIONEER2DX 3

/*struct defecto_recto
{
	geometry_msgs::Point coord_0;
	geometry_msgs::Point coord_f;

	int n_pasadas;
}*/

//Asume que el haz laser se encuentra delante del robot
class SimpleCPP
{
protected:
	
	//Datos chapa
	float longitud;//dimension mayor
	float ancho;//dimension menor
	//Datos laser-robot
	float cleaned_width;
	float dist_lr;


	//Área sensor
	float step;
	
	//float coordDefectos[]; si se quisiera simular un defecto

	geometry_msgs::PoseArray path;

	//Ejes de interés (pasar como TF o como Pose?)
	/*tf::Transform tf_robot;
	tf::Transform tf_tool;
	tf::Transform tf_projected_tool;
*/
	geometry_msgs::Point vector_robot_laser;


public:
	//Constructor
	SimpleCPP(float l, float a, float s, float d_lr, float c_w);

	geometry_msgs::PoseArray generateCoveragePathPlanning();
	void AddPointToPath(float x, float y, geometry_msgs::Quaternion q);
	geometry_msgs::Point AddXLaneToPath(geometry_msgs::Point start,float long_x, float generating_step, geometry_msgs::Quaternion q);
	geometry_msgs::Point AddYLaneToPath(geometry_msgs::Point start,float long_y, float generating_step, geometry_msgs::Quaternion q);
	void AddLaneToPath(geometry_msgs::Point start,float long_lane, float signed_generating_step, int axis, geometry_msgs::Quaternion q);



};