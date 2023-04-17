//#include "robotcontroller.h"
#include "coupledrobot.h"

int main(int argc, char **argv)
{
	
	ros::init(argc, argv, "coupledmain");

	geometry_msgs::Point dist;
	/*dist.x=0.0;
	dist.y=0.5;
	dist.z=0.25;*/

	//CoupledRobot coupled(YOUBOT,dist,0,3*pi/4,pi,"hokuyo_mod","coupled_robot",true);
/*	dist.x=0.0;
	dist.y=0.0;
	dist.z=0.25;
	CoupledRobot coupled(YOUBOT,dist,0,0,0,"kinect_ros","coupled_robot",false);
*/
	dist.x=0.0;
	dist.y=0.0;
  dist.z=0.6;
	//CoupledRobot coupled(YOUBOT,dist,0,0,0,"hokuyo_YVT-35LX","coupled_robot",false);
  CoupledRobot coupled(SUMMIT_XL_A,dist,0,0,0,"hokuyo_mod_slam","coupled_robot",false);



	coupled.start();


	return 0;
}
