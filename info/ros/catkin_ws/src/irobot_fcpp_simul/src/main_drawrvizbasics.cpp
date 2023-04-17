#include <ros/ros.h>
#include <geometry_msgs/Point32.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Polygon.h>
#include <geometry_msgs/PolygonStamped.h>

#include <irobot_fcpp_simul/FCPP_in.h>
#include <irobot_fcpp_simul/FCPP_out.h>
#include <irobot_fcpp_simul/defecto.h>

#include <string>
#include "std_msgs/String.h"
#include <sstream>



struct rectangle_limits
{
    double xmin, xmax, ymin, ymax;
};
geometry_msgs::Polygon rectlimits2rosPolygon(rectangle_limits limits)
{
    geometry_msgs::Polygon poly_return;

    geometry_msgs::Point32 p;
    p.z=0.0;
    p.x=limits.xmin;
    p.y=limits.ymin;
                    poly_return.points.push_back(p);
    p.x=limits.xmin;
    p.y=limits.ymax;
                    poly_return.points.push_back(p);
    p.x=limits.xmax;
    p.y=limits.ymax;
                    poly_return.points.push_back(p);
    p.x=limits.xmax;
    p.y=limits.ymin;
                    poly_return.points.push_back(p);

    return poly_return;
}




int main(int argc, char **argv)
{
    ros::init(argc, argv, "main_drawrvizbasics");
    ros::NodeHandle nh;


    std::string reference_frame_string="chapa_orig";

    ros::ServiceClient client_chapa = nh.serviceClient<irobot_fcpp_simul::FCPP_in>("fcpp_data_service");

    irobot_fcpp_simul::FCPP_in srv_in;
    srv_in.request.get_working_zones=true;

    //srv.request.id_chapa de momento sin request
    if (!client_chapa.call(srv_in))
    {   ROS_ERROR("Failed to call defectos service!!!!!");   }

    rectangle_limits rl;
    rl.xmax= srv_in.response.xmax_chapa;
    rl.xmin= srv_in.response.xmin_chapa;
    rl.ymin= srv_in.response.ymin_chapa;
    rl.ymax= srv_in.response.ymax_chapa;

    //Poligonos con las zonas
    std::vector<geometry_msgs::PolygonStamped> vector_zonas;
    geometry_msgs::PolygonStamped psz;

    psz.header.frame_id=reference_frame_string;

//    psz.polygon=srv_in.response.zone0;
//    vector_zonas.push_back(psz);
//    psz.polygon=srv_in.response.zone1;
//    vector_zonas.push_back(psz);
//    psz.polygon=srv_in.response.zone2;
//    vector_zonas.push_back(psz);
//    psz.polygon=srv_in.response.zone3;
//    vector_zonas.push_back(psz);
//    psz.polygon=srv_in.response.zone4;
//    vector_zonas.push_back(psz);
//    psz.polygon=srv_in.response.zone5;
//    vector_zonas.push_back(psz);
//    psz.polygon=srv_in.response.zone6;
//    vector_zonas.push_back(psz);
//    psz.polygon=srv_in.response.zone7;
//    vector_zonas.push_back(psz);
//    psz.polygon=srv_in.response.zone8;
//    vector_zonas.push_back(psz);
//    psz.polygon=srv_in.response.zone9;
//    vector_zonas.push_back(psz);

    psz.polygon=srv_in.response.zone0;
    vector_zonas.push_back(psz);
    psz.polygon=srv_in.response.zone90;
    vector_zonas.push_back(psz);
    psz.polygon=srv_in.response.zone180;
    vector_zonas.push_back(psz);
    psz.polygon=srv_in.response.zone270;
    vector_zonas.push_back(psz);


    //Poligono footprint de la herramienta
    geometry_msgs::PolygonStamped herr_footprint_msg;
    double med_sim=0.05;
    geometry_msgs::Point32 p32;
    p32.z=0;
    p32.x=-med_sim; p32.y=-med_sim;
    herr_footprint_msg.polygon.points.push_back(p32);
    p32.x=-med_sim; p32.y=med_sim;
    herr_footprint_msg.polygon.points.push_back(p32);
    p32.x=+med_sim; p32.y=med_sim;
    herr_footprint_msg.polygon.points.push_back(p32);
    p32.x=+med_sim; p32.y=-med_sim;
    herr_footprint_msg.polygon.points.push_back(p32);



    herr_footprint_msg.header.frame_id="projected_coupled_tool";

    //Poligono footprint del robot
    geometry_msgs::PolygonStamped footprint_msg;

    p32.z=0;
    p32.x=-srv_in.response.long_robotx*0.5; p32.y=-srv_in.response.long_roboty*0.5;
    footprint_msg.polygon.points.push_back(p32);
    p32.x=-srv_in.response.long_robotx*0.5; p32.y=srv_in.response.long_roboty*0.5;
    footprint_msg.polygon.points.push_back(p32);
    p32.x=srv_in.response.long_robotx*0.5; p32.y=srv_in.response.long_roboty*0.5;
    footprint_msg.polygon.points.push_back(p32);
    p32.x=srv_in.response.long_robotx*0.5; p32.y=-srv_in.response.long_roboty*0.5;
    footprint_msg.polygon.points.push_back(p32);

    footprint_msg.header.frame_id="summit_xl_a_base_link";


    //Poligono con la chapa
    geometry_msgs::Polygon chapa_poly=rectlimits2rosPolygon(rl);

    geometry_msgs::PolygonStamped chapa_msg;
                                  chapa_msg.polygon=chapa_poly;
                                  chapa_msg.header.frame_id=reference_frame_string;


    //Poligono de los defectos

    ros::ServiceClient client_defectos = nh.serviceClient<irobot_fcpp_simul::FCPP_out>("fcpp_outdata_service");

    irobot_fcpp_simul::FCPP_out srv_out;

    if (!client_defectos.call(srv_out))
    {   ROS_ERROR("Failed to call defectos service!!!!!");   }

    std::vector<irobot_fcpp_simul::defecto> estructura_defecto = srv_out.response.defecto_out;

    std::vector<geometry_msgs::PolygonStamped> vector_poligonos;
    std::vector<geometry_msgs::PolygonStamped> vector_trapecios;

    int i=0;
    for(auto & elem: estructura_defecto)
    {
        geometry_msgs::PolygonStamped polys;
        polys.polygon=elem.ros_poly;
        polys.header.frame_id=reference_frame_string;

        vector_poligonos.push_back(polys);
        i++;

        int info_i=0;
        int zona_i=0;
        for(auto & elemz: elem.defecto_divpor_zonas)
        {
            ROS_INFO("-----Zona %f", zona_i);
            for(auto & elemt: elemz.trap_vec)
            {
                geometry_msgs::PolygonStamped traps;
                traps.polygon=elemt.ros_poly;
                traps.header.frame_id=reference_frame_string;

                vector_trapecios.push_back(traps);

                ROS_INFO("Trapecio %f", zona_i);
                info_i++;
            }
            zona_i++;
        }
    }

    //Publisher de la chaoa
    ros::Publisher chapa_pub = nh.advertise<geometry_msgs::PolygonStamped>("topic_poligono_chapa", 1000);
    ROS_INFO("Publisher de la chapa listo!");

    ros::Publisher footprint_pub = nh.advertise<geometry_msgs::PolygonStamped>("topic_poligono_footprint", 1000);
    ROS_INFO("Publisher del footprint listo!");

    ros::Publisher footprintherr_pub = nh.advertise<geometry_msgs::PolygonStamped>("topic_poligono_footprint_herr", 1000);
    ROS_INFO("Publisher del footprint listo!");

    std::string topic_poligono_defecto="topic_poligono_defecto";
    std::string topic_poligono_trapecio="topic_defecto";
    std::string topic_poligono_trapecio2="_trapecio";
    std::string topic_poligono_zonas="topic_poligono_zona";

    //Publishers de las zonas
    std::vector<ros::Publisher> vector_zonas_publishers;
    for(int i=0; i<vector_zonas.size(); i++)
    {
        std::string i_string = std::to_string(i);
        vector_zonas_publishers.push_back(nh.advertise<geometry_msgs::PolygonStamped>(topic_poligono_zonas+i_string, 1000));
    }
    ROS_INFO("Publishers de las zonas listo!");


    //Publishers de los defectos
    std::vector<ros::Publisher> vector_defectos_publishers;
    std::vector<ros::Publisher> vector_trapecios_publishers;


    for(int i=0; i<vector_poligonos.size(); i++)
    {
        std::string i_string = std::to_string(i);
        vector_defectos_publishers.push_back(nh.advertise<geometry_msgs::PolygonStamped>(topic_poligono_defecto+i_string, 1000));

        //Publishers de los trapecios
        for(int z=0; z<estructura_defecto.at(i).defecto_divpor_zonas.size(); z++)
        {
         for(int j=0; j<estructura_defecto.at(i).defecto_divpor_zonas.at(z).trap_vec.size(); j++)
         {
            std::string j_string = std::to_string(j);
            vector_trapecios_publishers.push_back(nh.advertise<geometry_msgs::PolygonStamped>(topic_poligono_trapecio+i_string+topic_poligono_trapecio2+j_string, 1000));
         }
        }

    }
    ROS_INFO("Publishers de los defectos listo!");




    //ROS_INFO("Publishers de los trapecios listo!");

    ros::Rate loop_rate(10);


    while(ros::ok())
    {

        chapa_pub.publish(chapa_msg);

        footprint_pub.publish(footprint_msg);
        footprintherr_pub.publish(herr_footprint_msg);

        for(int i=0;i<vector_zonas_publishers.size();i++)
        {
            vector_zonas_publishers.at(i).publish(vector_zonas.at(i));
        }

        for(int i=0;i<vector_defectos_publishers.size();i++)
        {
            vector_defectos_publishers.at(i).publish(vector_poligonos.at(i));
        }

        for(int i=0;i<vector_trapecios_publishers.size();i++)
        {
            vector_trapecios_publishers.at(i).publish(vector_trapecios.at(i));
        }

        ros::spinOnce();
        loop_rate.sleep();

         //ROS_INFO("pub");
    }


    return 0;
}
