#include <ros/ros.h>

#include "ros/ros.h"
#include <actionlib/server/simple_action_server.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>

#include <irobot_fcpp_simul/ExecutePathAction.h>
#include <irobot_fcpp_simul/FCPP_out.h>
#include <irobot_fcpp_simul/FCPP_in.h>

#include<irobot_fcpp_simul/bool_aux.h>

#include <action_server_package/BaseRotationAction.h>
#include <action_server_package/MoveRobotCoordAction.h>



#include "gazebo_msgs/GetModelState.h"
#include <tf2/transform_datatypes.h>
#include <tf2_ros/transform_listener.h>
#include <tf/transform_datatypes.h>



#include <geometry_msgs/Point32.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Polygon.h>


#include "../../irobot_fcpp_pckg/src/trappathplanning.h"
#include "../../irobot_fcpp_pckg/src/cutter_functions.h"


#include "../../irobot_fcpp_pckg/src/coords_info.h"


//Declaracion de estructuras para los defectos
enum dir_rep{YPOS, YNEG, XPOS, XNEG, OUT};


class ExecutePathAction
{
protected:

  ros::NodeHandle nh_;
  actionlib::SimpleActionServer<irobot_fcpp_simul::ExecutePathAction> as_; // NodeHandle instance must be created before this line. Otherwise strange error occurs.
  std::string action_name_;
  ros::Publisher *pub;


  // create messages that are used to published feedback/result
  //action_server_package::BaseRotationFeedback feedback_;
  irobot_fcpp_simul::ExecutePathResult result_;
  irobot_fcpp_simul::ExecutePathFeedback feedback_;


public:

  ExecutePathAction(std::string name) :
    as_(nh_, name, boost::bind(&ExecutePathAction::executeCB, this, _1), false),
    action_name_(name)
  {
    as_.start();
  }

  ~ExecutePathAction(void)
  {
  }

  void executeCB(const irobot_fcpp_simul::ExecutePathGoalConstPtr &goal)
  {
    // helper variables
    ros::Rate r(1);
    bool success = true;
    bool arrivedOrigin = false;
    irobot_fcpp_simul::bool_aux msg_bool;
    msg_bool.data = false;

    std::string robot_model_name="summit_xl_a";
    std::string tf_robot_name="summit_xl_a_base_link";
    std::string tf_reference_frame_name="origin_of_the_universe";

    pub = new ros::Publisher(nh_.advertise<irobot_fcpp_simul::bool_aux>("/getImagesBool", 1));


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

         actionlib::SimpleActionClient<action_server_package::BaseRotationAction> ac_rot("baserotation", true);
         ac_rot.waitForServer();
         actionlib::SimpleActionClient<action_server_package::MoveRobotCoordAction> ac_mov("moverobotcoord", true);
         ac_mov.waitForServer();


         //Calcular path planning desde el punto más cercano
          ROS_INFO("Iniciando ejecucion path");


         //Ejecutar el movimiento
         for(int i_path=0; i_path<goal->path.size(); i_path++)
         {
         ROS_INFO("Nuevo path");
         for(int i_pose=0; i_pose<goal->path.at(i_path).poses.size(); i_pose++)
         {
             ROS_INFO("Nueva pose");
             action_server_package::MoveRobotCoordGoal coord_goal;


             if (i_pose == 1)
                arrivedOrigin = true;

             if (arrivedOrigin)
             {
                 msg_bool.header.stamp = ros::Time::now() ;
                 msg_bool.data = true;
                 pub->publish(msg_bool);
                 arrivedOrigin = false;
             }


             if(goal->path.at(i_path).poses.at(i_pose).position.z!=0)
                 ROS_INFO("Pose singular");

             coord_goal.movement.x=goal->path.at(i_path).poses.at(i_pose).position.x;
             coord_goal.movement.y=goal->path.at(i_path).poses.at(i_pose).position.y;
             geometry_msgs::Quaternion q_ros=goal->path.at(i_path).poses.at(i_pose).orientation;
             tf::Quaternion q_tf;
             tf::quaternionMsgToTF(q_ros , q_tf);
             double theta_rot=q_tf.getAngle()/**180/3.14159265359*/;

             coord_goal.movement.theta=theta_rot;

             coord_goal.vel=0.3; //Estaba 0.3
             coord_goal.frame=tf_reference_frame_name;

             ROS_INFO("Enviando goal moverobotcoord");
             ac_mov.sendGoal(coord_goal);

             //wait for the action to return
             bool finished_before_timeout = ac_mov.waitForResult(ros::Duration(3600.0));


             if (finished_before_timeout)
             {
               ROS_INFO("Finished before timeout");
               actionlib::SimpleClientGoalState state = ac_mov.getState();
               //ROS_INFO("Carril finished: %s",state.toString().c_str());
             }
             else
               ROS_INFO("Carril did not finish before the time out.");


             action_server_package::BaseRotationGoal rot_goal;

             rot_goal.number_of_degrees=theta_rot*180/3.14159265359;

             ROS_INFO("Enviando goal baserotation");

           //  ac_rot.sendGoal(rot_goal);

             //wait for the action to return
             bool finished_before_timeout2 = ac_rot.waitForResult(ros::Duration(3600.0));

             if (finished_before_timeout2)
             {
               actionlib::SimpleClientGoalState state = ac_rot.getState();
               ROS_INFO("Reorientation postmov finished: %s",state.toString().c_str());
             }
             else
               ROS_INFO("Reorientation did not finish before the time out!!!");

          //  std::string msg="Alcanzada posicion"+ std::to_string(i_pose)+ "de"+ std::to_string(goal->path.at(35).poses.size());
            // std::cout<<msg<<std::endl;


             feedback_.recorrido = false;
             as_.publishFeedback(feedback_);
         }

        }

         // this sleep is not necessary, the sequence is computed at 1 Hz for demonstration purposes
           r.sleep();


           if(success)
           {

               //Informar de los resultados

               ///Solucionar el result
               result_.recorrido=true; //Quizas necesario algo más complejo que un bool
               ROS_INFO("%s: Succeeded", action_name_.c_str());
               // set the action state to succeeded
               as_.setSucceeded(result_);

           }

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

      try{
        transformStamped = tfBuffer.lookupTransform(reference_frame_name,robot_frame_name,ros::Time(0), ros::Duration(1.0));
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
    ros::init(argc, argv, "executePath_actionserver");
    ros::NodeHandle nh;    

    ExecutePathAction PathExecution("executepath_action");
    ROS_INFO("ExecutePath action server is ready!");

    ros::spin();

}
