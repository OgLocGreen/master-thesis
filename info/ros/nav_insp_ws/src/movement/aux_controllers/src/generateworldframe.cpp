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

    
using namespace std;


//Programa que genera un frame del mundo a partir de un frame de un robot en Gazebo

int main(int argc, char **argv)
{
	
	ros::init(argc, argv, "generateWorldFrame");

	//---------¡¡¡¡CAMBIAR DEPENDIENDO DEL ROBOT!!!!
    string gazebo_robot_model_name="summit_xl";//mpo
    string robot_frame="summit_xl_base_link";
	

	//Cliente GetModelSTate
	ros::NodeHandle n_client;
	ros::ServiceClient client;
	client= n_client.serviceClient<gazebo_msgs::GetModelState>("/gazebo/get_model_state");

	gazebo_msgs::GetModelState modelstate_msg;	
  	modelstate_msg.request.model_name=gazebo_robot_model_name;
  	modelstate_msg.request.relative_entity_name="world";

	//Frame TF
	tf::TransformBroadcaster br;
	tf::Transform transform;

	geometry_msgs::Point robot_position;
	tf::Quaternion world_rotation;
	tf::Matrix3x3 rot_mat;
	double roll, pitch,robot_yaw;

	while(ros::ok())
	{
	 	//Posicion y orientación del robot respecto al mundo obtenidas de GetModelState
	 	client.call(modelstate_msg);
	 	robot_position=modelstate_msg.response.pose.position;
	 	tf::quaternionMsgToTF(modelstate_msg.response.pose.orientation, world_rotation);
	 	
	 	//La rotación será el quaternion inverso
	 	rot_mat=tf::Matrix3x3(world_rotation);
	 	rot_mat.getRPY(roll,pitch,robot_yaw);
	 	world_rotation=world_rotation.inverse();

	 	//La posición se obtiene con la matriz de rot
	 	//[x'] [cos0 -sin0][x]
	 	//[y']=[sin0  cos0][y]
	 	transform.setOrigin(tf::Vector3(-1*(robot_position.x*cos(-robot_yaw)-robot_position.y*sin(-robot_yaw)),
	 									-1*(robot_position.y*cos(-robot_yaw)+robot_position.x*sin(-robot_yaw)),
	 									robot_position.z));
	    transform.setRotation(world_rotation);
	    //Se publica el frame
	    br.sendTransform(tf::StampedTransform(transform, ros::Time::now(),robot_frame,"gaz_world"));
	}
	return 0;
}
