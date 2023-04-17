#include "gazebosimmovement.h"

GazeboSimMovement::GazeboSimMovement(string gaz_state_model_name, string frame_n, string ref_frame_n)
{
    q0.x=q0.y=q0.z=0.0; q0.w=1.0;

    q90.x=q90.y=0.0; q90.w=q90.z= 0.707;

    q180.x=q180.y=q180.w=0.0; q180.z=1.0;

    q270.x=q270.y=0.0; q270.w= -0.707; q270.z= 0.707;




    gazebo_state_model_name=gaz_state_model_name;
    frame_name=frame_n;
    reference_frame_name=ref_frame_n;

    set_state_pub= n_talker.advertise<gazebo_msgs::ModelState>("/gazebo/set_model_state", 1000);
}

void GazeboSimMovement::startSimulation()
{
    bool finished;
    int count=all_poses.poses.size()-1;
    int n_msgs=0;

    rotateAllPoses();

    ros::Rate loop_rate(25);//50);
    while(ros::ok() && !finished)
    {
            /*Publicacion de la pose del robot
            coupled_pose_msg.pose=coupled_pose;
            coupled_pose_msg.header.frame_id=mother_frame_name;
            coupled_pose_msg.header.stamp=ros::Time();
            coupled_pose_pub.publish(coupled_pose_msg);*/

            //Publicacion del estado del robot
            geometry_msgs::Pose pose_aux;

            pose_aux=all_poses.poses.at(count);

                        //            tf::Transform pose_chaparef_tf;
                        //            tf::poseMsgToTF(pose_chaparef, pose_chaparef_tf);

                        //            //Use the listener object to lookup the latest transform between the request.base_frame and the reference frame from the ARMarker message (which should be “camera_frame”):

                        //            tf::StampedTransform chapa_to_orig;
                        //            listener_.waitForTransform( "origin_of_the_universe","gaz_world", ros::Time(),ros::Duration(1.0));
                        //            listener_.lookupTransform( "origin_of_the_universe","gaz_world", ros::Time(0), chapa_to_orig);

//            Using the above information, transform the object pose into the target frame.

                        //            tf::Transform pose_gazref_tf;
                        //            pose_gazref_tf = chapa_to_orig * pose_chaparef_tf;

            //Return the transformed pose in the service response.



            model_state_msg.pose.position.x=-1*pose_aux.position.y+11.925;
            model_state_msg.pose.position.y=pose_aux.position.x+9.295;


            //model_state_msg.pose=pose_to_pub;

//            model_state_msg.pose.orientation.w= 0.707;
//            model_state_msg.pose.orientation.z= 0.707;
              model_state_msg.pose.orientation=pose_aux.orientation;




            model_state_msg.reference_frame=reference_frame_name;
            model_state_msg.model_name=gazebo_state_model_name;
            set_state_pub.publish(model_state_msg);
            n_msgs++;

            //Creacion frame TF del robot acoplado
//            transform.setOrigin( tf::Vector3(coupled_pose.position.x, coupled_pose.position.y, coupled_pose.position.z) );
//            transform.setRotation( tf::Quaternion(coupled_pose.orientation.x, coupled_pose.orientation.y, coupled_pose.orientation.z, coupled_pose.orientation.w) );
//            br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), mother_frame_name, tf_newframe_name));

            ros::spinOnce();

            loop_rate.sleep();
            count--;

            if (count<5)
//            if (count>all_poses.poses.size()-5)
                finished=true;
    }

    ROS_INFO("Enviados %d msgs", n_msgs);


}

void GazeboSimMovement::readPosesFromMarkerTopic(string topic)
{
    ros::NodeHandle n;

    sub_pathtopic = n.subscribe<visualization_msgs::Marker>(topic, 1000, &GazeboSimMovement::readPosesFromMarkerTopic_callback, this);

    while(ros::ok() && !topic_read)
        {ros::spinOnce();}



    original_poses=MarkerMsg2PoseArraymsg(aux_marker_msg);
    ROS_INFO("Obtenido array de %d poses", original_poses.poses.size()-1);



    read_count=0;
    topic_read=false;
}

void GazeboSimMovement::readPosesFromArrayTopic(string topic)
{
    ros::NodeHandle n;

    sub_pathtopic = n.subscribe<geometry_msgs::PoseArray>(topic, 1000, &GazeboSimMovement::readPosesFromArrayTopic_callback, this);

    while(ros::ok() && !topic_read)
        {ros::spinOnce();}



    original_poses=aux_array_msg;
    ROS_INFO("Obtenido array de %d poses", original_poses.poses.size()-1);


    int orient_debug=0;
    geometry_msgs::Quaternion prev_q;
    for (auto & elem: original_poses.poses)
    {
        if(orient_debug==0)
        {
            orient_debug++;
            prev_q=elem.orientation;
            ROS_INFO("x=%f y=%f z=%f w=%f", elem.orientation.x,elem.orientation.y,elem.orientation.z,elem.orientation.w);
            continue;
        }

        if(abs(prev_q.w - elem.orientation.w)>0.1
           ||
           abs(prev_q.z - elem.orientation.z)>0.1)
        {
         orient_debug++;
         ROS_INFO("x=%f y=%f z=%f w=%f", elem.orientation.x,elem.orientation.y,elem.orientation.z,elem.orientation.w);
        }

        prev_q=elem.orientation;
    }

    ROS_INFO("%d cambios de orientaciones", orient_debug);


    read_count=0;
    topic_read=false;
}

void  GazeboSimMovement::readPosesFromArrayTopic_callback(const geometry_msgs::PoseArray::ConstPtr& msg)
{
  if(!topic_read)
  {
  read_count++;

  if(read_count>20)
  {
      aux_array_msg = *msg;
      topic_read=true;
  }
    }

}



geometry_msgs::PoseArray GazeboSimMovement::MarkerMsg2PoseArraymsg(visualization_msgs::Marker marker)
{
    geometry_msgs::PoseArray return_pa;

    for (auto & elem: marker.points)
    {
        geometry_msgs::Pose p;
        p.position.x=elem.x;
        p.position.y=elem.y;

        return_pa.poses.push_back(p);
    }

    return return_pa;
}

bool GazeboSimMovement::areQuatEqual(geometry_msgs::Quaternion q1, geometry_msgs::Quaternion q2)
{
    return abs(q1.x-q2.x)<0.1 &&
           abs(q1.y-q2.y)<0.1 &&
           abs(q1.z-q2.z)<0.1 &&
           abs(q1.w-q2.w)<0.1;
}

void  GazeboSimMovement::readPosesFromMarkerTopic_callback(const visualization_msgs::Marker::ConstPtr& msg)
{
  if(!topic_read)
  {
  read_count++;

  if(read_count>20)
  {
      aux_marker_msg = *msg;
      topic_read=true;
  }
    }

}


void GazeboSimMovement::readPosesFromCSV()
{
    //TO-DO
}

void GazeboSimMovement::interpolatePoses(float dist)
{

    for (int i=0; i<original_poses.poses.size()-1; i++)
    {
        geometry_msgs::Pose final_pose_i=original_poses.poses.at(i+1);

        all_poses.poses.push_back(original_poses.poses.at(i));

        geometry_msgs::Pose pose_i=original_poses.poses.at(i);
        geometry_msgs::Pose old_pose_i=original_poses.poses.at(i);

        ROS_INFO("Vertice numero %d", i);


        int i_debug=0;
           while(pose_i.position.x!=final_pose_i.position.x
                 ||
                 pose_i.position.y!=final_pose_i.position.y)
        {
            pose_i=getPoseInSegment(old_pose_i,final_pose_i,dist);

            all_poses.poses.push_back(pose_i);
            old_pose_i=pose_i;

            i_debug++;
        }
           ROS_INFO("      %d interpolaciones", i_debug);

    }

    ROS_INFO("Aumentado el array a %d poses", all_poses.poses.size()-1);

    geometry_msgs::Pose prev_pose;

    prev_pose=all_poses.poses.at(0);

//for(auto&elem:all_poses.poses)
//{
//    if ((abs(elem.position.x-prev_pose.position.x)>5 || abs(elem.position.y-prev_pose.position.y)>5))
//        elem=prev_pose;
//    prev_pose=elem;
//}

}

void GazeboSimMovement::rotateAllPoses()
{
    for(auto & elem: all_poses.poses)
    {
        if(areQuatEqual(elem.orientation,q0))
        {
            elem.orientation=q90;
            continue;
        }
        if(areQuatEqual(elem.orientation,q90))
        {
            elem.orientation=q180;
            continue;
        }
        if(areQuatEqual(elem.orientation,q180))
        {
            elem.orientation=q270;
            continue;
        }
        if(areQuatEqual(elem.orientation,q270))
        {
            elem.orientation=q0;
            continue;
        }
    }

    ROS_INFO("Poses rotated");

}



float GazeboSimMovement::getThetaFromTwoPoints(float x1, float y1,float x2, float y2)
{
    return atan2(y2 - y1, x2 - x1);
}


geometry_msgs::Pose GazeboSimMovement::getPoseInSegment(geometry_msgs::Pose ini, geometry_msgs::Pose end, float dist)
{
        if (hypot(ini.position.x-end.position.x, ini.position.y-end.position.y)<=dist)
                return end;
        else
        {
                float theta = getThetaFromTwoPoints(ini.position.x, ini.position.y, end.position.x, end.position.y);

                geometry_msgs::Point vector;
                                                         vector.x=cos(theta);
                                                         vector.y=sin(theta);

                geometry_msgs::Pose return_pose;
                                                         return_pose.position.x=ini.position.x+dist*vector.x;
                                                         return_pose.position.y=ini.position.y+dist*vector.y;
                                                         return_pose.orientation=ini.orientation;

                return return_pose;
        }
}
