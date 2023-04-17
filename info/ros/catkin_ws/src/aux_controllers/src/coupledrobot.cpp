#include "coupledrobot.h"

///Constructor del controlador
CoupledRobot::CoupledRobot(int model, geometry_msgs::Point vect,
						   double roll_rot, double pitch_rot, double yaw_rot,
						   string gzbo_coupled_m_n, string new_TFframe_n,
						   bool p)
{
	//Selección del modelo
	if (model==YOUBOT)
	{
		gazebo_state_model_name="youbot";
		mother_frame_name="base_footprint";
	}
	if (model==PIONEER2DX)
	{
		gazebo_state_model_name="pioneer2dx";
	}
	if (model==MPO700)
	{
		gazebo_state_model_name="robot";
		mother_frame_name="base_footprint";
	}
	if (model==SUMMITXL)
	{
		gazebo_state_model_name="summit_xl_a";
		mother_frame_name="summit_xl_a_base_footprint";
	}
	//Lectura del booleano
	projected=p;

	//Asignacion de los nombres
	tf_newframe_name=new_TFframe_n;
	gazebo_coupled_model_name=gzbo_coupled_m_n;
  	modelstate_msg.request.model_name=gazebo_state_model_name;
  	modelstate_msg.request.relative_entity_name="world";
	
	//Parametros para la Pose del robot acoplado
		//Posición
	coupled_pose.position.x=vect.x;
	coupled_pose.position.y=vect.y;
	coupled_pose.position.z=vect.z;
		//Orientación
	geometry_msgs::Quaternion coupled_rotation;
	tf::Quaternion tf_coupled_rotation;
	tf_coupled_rotation=tf::createQuaternionFromRPY(roll_rot, pitch_rot, yaw_rot);
	tf::quaternionTFToMsg(tf_coupled_rotation, coupled_rotation);
	coupled_pose.orientation=coupled_rotation;

	//Iniciacion de los nodos publicadores y del cliente
	//coupled_pose_pub= n_talker.advertise<geometry_msgs::PoseStamped>("coupled_pose_stamped", 1000);
	coupled_state_pub= n_talker.advertise<gazebo_msgs::ModelState>("/gazebo/set_model_state", 1000);
	client= n_client.serviceClient<gazebo_msgs::GetModelState>("/gazebo/get_model_state");
}


void CoupledRobot::start()
{
 	while(ros::ok())
 	{
 		mother_pose=getMotherPose();
 				
 		/*Publicacion de la pose del robot
 		coupled_pose_msg.pose=coupled_pose;
 		coupled_pose_msg.header.frame_id=mother_frame_name;
 		coupled_pose_msg.header.stamp=ros::Time();
 		coupled_pose_pub.publish(coupled_pose_msg);*/

 		//Publicacion del estado del robot
 		coupled_state_msg.pose=coupled_pose;
 		coupled_state_msg.reference_frame=mother_frame_name;
 		coupled_state_msg.model_name=gazebo_coupled_model_name;
 		coupled_state_pub.publish(coupled_state_msg);

 		//Creacion frame TF del robot acoplado
 		transform.setOrigin( tf::Vector3(coupled_pose.position.x, coupled_pose.position.y, coupled_pose.position.z) );
    	transform.setRotation( tf::Quaternion(coupled_pose.orientation.x, coupled_pose.orientation.y, coupled_pose.orientation.z, coupled_pose.orientation.w) );
    	br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), mother_frame_name, tf_newframe_name));

    	if(projected)//Creacion frame TF de la proyección del robot acoplado
    	{

    	
    	//Se calcula intersección eje X del robot acoplado con plano XY del robot principal
    	tf::Matrix3x3 base=transform.getBasis();
    	tf::Vector3 colx=base.getRow(0);
    	tf::Vector3 normalplano=tf::Vector3(0.0,0.0,1.0);

    	double t= (0 - normalplano.dot(tf::Vector3(coupled_pose.position.x, coupled_pose.position.y, coupled_pose.position.z))) / normalplano.dot(colx);

    	transform2.setOrigin(colx*t+tf::Vector3(coupled_pose.position.x, coupled_pose.position.y, coupled_pose.position.z));
    	transform2.setRotation( tf::Quaternion(0.0, 0.0, 0.0, 1.0) );
    	br2.sendTransform(tf::StampedTransform(transform2, ros::Time::now(), mother_frame_name, "projected_"+tf_newframe_name));
		}
	}
}

geometry_msgs::Pose CoupledRobot::getMotherPose()
{
	client.call(modelstate_msg);

	return modelstate_msg.response.pose;
}

