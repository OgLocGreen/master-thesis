#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <action_server_package/CompleteRectangleCoverageAction.h>

#include "../../aux_controllers/src/robotcontroller.h"
#include "../../aux_controllers/src/simplecpp.h"  

class CompleteRectangleCoverageAction
{
protected:

  ros::NodeHandle nh_;
  actionlib::SimpleActionServer<action_server_package::CompleteRectangleCoverageAction> as_; // NodeHandle instance must be created before this line. Otherwise strange error occurs.
  std::string action_name_;
  // create messages that are used to published feedback/result
  action_server_package::CompleteRectangleCoverageFeedback feedback_;
  action_server_package::CompleteRectangleCoverageResult result_;

public:

  CompleteRectangleCoverageAction(std::string name) :
    as_(nh_, name, boost::bind(&CompleteRectangleCoverageAction::executeCB, this, _1), false),
    action_name_(name)
  {
    as_.start();
  }

  ~CompleteRectangleCoverageAction(void)
  {
  }

  void executeCB(const action_server_package::CompleteRectangleCoverageGoalConstPtr &goal)
  {
    // helper variables
    ros::Rate r(1);
    bool success = true;

    geometry_msgs::PoseArray path;
    RobotController robot(SUMMIT_XL_A, "inspection_frame");
    ROS_INFO("Inicia movimiento");

    // publish info to the console for the user
    //ROS_INFO("%s: Ejecutado una rotacion del %f por ciento", action_name_.c_str(), feedback_.number_of_degrees_accomplished);

    // start executing the action

      // check that preempt has not been requested by the client
      if (as_.isPreemptRequested() || !ros::ok())
      {
        robot.stop();
        ROS_INFO("%s: Preempted", action_name_.c_str());
        // set the action state to preempted
        as_.setPreempted();
        success = false;
       
      }
      
      else
      {
        //Se leen los parametros de la accion
        float chapa_long    =  goal->rect_long;
        float chapa_width   =  goal->rect_width;
        float coverage_step =  goal->step;
        float dist_lr       =  goal->dist_lr;
        float laser_width   =  goal->laser_width;
        float vel           =  goal->vel;


        //Se genera el path
        SimpleCPP genpath(chapa_long, chapa_width,
                          coverage_step,
                          dist_lr, laser_width);
        path=genpath.generateCoveragePathPlanning();

        
        for(int i=0;i<path.poses.size();i++)
        {
          ROS_INFO("GOAL PATH x:%f,y:%f,yaw:%f",path.poses[i].position.x, path.poses[i].position.y, robot.Quaternion2EulerYaw(path.poses[i].orientation));
          //Movimientos del robot referidos a la esquina A de la chapa
          robot.move(path.poses[i].position.x, path.poses[i].position.y, 0.5, "inspection_frame",
                     robot.Quaternion2EulerYaw(path.poses[i].orientation), 0, DEFINED_INITIAL_ANGLE);
          

          //            x          ,             y          , vel ,                       theta1             ,theta2,           ANGLE_MODE
        }
      }

      // this sleep is not necessary, the sequence is computed at 1 Hz for demonstration purposes
      r.sleep();
    

    if(success)
    {

      result_.path = path; //no es global
      ROS_INFO("%s: Succeeded", action_name_.c_str());
      // set the action state to succeeded
      as_.setSucceeded(result_);
    }

  }


};


int main(int argc, char** argv)
{
  ros::init(argc, argv, "completerectanglecoverage");

  CompleteRectangleCoverageAction completerectanglecoverage("completerectanglecoverage");

  ROS_INFO("completerectanglecoverage action server is ready!");

  ros::spin();

  return 0;
}
