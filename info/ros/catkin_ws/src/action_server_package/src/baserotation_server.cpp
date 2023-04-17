#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <action_server_package/BaseRotationAction.h>

#include "../../aux_controllers/src/robotcontroller.h" 
#include "geometry_msgs/Pose.h" 

class BaseRotationAction
{
protected:

  ros::NodeHandle nh_;
  actionlib::SimpleActionServer<action_server_package::BaseRotationAction> as_; // NodeHandle instance must be created before this line. Otherwise strange error occurs.
  std::string action_name_;
  // create messages that are used to published feedback/result
  action_server_package::BaseRotationFeedback feedback_;
  action_server_package::BaseRotationResult result_;

public:

  BaseRotationAction(std::string name) :
    as_(nh_, name, boost::bind(&BaseRotationAction::executeCB, this, _1), false),
    action_name_(name)
  {
    as_.start();
  }

  ~BaseRotationAction(void)
  {
  }

  void executeCB(const action_server_package::BaseRotationGoalConstPtr &goal)
  {
    // helper variables
    ros::Rate r(1);
    bool success = true;

    RobotController robot(SUMMIT_XL_A);
    ROS_INFO("Inicia rotacion");

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
        float n_degrees_rad=(goal->number_of_degrees)*pi/180;

        //geometry_msgs::Pose initial_pose=robot.getPose("map");
        //float yaw0=robot.Quaternion2EulerYaw(initial_pose.orientation);
        
        robot.turn_rel(n_degrees_rad,0.4);

        // this sleep is not necessary, the sequence is computed at 1 Hz for demonstration purposes
        r.sleep();


      if(success)
      {
            geometry_msgs::Pose final_pose=robot.getPose();
            float yawf=robot.Quaternion2EulerYaw(final_pose.orientation);
        result_.final_yaw = yawf;
        ROS_INFO("%s: Succeeded", action_name_.c_str());
        // set the action state to succeeded
        as_.setSucceeded(result_);
      }
      }



  }


};


int main(int argc, char** argv)
{
  ros::init(argc, argv, "baserotation");

  BaseRotationAction baserotation("baserotation");

  ROS_INFO("BaseRotation action server is ready!");

  ros::spin();

  return 0;
}
