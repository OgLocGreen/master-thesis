#include "simplecpp.h"

SimpleCPP::SimpleCPP(float l, float a, float s, float d_lr, float c_w)
{
longitud=l;
ancho=a;
step=s;

dist_lr=d_lr;
cleaned_width=c_w;

}

//Setters
geometry_msgs::PoseArray SimpleCPP::generateCoveragePathPlanning()
{
	float long_lane=longitud-cleaned_width;
	float width_lane=cleaned_width;
	float last_lane_y=ancho-cleaned_width/2;

	int n_lanes;
	n_lanes=ceil(ancho/width_lane); //numero de carriles

	geometry_msgs::Point start;
						 start.x=cleaned_width-dist_lr;
						 start.y=cleaned_width/2;

	geometry_msgs::Point px, py;
	px=start;

	geometry_msgs::Quaternion default_q;
		default_q.x=0;
		default_q.y=0;
		default_q.z=0;
		default_q.w=1;

	for(int i=1;i<=n_lanes;i++)
	{
		
		py=AddXLaneToPath(px,long_lane,step,default_q);
		if((py.y+width_lane)>last_lane_y)
			px=AddYLaneToPath(py, last_lane_y-py.y, step,default_q);
		else
			px=AddYLaneToPath(py,width_lane,step,default_q);
		//ROS_INFO("LANE");
		long_lane=long_lane*-1;
	}

	geometry_msgs::Point p_last;
	p_last.x=start.x;
	p_last.y=last_lane_y;

	geometry_msgs::Quaternion pre_final_q;
						pre_final_q.x=0;
						pre_final_q.y=0;
						pre_final_q.z=1;
						pre_final_q.w=0;
	AddYLaneToPath(p_last,0,step, pre_final_q);

	
	//ROS_INFO("LAST LANE");
	geometry_msgs::Quaternion final_q;
						final_q.x=0;
						final_q.y=0;
						final_q.z=-0.707;
						final_q.w= 0.707;

	AddYLaneToPath(p_last,(start.y-p_last.y),step, final_q);

	/*ROS_INFO("~~~OTRA VEZ~~~");
	for(int i=0;i<path.poses.size();i++)
		ROS_INFO("x:%f y:%f",path.poses[i].position.x,path.poses[i].position.y);
	*/
	return path;		
}

//Añade un punto al array
void SimpleCPP::AddPointToPath(float x, float y, geometry_msgs::Quaternion q)
{
	geometry_msgs::Point p;
	p.x=x;
	p.y=y;
	//Add to path
	geometry_msgs::Pose pose;
	pose.position=p;
	pose.orientation=q;
	path.poses.push_back(pose);
	//ROS_INFO("x:%f y:%f",x,y);
}

//Añade un conjunto de puntos en una direccion X al Path
geometry_msgs::Point SimpleCPP::AddXLaneToPath(geometry_msgs::Point start, float long_x, float generating_step, geometry_msgs::Quaternion q)
{
	if (long_x<0)//signo del step
		generating_step=-1*(generating_step);

	for (int i_x=0; abs(i_x)<abs(long_x); i_x=i_x+generating_step)//largo
	{
		AddPointToPath(i_x+start.x, start.y, q);
	}
	
	//Añadir punto final
	AddPointToPath(start.x+long_x, start.y, q);
	
	geometry_msgs::Point p;
	p.x=start.x+long_x;
	p.y=start.y;
	return p;

}

//Añade un conjunto de puntos en una direccion Y al Path
geometry_msgs::Point SimpleCPP::AddYLaneToPath(geometry_msgs::Point start, float long_y, float generating_step, geometry_msgs::Quaternion q)
{
	if (long_y<0)//signo del step
		generating_step=-1*(generating_step);

	for (int i_y=0; abs(i_y)<abs(long_y); i_y=i_y+generating_step)//largo
	{
		AddPointToPath(start.x, start.y+i_y, q);
	}
	
	//Añadir punto final
	AddPointToPath(start.x, start.y+long_y, q);
	
	geometry_msgs::Point p;
	p.x=start.x;
	p.y= start.y+long_y;
	return p;

}

//Función auxiliar para añadir carriles de puntos
void SimpleCPP::AddLaneToPath(geometry_msgs::Point start, float long_lane, float signed_generating_step, int axis, geometry_msgs::Quaternion q)
{
	float i_x=0;
	float i_y=0;

	for (int i=0; abs(i)<long_lane; i=i+signed_generating_step)//largo
	{
		if(axis==1)i_x=i;
		if(axis==2)i_y=i;

		AddPointToPath(start.x+i_x, start.y+i_y, q);
	}
	
	//Añadir punto final
	//AddPointToPath(end.x, end.y);

}
