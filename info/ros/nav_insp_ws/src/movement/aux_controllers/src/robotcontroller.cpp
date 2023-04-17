#include "robotcontroller.h"
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>

///Constructor del controlador
RobotController::RobotController(int model, string default_frame)
{
//Selección del modelo
if (model==YOUBOT)
{
    robot_frame_name="base_link";
    topic_cmdvel_name="cmd_vel";
    dir_rot=1;
}
if (model==PIONEER2DX)
{
    robot_frame_name="base_link";
    topic_cmdvel_name="/pioneer2dx/cmd_vel";
    dir_rot=-1;
}

if (model==MPO700)
{
    robot_frame_name="base_link";
    topic_cmdvel_name="/base/twist_mux/command_navigation";
    dir_rot=1;
}

if (model==SUMMIT_XL_A)
{
    //robot_frame_name="summit_xl_base_link";
    robot_frame_name="summit_xl_base_link";
    topic_cmdvel_name= "/summit_xl/cmd_vel";
    dir_rot=1;
}
    default_reference_frame=default_frame;

	//Configuración del topic cmd_vel
    cmd_vel_pub= n_talker.advertise<geometry_msgs::Twist>(topic_cmdvel_name, 10);

	command.linear.x=0.0;
	command.angular.z=0.0;
    cmd_vel_pub.publish(command);
}

geometry_msgs::Pose RobotController::getPose(string reference_frame_name)
{
/*	client.call(modelstate_msg);

	return modelstate_msg.response.pose;*/

	tf2_ros::Buffer tfBuffer;
  	tf2_ros::TransformListener tfListener(tfBuffer);

  	geometry_msgs::TransformStamped transformStamped;

    static tf::TransformListener tf_listener2;
    tf::StampedTransform tS;
    
    try{

      tf_listener2.waitForTransform(reference_frame_name,robot_frame_name,ros::Time(0), ros::Duration(3.0));
      tf_listener2.lookupTransform(reference_frame_name,robot_frame_name,ros::Time(0),tS);
      tf::transformStampedTFToMsg(tS,transformStamped);
     // transformStamped = tfBuffer.lookupTransform(reference_frame_name,robot_frame_name,ros::Time(0), ros::Duration(3.0));
    }
    catch (tf2::TransformException &ex) {
      ROS_WARN("%s",ex.what());
      //continue;
    }

    geometry_msgs::Pose pose_return;

    pose_return.orientation=transformStamped.transform.rotation;
    pose_return.position.x=transformStamped.transform.translation.x;
    pose_return.position.y=transformStamped.transform.translation.y;
    pose_return.position.z=transformStamped.transform.translation.z;

    return pose_return;


}
		geometry_msgs::Pose RobotController::getPose()
		{
			geometry_msgs::Pose pose_return = getPose(default_reference_frame);
			return pose_return;
		}


float RobotController::getEulerYaw(string reference_frame_name)
{
    geometry_msgs::Pose pose;

    pose=getPose(reference_frame_name);

    float yaw=Quaternion2EulerYaw(pose.orientation);

    return yaw;

}
		float RobotController::getEulerYaw()
		{
			float yaw_return = getEulerYaw(default_reference_frame);
			return yaw_return;
		}


void RobotController::move(float x, float y, float vel, string reference_frame_name, float theta1, float theta2, int ANGLE_MODE)
{
    vel= 0.15;

    float theta_0, theta_f;
    float w=0.1;

	//····Analizar el ANGLE_MODE	
	switch (ANGLE_MODE)
	{
		case DEFINED_ANGLES:
									theta_0=theta1;
									theta_f=theta2;						
									break;
		case DEFINED_INITIAL_ANGLE:
									theta_0=theta1;
									break;
		case DEFINED_FINAL_ANGLE:
									theta_f=theta2;
									break;
	};

	//····Rotación inicial
    //¿Convertir todo a 0->360?

    sleep(1);
	if (ANGLE_MODE==DEFINED_ANGLES || ANGLE_MODE==DEFINED_INITIAL_ANGLE)
	{
		if (reference_frame_name==robot_frame_name)
		{
            ROS_INFO("ROTACION INICIAL RELATIVA: %f", theta_0);
			turn_rel(theta_0,w);// string reference_frame_name="map"
		}
		else
		{
            ROS_INFO("ROTACION INICIAL ABSOLUTA: %f", theta_0);
            turn(theta_0, w, reference_frame_name);

		}
	}

	//stop();

	//····Comandos de  velocidad


	geometry_msgs::Pose posc_i = getPose(reference_frame_name);
    double yaw_0=Quaternion2EulerYaw(posc_i.orientation); //yaw inicial
	
	geometry_msgs::Point posc_f;
						 posc_f.x=x;
	 					 posc_f.y=y;

	//Angulo entre los 2 puntos

	double yaw_1=atan2(
						y-posc_i.position.y,
						x-posc_i.position.x
						); 

	//Caso especial de coordenadas relativas al propio robot
	if(reference_frame_name==robot_frame_name)
	{
	 	 //ROS_INFO("Coord relativas");
         posc_i=getPose(default_reference_frame);
		 ROS_INFO("x_i:%f, y_i:%f", posc_i.position.x, posc_i.position.y);
		 yaw_0=Quaternion2EulerYaw(posc_i.orientation);

	 	 double xw,yw;
	 	 xw=x*cos(yaw_0)-y*sin(yaw_0);
	 	 yw=y*cos(yaw_0)+x*sin(yaw_0);
		 
		 posc_f.x=xw + posc_i.position.x;
		 posc_f.y=yw + posc_i.position.y;
			
		 yaw_1=atan2(yw,xw);
	}


	//objetivo final
    ROS_INFO("OBEJTIVO FINAL x_f:%f", posc_f.x);
    ROS_INFO("OBJETIVO FINAL y_f:%f", posc_f.y);
	
	geometry_msgs::Point p_i;
						 p_i.x=posc_i.position.x;//P_i
						 p_i.y=posc_i.position.y;
	geometry_msgs::Point theory_p_i=p_i;
	geometry_msgs::Point p_i1;//P_i+1

    ROS_INFO("El robot esta aqui respecto a %s x:%f, y:%f",reference_frame_name.c_str(), p_i.x, p_i.y);


	//While: 

    while(
          abs(p_i.x-posc_f.x)>0.08
		  			||
          abs(p_i.y-posc_f.y)>0.08
			/*p_i.x!=posc_f.x
	 			||
           p_i.y!=posc_f.y*/
          )
	 	  {

			 	p_i1=getPointInSegment(theory_p_i,posc_f,0.5);

                ROS_INFO("	i x:%f, y:%f ---> x:%f, y:%f", p_i.x, p_i.y, p_i1.x, p_i1.y);
			 
				
			 	yaw_1=atan2(
							p_i1.y-posc_i.position.y,
							p_i1.x-posc_i.position.x
							); 
			 	
			 	if(reference_frame_name!=robot_frame_name)
				 	yaw_0=getEulerYaw(reference_frame_name); 
				else
					yaw_0=getEulerYaw(default_reference_frame);



                while( abs(p_i1.x-posc_i.position.x)>0.08
									  ||
                       abs(p_i1.y-posc_i.position.y)>0.08 )
				 	{

                        command.linear.x=vel*cos(yaw_1-yaw_0);
						command.linear.y=vel*sin(yaw_1-yaw_0);
						command.angular.z=0.0;
				        cmd_vel_pub.publish(command);


				 		if (reference_frame_name!=robot_frame_name)
				 			posc_i=getPose(reference_frame_name);
				 		else
				 			posc_i=getPose(default_reference_frame);


                        ROS_INFO("	i x:%f, y:%f ---> x:%f, y:%f", posc_i.position.x, posc_i.position.y, p_i1.x, p_i1.y);
                        ROS_INFO("	velX: %f, velY: %f", command.linear.x, command.linear.y);


//                        ROS_INFO("El robot esta aqui respecto a %s x:%f, y:%f",reference_frame_name.c_str(), posc_i.position.x, posc_i.position.y);

				 		//Correción anti derrape (necesaria o ajustar más el turn(una velocidad que vaya dismuyendo segun se aproxime a objetivo?))
			        	//turn(yaw_0,0.2);
				 	}
				 	theory_p_i=p_i1; //posc en la que debería encontrarse
				 	

				 	p_i.x=posc_i.position.x;//posc en la que está
                    p_i.y=posc_i.position.y;


           }

	//····Rotación final
/*
	if (ANGLE_MODE==DEFINED_ANGLES || ANGLE_MODE==DEFINED_FINAL_ANGLE)
	{
		if (reference_frame_name==robot_frame_name)
		{
            ROS_INFO("ROTACION FINAL RELATIVA: %f", theta_0);
			turn_rel(theta_0,w);// string reference_frame_name="map"
		}
		else
		{
            ROS_INFO("ROTACION FINAL ABSOLUTA: %f", theta_f);
            turn(theta_f, w, reference_frame_name);
		}
	}
*/
	//····Parada

    ROS_INFO("LLEGO A LA POSICION. BUSCANDO LA SIGUIENTE");
    //pose_ant.position.x = posc_f.x;
    //pose_ant.position.y = posc_f.y;

    stop();
   // sleep(5);


 }
		void RobotController::move(float x, float y, float vel, float theta1, float theta2, int ANGLE_MODE)
		{move(x,y,vel, default_reference_frame, theta1, theta2, ANGLE_MODE);}




int RobotController::shortest_rot_dir(float theta_f, float theta_0)
{

    //1. Convertir ángulos al rango 0º-360º
    float theta_f_deg = theta_f*180/pi;
    float theta_0_deg = theta_0*180/pi;

    while(theta_f_deg>360) theta_f_deg = theta_f_deg - 360;
    while(theta_0_deg>360) theta_0_deg = theta_0_deg - 360;

    while (theta_f_deg < 0)
    {
       // while (theta_f_deg < 360) theta_f_deg = theta_f_deg + 360;
        theta_f_deg = theta_f_deg + 360;
    }

    while (theta_0_deg < 0)
    {
      //  while (theta_0_deg < 360) theta_0_deg = theta_0_deg + 360;
        theta_0_deg = theta_0_deg + 360;
    }

    //2. Calcular la dirección de rotación más corta
    //Retornamos 1 si la velocidad tiene que ser positiva y -1 si negativa. Dependiendo del sentido de giro

    float dist = theta_f_deg - theta_0_deg;
    int dir=0;

    if (dist>=0 && fabs(dist) <= 180) dir = 1;
    else if (dist>0 && fabs(dist) > 180) dir = -1;
    else if (dist<0 && fabs(dist) < 180) dir = -1;
    else if (dist<=0 && fabs(dist) >= 180) dir = 1;

    ROS_INFO("THETA_0: %f, THETA_F: %f, DIR: %d", theta_0_deg, theta_f_deg, dir);

    return dir;


    //Lo de abajo está comentado por Sara. Estaba hecho por Álvaro pero a veces gira en el sentido que no debe
    //Veamos si lo de arriba funciona mejor.

    /*
	float theta_f_2pi, theta_0_2pi;
	if(theta_f<0)
		theta_f_2pi=pi2+theta_f;
	else
		theta_f_2pi=theta_f;

	if(theta_0<0)
		theta_0_2pi=pi2+theta_0;
	else
		theta_0_2pi=theta_0;

	float theta_0_2pi_opos=theta_0_2pi+pi;

	float theta_dist=theta_f_2pi-theta_0_2pi;

	while (theta_dist>pi)
		theta_dist=theta_dist-pi2;
	while(theta_dist<-pi)
		theta_dist=theta_dist+pi2;


	if (theta_dist>0) return 1;
	else return -1; 
    */

}

float RobotController::getThetaFromTwoPoints(float x1, float y1,float x2, float y2)
{
	return atan2(y2 - y1, x2 - x1);
}


geometry_msgs::Point RobotController::getPointInSegment(geometry_msgs::Point ini, geometry_msgs::Point end, float dist)
{
	if (hypot(ini.x-end.x, ini.y-end.y)<=dist)
		return end;
	else
	{
		float theta = getThetaFromTwoPoints(ini.x, ini.y, end.x, end.y);

		geometry_msgs::Point vector;
							 vector.x=cos(theta);
							 vector.y=sin(theta);

		geometry_msgs::Point return_point;
							 return_point.x=ini.x+dist*vector.x;
							 return_point.y=ini.y+dist*vector.y;

		return return_point;
	}
}

# define PI 3.141592
void::RobotController::turn_abs(float theta, float vel)
{

    float vel_ang = vel/60*(2*PI);
    command.linear.x = 0.0;
    command.linear.y = 0.0;
    command.angular.z = vel;

    ros::Time beginTime = ros::Time::now();
    ros::Time secondsIWantToSendMessagesFor = ros::Time(2*theta/vel);
    ros::Time endTime = ros::Time(secondsIWantToSendMessagesFor.sec + beginTime.sec);

    while(ros::Time::now() < endTime )
    {
        cmd_vel_pub.publish(command);
        ros::Duration(0.2).sleep();
    }

   // ROS_INFO("PUBLICANDO VELOCIDAD. VEL=%f, time=%f",vel,2*theta/vel);


   // ros::Duration(2*theta/vel).sleep();

    command.angular.z = 0.0;
    cmd_vel_pub.publish(command);
}

void RobotController::turn(float theta, float w, string reference_frame_name, bool shortest_path, int sign)
{
	
	double theta_i=getEulerYaw(reference_frame_name);
	
	int dir;

    dir=shortest_rot_dir(theta, theta_i);

//    if(shortest_path) dir=shortest_rot_dir(theta, theta_i);
//	else dir=sign;

    while(abs(theta-theta_i)>0.05)//aprox 3º
 	{
		command.linear.x=0.0;
		command.linear.y=0.0;

       // if(shortest_path) dir=shortest_rot_dir(theta, theta_i);
				
        dir=shortest_rot_dir(theta, theta_i);
		command.angular.z=dir_rot*dir*w;
		/*if(abs(theta-theta_i)<0.1)
			ROS_INFO("t=%f, tf=%f, dif=%f",theta_i, theta,abs(theta-theta_i));*/
        cmd_vel_pub.publish(command);

       // ROS_INFO("DIR: %d", dir);
       // ROS_INFO("ROTANDO (º): t=%f, tf=%f, dif=%f, vel=%f",theta_i*180/pi, theta*180/pi,(theta_i-theta)*180/pi, command.angular.z);

        theta_i=getEulerYaw(reference_frame_name);
 	}
 	stop();
}
			void RobotController::turn(float theta, float w, bool shortest_path, int sign)
			{turn(theta, w, default_reference_frame, shortest_path, sign);}


void RobotController::turn_rel(float theta_rel, float w, string reference_frame_name)
{
		double yaw_0=getEulerYaw(reference_frame_name);
		//ROS_INFO("                     theta: %f",theta_rel*180/pi);	
		//ROS_INFO("                     yaw_ini: %f",yaw_0*180/pi);
		
        float yaw, yawf;
        int signo;
        if (theta_rel>=0)signo=1;
        else signo=-1;

        yawf=yaw_0+theta_rel;
        
        if (yawf>pi) yawf=-pi+(abs(yawf-pi));
        if (yawf<-pi) yawf=pi-(abs(yawf+pi));

        //ROS_INFO("                     Objetivo final yaw: %f",yawf*180/pi);
        turn(yawf,0.2,reference_frame_name, false, signo);
        stop();

        //ROS_INFO("						Fin rotacion");
      

}
			void RobotController::turn_rel(float theta_rel, float w)
			{turn_rel(theta_rel, w, default_reference_frame);}

void RobotController::stop()
{
	ros::Time start_time = ros::Time::now();
	ros::Duration timeout(0.1); // Timeout of 0.1 seconds
	while(ros::Time::now() - start_time < timeout)//0.005 da problemas encima de superficies
	{
	command.linear.x=0.0;
   	command.linear.y=0.0;
   	command.linear.z=0.0;

	command.angular.x=0.0;
	command.angular.y=0.0;
	command.angular.z=0.0;


    cmd_vel_pub.publish(command);
    }

}

double RobotController::Quaternion2EulerYaw(geometry_msgs::Quaternion quaternion)
{
	tf2::Quaternion q(quaternion.x,
					 quaternion.y,
					 quaternion.z,
					 quaternion.w);
	tf2::Matrix3x3 m(q);
	double roll, pitch, yaw;
	m.getRPY(roll, pitch, yaw);
	return yaw;
}
