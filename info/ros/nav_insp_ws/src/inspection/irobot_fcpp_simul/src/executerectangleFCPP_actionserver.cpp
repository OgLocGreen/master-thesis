#include <ros/ros.h>

#include "ros/ros.h"
#include <actionlib/server/simple_action_server.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>

#include <irobot_fcpp_simul/ExecuteRectangleFCPPAction.h>
#include <irobot_fcpp_simul/FCPP_out.h>
#include <irobot_fcpp_simul/FCPP_in.h>

#include <action_server_package/BaseRotationAction.h>
#include <action_server_package/MoveRobotCoordAction.h>



#include "gazebo_msgs/GetModelState.h"
#include <tf2/transform_datatypes.h>
#include <tf2_ros/transform_listener.h>


#include <geometry_msgs/Point32.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Polygon.h>


#include "../../irobot_fcpp_pckg/src/trappathplanning.h"
#include "../../irobot_fcpp_pckg/src/cutter_functions.h"


#include "../../irobot_fcpp_pckg/src/coords_info.h"

#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>

//Declaracion de estructuras para los defectos
enum dir_rep{YPOS, YNEG, XPOS, XNEG, OUT};


class RectangleFCPPAction
{
protected:

  ros::NodeHandle nh_;
  actionlib::SimpleActionServer<irobot_fcpp_simul::ExecuteRectangleFCPPAction> as_; // NodeHandle instance must be created before this line. Otherwise strange error occurs.
  std::string action_name_;

  // create messages that are used to published feedback/result
  //action_server_package::BaseRotationFeedback feedback_;
  irobot_fcpp_simul::ExecuteRectangleFCPPActionResult result_;

public:

  RectangleFCPPAction(std::string name) :
    as_(nh_, name, boost::bind(&RectangleFCPPAction::executeCB, this, _1), false),
    action_name_(name)
  {
    as_.start();
  }

  ~RectangleFCPPAction(void)
  {
  }

  void executeCB(const irobot_fcpp_simul::ExecuteRectangleFCPPGoalConstPtr &goal)
  {
    // helper variables
    ros::Rate r(1);
    bool success = true;


    std::string robot_model_name="summit_xl";
    std::string tf_robot_name="summit_xl_base_link";
    std::string tf_reference_frame_name="sheet_inspection_frame";


    // start executing the action

      // check that preempt has not been requested by the client
      if (as_.isPreemptRequested() || !ros::ok())
      {
        //robot.stop();
        ROS_INFO("%s: Preempted", action_name_.c_str());
        // set the action state to preempted
        as_.setPreempted();
        success = false;

      }

      else
      {
        ///1.-Obtener la estructura de defectos del servicio


//          ros::ServiceClient client_defectos = nh_.serviceClient<irobot_fcpp_simul::FCPP_out>("fcpp_outdata_service");

//          irobot_fcpp_simul::FCPP_out srv;

//          //srv.request.id_chapa de momento sin request



//          if (!client_defectos.call(srv))
//          {   ROS_ERROR("Failed to call defectos service!!!!!");   return;   }

//          std::vector<irobot_fcpp_simul::defecto> estructura_defectos = srv.response.defecto_out;



        ///2.-Obtener zona en la que se encuentra el robot (sacar de TF)
        ///


          geometry_msgs::Pose pose_robot=getRobotPose(tf_robot_name,tf_reference_frame_name);

          //Se deben obtener las zonas de trabajo y la de rotacion
          ros::ServiceClient client = nh_.serviceClient<irobot_fcpp_simul::FCPP_in>("fcpp_data_service");

          irobot_fcpp_simul::FCPP_in srv_in;

          srv_in.request.id_input=0;
          srv_in.request.get_working_zones=true;
          srv_in.request.get_rot_zone=true;

          if (!client.call(srv_in))
          {   ROS_ERROR("Failed to call service!!!!!");   return;   }

          geometry_msgs::Polygon poly_rot = srv_in.response.zone_rot;

          std::vector<geometry_msgs::Polygon> working_zones_vec;
                                              working_zones_vec.push_back(srv_in.response.zone0);
                                              working_zones_vec.push_back(srv_in.response.zone90);
                                              working_zones_vec.push_back(srv_in.response.zone180);
                                              working_zones_vec.push_back(srv_in.response.zone270);
                                              /*working_zones_vec.push_back(srv_in.response.zone4);
                                              working_zones_vec.push_back(srv_in.response.zone5);
                                              working_zones_vec.push_back(srv_in.response.zone6);
                                              working_zones_vec.push_back(srv_in.response.zone7);
                                              working_zones_vec.push_back(srv_in.response.zone8);
                                              working_zones_vec.push_back(srv_in.response.zone9);*/

          //int zona_int = getWorkingZoneByPos(pose_robot.position.x,pose_robot.position.y, working_zones_vec);
           //En un futuro hacer que empiece por la zona que corresponda


        ///3.-Chequear si el robot se encuentra en zona de rotación
        ///         si no lo está se mueve a ella

          bool canRotate;

         actionlib::SimpleActionClient<action_server_package::BaseRotationAction> ac_rot("baserotation", true);
         ac_rot.waitForServer();
         actionlib::SimpleActionClient<action_server_package::MoveRobotCoordAction> ac_mov("moverobotcoord", true);
         ac_mov.waitForServer();

        ///----------------------REPETIR PARA CADA ZONA---------------

                 ///4.- Orientar a robot para reparar trapecios de zona

                   canRotate = isInRotationZone(pose_robot.position.x,pose_robot.position.y, poly_rot);
                 if(!canRotate)
                 {
                     //Calcular el punto más cercano dentro de la zona de rotacion
                    rectangle_limits rl_rot=rosPolygon2rectlimits(poly_rot);

                    double x_obj=pose_robot.position.x;
                    double y_obj=pose_robot.position.y;

                    if(pose_robot.position.x < rl_rot.xmin)
                        x_obj=rl_rot.xmin;
                    if(pose_robot.position.x > rl_rot.xmax)
                        x_obj=rl_rot.xmax;
                    if(pose_robot.position.y < rl_rot.ymin)
                        y_obj=rl_rot.ymin;
                    if(pose_robot.position.y > rl_rot.ymax)
                        y_obj=rl_rot.ymax;

                        action_server_package::MoveRobotCoordGoal goal;

                        goal.movement.x=x_obj;
                        goal.movement.y=y_obj;
                        //Sin cambiar el theta
                        goal.frame=tf_reference_frame_name;

                        ac_mov.sendGoal(goal);

                        //wait for the action to return
                        bool finished_before_timeout = ac_mov.waitForResult(ros::Duration(3600.0));

                        if (finished_before_timeout)
                        {
                          actionlib::SimpleClientGoalState state = ac_mov.getState();
                          ROS_INFO("Action finished: %s",state.toString().c_str());
                        }
                        else
                          ROS_INFO("Action did not finish before the time out.");

                 }

                 //Rotar robot
                 action_server_package::BaseRotationGoal rot_goal;

                 double theta_rot;
                 int dir_rep;

                 //Dependiendo de tras_herry
                 //trasherry>0 herramienta a la izda
                 //trasherry<0 herramienta a la dcha
                 bool herr_izda = srv_in.response.tras_herry>0;

                 switch (goal->rectangle_id) //Añadir al mensaje
                 {
                 case 0:
                     theta_rot=0;
                     dir_rep=YPOS;
                     break;
                 case 1:
                     theta_rot=0;
                     dir_rep=YNEG;
                     break;
                 case 2:
                     theta_rot=90;
                     dir_rep=XNEG;
                     break;
                 case 4:
                     theta_rot=90;
                     dir_rep=XPOS;
                     break;
                 }

                 rot_goal.number_of_degrees=theta_rot;

                 ac_rot.sendGoal(rot_goal);

                 //wait for the action to return
                 bool finished_before_timeout = ac_rot.waitForResult(ros::Duration(3600.0));

                 if (finished_before_timeout)
                 {
                   actionlib::SimpleClientGoalState state = ac_rot.getState();
                   ROS_INFO("Rotation finished: %s",state.toString().c_str());
                 }
                 else
                   ROS_INFO("Rotation did not finish before the time ou!!!");




                 ///5.- Cubrir zona

                             //Calcular path planning desde el punto más cercano
                              ROS_INFO("Iniciando inspeccion zona");

                             TYPE_OF_PATH type_of_path;
                             if(dir_rep==XPOS || dir_rep==XNEG)
                                 type_of_path=Y_CTE;
                             else
                                 type_of_path=X_CTE;

                             //Sustitur el 0.15 por el ancho de la imagen
                             TrapPathPlanning path(working_zones_vec.at(goal->rectangle_id),1, type_of_path);
                             std::vector<geometry_msgs::Point> path_result;

                             geometry_msgs::Point pose_point;
                             pose_point.x=pose_robot.position.x; pose_point.y=pose_robot.position.y;
                             path.generatePath();
                             path_result = path.computePathStartingFromNearestPoint(pose_point);


                             geometry_msgs::Pose herr_respecto_orig=getRobotPose("reparation_tool_frame",tf_reference_frame_name);
                             geometry_msgs::Pose base_respecto_orig=getRobotPose(tf_robot_name,tf_reference_frame_name);
                             //Trasladar puntos para que los ejecute el robot


                             translatePoints(path_result, -1*(herr_respecto_orig.position.x-base_respecto_orig.position.x),
                                                          -1*(herr_respecto_orig.position.y-base_respecto_orig.position.y));

                             //Ejecutar el movimiento
                             for(int i=0; i<(path_result.size()-1); i++)
                             {
                                 action_server_package::MoveRobotCoordGoal goal;

                                 goal.movement.x=path_result.at(i).x;
                                 goal.movement.y=path_result.at(i).y;
                                 goal.movement.theta=theta_rot;
                                 goal.vel=0.3;
                                 goal.frame=tf_reference_frame_name;

                                 ac_mov.sendGoal(goal);

                                 //wait for the action to return
                                 bool finished_before_timeout = ac_mov.waitForResult(ros::Duration(3600.0));

                                 if (finished_before_timeout)
                                 {
                                   actionlib::SimpleClientGoalState state = ac_mov.getState();
                                   //ROS_INFO("Carril finished: %s",state.toString().c_str());
                                 }
                                 //else
                                   //ROS_INFO("Carril did not finish before the time out.");


                                 rot_goal.number_of_degrees=theta_rot;

                                 ac_rot.sendGoal(rot_goal);

                                 //wait for the action to return
                                 bool finished_before_timeout2 = ac_rot.waitForResult(ros::Duration(3600.0));

                                 if (finished_before_timeout2)
                                 {
                                   actionlib::SimpleClientGoalState state = ac_rot.getState();
                                   ROS_INFO("Reorientation postmov finished: %s",state.toString().c_str());
                                 }
                                 else
                                   ROS_INFO("Reorientation did not finish before the time ou!!!");



                             }


                 //Se actualiza la pose del robot

                 pose_robot= getRobotPose(tf_robot_name, tf_reference_frame_name);


         ///-------------------------------------------------------------------
      }

      // this sleep is not necessary, the sequence is computed at 1 Hz for demonstration purposes
        r.sleep();


        if(success)
        {

            //Informar de los resultados


            ///Solucionar el result
            //result_.recorrido=true; //Quizas necesaripo algo más complejo que un bool
            ROS_INFO("%s: Succeeded", action_name_.c_str());
            // set the action state to succeeded
            //as_.setSucceeded(result_);
        }

  }

  int getWorkingZoneByPos(double x, double y,
                          std::vector<geometry_msgs::Polygon> polygon_vector)
  {
      //Funcion que devuelve la zona que corresponde a unas determinadas coordenadas
      int zona_int=-1;

      for(int i=0; i<polygon_vector.size(); i++)
      {
          if( isInsideRectLimits(x,y, rosPolygon2rectlimits(polygon_vector.at(i))) )
          {
              zona_int=i;
          }
      }

      return zona_int;
  }

  bool isInRotationZone(double x, double y,
                        geometry_msgs::Polygon poly)
  {
    rectangle_limits rot_rl=rosPolygon2rectlimits(poly);
    return isInsideRectLimits(x,y,rot_rl);
  }

  bool isInsideRectLimits(double x, double y, rectangle_limits rl)
  {
      return (x>=rl.xmin && x<=rl.xmax && y>=rl.ymin && y<=rl.ymax);
  }

  rectangle_limits rosPolygon2rectlimits(geometry_msgs::Polygon p)
  {
      rectangle_limits rl;

      double xm, XM, ym, YM;
      xm=-100000000; XM=100000000;struct rectangle_limits
      {
          double xmin, xmax, ymin, ymax;
      };
      ym=xm; YM=XM;

      for(auto & elem: p.points)
      {
          if(elem.x>XM)
             XM=elem.x;
          if(elem.x<xm)
             xm=elem.x;
          if(elem.y>YM)
              YM=elem.y;
          if(elem.y<ym)
              ym=elem.y;
      }
      rl.xmin=xm; rl.xmax=XM;
      rl.ymin=ym; rl.ymax=YM;

      return rl;
  }

  void translatePoints(std::vector<geometry_msgs::Point> &vector, double tras_x, double tras_y)
  {
      for(auto & elem: vector)
      {
          elem.x=elem.x+tras_x;
          elem.y=elem.y+tras_y;
      }
  }

  geometry_msgs::Pose getRobotPose(string robot_frame_name, string reference_frame_name)
  {
      tf2_ros::Buffer tfBuffer;
      tf2_ros::TransformListener tfListener(tfBuffer);

      geometry_msgs::TransformStamped transformStamped;

      static tf::TransformListener tf_listener2;
      tf::StampedTransform tS;

      try{
          tf_listener2.waitForTransform(reference_frame_name,robot_frame_name,ros::Time::now(), ros::Duration(3.0));
          tf_listener2.lookupTransform(reference_frame_name,robot_frame_name,ros::Time::now(),tS);
          tf::transformStampedTFToMsg(tS,transformStamped);

//        transformStamped = tfBuffer.lookupTransform(reference_frame_name,robot_frame_name,ros::Time(0), ros::Duration(1.0));
      }
      catch (tf2::TransformException &ex) {
        ROS_WARN("%s",ex.what());
        ros::Duration(1.0).sleep();
        //continue;
      }

      geometry_msgs::Pose pose_return;

      pose_return.orientation=transformStamped.transform.rotation;
      pose_return.position.x=transformStamped.transform.translation.x;
      pose_return.position.y=transformStamped.transform.translation.y;
      pose_return.position.z=transformStamped.transform.translation.z;

      return pose_return;


  }
};






int main(int argc, char **argv)
{
    ros::init(argc, argv, "executeFCPPofrectangle_actionserver");
    ros::NodeHandle nh;

    RectangleFCPPAction FCPPexecution("rectanglefcpp");
    ROS_INFO("ExecuteRectangleFCPP action server is ready!");

    ros::spin();

    ROS_INFO("Hello world!");
}
