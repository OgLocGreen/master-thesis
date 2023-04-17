//#include "robotcontroller.h"
#include "coupledrobot.h"

int main(int argc, char **argv)
{
	
	ros::init(argc, argv, "coupledmain2");

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
	dist.z=0.5;
	CoupledRobot coupled(MPO700,dist,0,0,0,"velodyne_robot","coupled_robot2",false);
	//CoupledRobot coupled(YOUBOT,dist,0,0,0,"hokuyo_mod_slam","coupled_robot",false);



	coupled.start();


	return 0;
}