#include "simplecpp.h"
#include "robotcontroller.h"

int main(int argc, char **argv)
{
	
	ros::init(argc, argv, "simplecpp");

				//long  anch  step  dist_lr  anch_laser
	SimpleCPP genpath(8,    5,    1,     1,       2);

	geometry_msgs::PoseArray path=genpath.generateCoveragePathPlanning();

  RobotController robot(SUMMIT_XL_A, "generated_world");

	 for(int i=0;i<path.poses.size();i++)
	 	{
	 	ROS_INFO("GOAL PATH x:%f,y:%f,yaw:%f",path.poses[i].position.x, path.poses[i].position.y, robot.Quaternion2EulerYaw(path.poses[i].orientation));
	 	robot.move(path.poses[i].position.x,path.poses[i].position.y, 0.3 ,robot.Quaternion2EulerYaw(path.poses[i].orientation), 0     ,DEFINED_INITIAL_ANGLE);
	 	//						x          ,             y          , vel ,                       theta1					   ,theta2,           ANGLE_MODE
	 	}





	return 0;
}
