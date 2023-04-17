#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <action_server_package/RectangleCoveragePathPlanningAction.h>

#include "../../aux_controllers/src/simplecpp.h" 

class RectangleCoveragePathPlanningAction
{
protected:

  ros::NodeHandle nh_;
  actionlib::SimpleActionServer<action_server_package::RectangleCoveragePathPlanningAction> as_; // NodeHandle instance must be created before this line. Otherwise strange error occurs.
  std::string action_name_;
  // create messages that are used to published feedback/result
  action_server_package::RectangleCoveragePathPlanningFeedback feedback_;
  action_server_package::RectangleCoveragePathPlanningResult result_;

public:

  RectangleCoveragePathPlanningAction(std::string name) :
    as_(nh_, name, boost::bind(&RectangleCoveragePathPlanningAction::executeCB, this, _1), false),
    action_name_(name)
  {
    as_.start();
  }

  ~RectangleCoveragePathPlanningAction(void)
  {
  }

  void executeCB(const action_server_package::RectangleCoveragePathPlanningGoalConstPtr &goal)
  {
    // helper variables
    ros::Rate r(1);
    
    bool success= true;
    
    geometry_msgs::PoseArray path;

    ROS_INFO("Inicia movimiento");

    // publish info to the console for the user
    //ROS_INFO("%s: Ejecutado una rotacion del %f por ciento", action_name_.c_str(), feedback_.number_of_degrees_accomplished);

    // start executing the action

      // check that preempt has not been requested by the client
      if (as_.isPreemptRequested() || !ros::ok())
      {
        ROS_INFO("%s: Preempted", action_name_.c_str());
        // set the action state to preempted
        as_.setPreempted();
        success = false;
       
      }
      
      else
      {
        SimpleCPP genpath(goal->long_rectangle, goal->width_rectangle,
                          goal->step,
                          goal->dist_lr, goal->width_laser);

        path=genpath.generateCoveragePathPlanning();


      }

      // this sleep is not necessary, the sequence is computed at 1 Hz for demonstration purposes
      r.sleep();
    

    if(success)
    {

      result_.path = path;
      ROS_INFO("%s: Succeeded", action_name_.c_str());
      // set the action state to succeeded
      as_.setSucceeded(result_);
    }

  }


};


int main(int argc, char** argv)
{
  ros::init(argc, argv, "rectanglecoveragepathplanning");

  RectangleCoveragePathPlanningAction rectanglecoveragepathplanning("rectanglecoveragepathplanning");

  ROS_INFO("RectangleCoveragePathPlanning action server is ready!");

  ros::spin();

  return 0;
}
