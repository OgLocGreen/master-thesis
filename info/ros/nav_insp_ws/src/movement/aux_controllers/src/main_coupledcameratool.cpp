//#include "robotcontroller.h"
#include "coupledrobot.h"

int main(int argc, char **argv)
{
	
        ros::init(argc, argv, "coupledcameramain");

	geometry_msgs::Point dist;
	dist.x=0.3;
	dist.y=-0.4;
	dist.z=0.15;
	//CoupledRobot coupled(YOUBOT,dist,0,0,0,"hokuyo_YVT-35LX","coupled_robot",false);
        CoupledRobot coupled(SUMMIT_XL_A,dist,0, -pi/4,0,"false_realsense","coupled_camera",true);



	coupled.start();


	return 0;
}
