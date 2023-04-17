
#include <ros/ros.h>
#include <inspection_realsense/moveLeftStepAction.h>
#include <inspection_realsense/Twist_inspection.h>
#include <geometry_msgs/Twist.h>

#include <actionlib/server/simple_action_server.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>

#include <signal.h>

using namespace std;

class moveLeftStepAction
{
protected:
    ros::NodeHandle nh_;
    ros::NodeHandle nh;
    actionlib::SimpleActionServer<inspection_realsense::moveLeftStepAction> as_; // NodeHandle instance must be created before this line. Otherwise strange error occurs.
    std::string action_name_;

    // create messages that are used to published feedback/result
    inspection_realsense::moveLeftStepFeedback feedback_;
    inspection_realsense::moveLeftStepResult result_;

    //Variables
    ros::Publisher *pub_vel;
    inspection_realsense::Twist_inspection vel_msg;
    float vel_goal_=100;
    float step_;



public:

    moveLeftStepAction(std::string name) :
        as_(nh_, name,boost::bind(&moveLeftStepAction::executeCB,this,_1), false),
        action_name_(name)
      {

       as_.start();

      }

    ~moveLeftStepAction(void)
    {
    }


    void executeCB(const inspection_realsense::moveLeftStepGoalConstPtr &goal)
     {


        // helper variables
        ros::Rate r(1);
        bool success = true;


        // start executing the action
          // check that preempt has not been requested by the client
          if (as_.isPreemptRequested() || !ros::ok())
          {

            ROS_INFO("%s: Preempted", action_name_.c_str());
            // set the action state to preempted
            as_.setPreempted();
            success = false;

          }

          else {


              pub_vel = new ros::Publisher(nh.advertise<inspection_realsense::Twist_inspection>("cmd_vel_robot", 30));

              // helper variables
               nh = nh;
               vel_msg.linear.x = vel_msg.linear.y = vel_msg.angular.z = 0;
               vel_msg.distance_left= 1000;
               // accept the new goal

               vel_goal_ = goal->vel;
               step_ = goal->step;

              if (vel_goal_ == 100)
                  return;


              //Ejecutar ¿?
              float t = step_/vel_goal_; //segundos
              ROS_INFO("time: %f",t);
              vel_msg.linear.y = vel_goal_;

              ros::Time beginTime = ros::Time::now();
              ros::Duration secondsIWantToSendMessagesFor = ros::Duration(t);
            //  float endTime = secondsIWantToSendMessagesFor.toSec() + beginTime.toSec();

              while(ros::Time::now().sec - beginTime.sec < t )
              {
                  pub_vel->publish(vel_msg);

                  // Time between messages, so you don't blast out an thousands of
                  // messages in your 3 secondperiod
                  ros::Duration(0.1).sleep();

              }

              vel_msg.linear.y = 0;
              pub_vel->publish(vel_msg);
              sleep(2);

              //Finalizar
          }

          if(success)
          {
                ROS_INFO("%s: Succeeded", action_name_.c_str());
                // set the action state to succeeded
                as_.setSucceeded(result_);

          }


     }


};

int main(int argc, char **argv)
{

    ros::init(argc, argv, "moveLeftStep");
    ros::NodeHandle nh;

    moveLeftStepAction moveLeftStep("moveLeftStep");
    ROS_INFO("Move left action server is ready!");

    ros::spin();

}

