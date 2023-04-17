#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <action_server_package/MoveRobotCoordAction.h>

#include "../../aux_controllers/src/robotcontroller.h" 

class MoveRobotCoordAction
{
protected:

  ros::NodeHandle nh_;
  actionlib::SimpleActionServer<action_server_package::MoveRobotCoordAction> as_; // NodeHandle instance must be created before this line. Otherwise strange error occurs.
  std::string action_name_;
  // create messages that are used to published feedback/result
  action_server_package::MoveRobotCoordFeedback feedback_;
  action_server_package::MoveRobotCoordResult result_;
  float x_ant, y_ant;

public:

  MoveRobotCoordAction(std::string name) :
    as_(nh_, name, boost::bind(&MoveRobotCoordAction::executeCB, this, _1), false),
    action_name_(name)
  {
    as_.start();
  }

  ~MoveRobotCoordAction(void)
  {
  }

  void executeCB(const action_server_package::MoveRobotCoordGoalConstPtr &goal)
  {
    // helper variables
    ros::Rate r(10);
    bool success = true;

    RobotController robot(SUMMIT_XL_A);
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
        float x=goal->movement.x;
        float y=goal->movement.y;
        float theta=goal->movement.theta;
        string frame=goal->frame;

        float vel=goal->vel;

        ROS_INFO("Robot moviendose a %f, %f con theta: %f segun frame: %s", x,y, theta,frame.c_str());
        robot.move(x,y,vel, frame, theta,theta,DEFINED_ANGLES);

        // this sleep is not necessary, the sequence is computed at 1 Hz for demonstration purposes
        r.sleep();


      if(success)
      {

        result_.finished = true;
        ROS_INFO("%s: Succeeded", action_name_.c_str());
        // set the action state to succeeded
        as_.setSucceeded(result_);
      }
    }



  }


};


int main(int argc, char** argv)
{
  ros::init(argc, argv, "moverobotcoord");

  MoveRobotCoordAction moverobotcoord("moverobotcoord");

  ROS_INFO("MoveRobotCoord action server is ready!");

  ros::spin();

  return 0;
}
