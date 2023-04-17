#include "ros/ros.h"
//#include "irobot_fcpp_simul/FCPP_in.h"
#include "fcppstorage_service_class.h"

#include "geometry_msgs/Point32.h"
#include "geometry_msgs/Polygon.h"

#include <math.h>


int main(int argc, char **argv)
{
  ros::init(argc, argv, "defectos_in_storage_server");
  ros::NodeHandle n;

    double xmin, xmax, ymin, ymax;

    //xmin=0; xmax=23.0; ymin=0.0; ymax=39.0;
    xmin=0; xmax=7.66; ymin=0.0; ymax=13;

    double herr_proa=2.0/3;
    double herr_popa=3.0/3;
    double herr_babor=4.0/3;

    double long_robot=herr_popa+herr_proa;
    double long_2_robot=long_robot*0.5;
    double herr_babor_2=herr_babor*0.5;

    double radius=sqrt(herr_babor_2*herr_babor_2+
                       long_2_robot*long_2_robot);

//    double xmin_ch, xmax_ch, ymin_ch, ymax_ch;

//    xmin_ch=0.0; xmax_ch=3.0;
//    ymin_ch=0.0; ymax_ch=6.0;

    double long_chapa_x=8;//8;
    double long_chapa_y=4;//14;

    double long_robot_x, long_robot_y;
    long_robot_x=0.58; long_robot_y=0.44;

    double tras_herrx=40;//15; //Sacar de la proyeccion
    double tras_herry=40;//15;

    //Parametros herramienta
    //?¿?¿?¿?¿?¿



    FCPPStorage_Service_Class fcpp_srv(long_robot_x, long_robot_y,
                                       long_chapa_x, long_chapa_y,
                                       tras_herrx,tras_herry,
                                       radius);

//    FCPPStorage_Service_Class fcpp_srv(xmin, xmax, ymin, ymax,
//                                       herr_babor, herr_proa, herr_popa,
//                                       radius);



    //Defectos
    geometry_msgs::Point32 p; p.z=0.0;

//Datos muy grandes
//    geometry_msgs::Polygon poly0;
//    p.x= 7; p.y=2;   poly0.points.push_back(p);
//    p.x= 3; p.y=15;   poly0.points.push_back(p);
//    p.x= 5; p.y=18;   poly0.points.push_back(p);
//    p.x= 6; p.y=20;   poly0.points.push_back(p);
//    p.x= 12; p.y=15.5; poly0.points.push_back(p);
//    fcpp_srv.addPolydefect(poly0);

//    geometry_msgs::Polygon poly1;
//    p.x= 7;   p.y=30;     poly1.points.push_back(p);
//    p.x= 2;   p.y=35;     poly1.points.push_back(p);
//    p.x= 5.5; p.y=38.5;   poly1.points.push_back(p);
//    fcpp_srv.addPolydefect(poly1);

//    geometry_msgs::Polygon poly2;
//    p.x= 10; p.y=35;     poly2.points.push_back(p);
//    p.x= 15; p.y=38.8;     poly2.points.push_back(p);
//    p.x= 19; p.y=35;   poly2.points.push_back(p);
//    p.x= 21; p.y=25;     poly2.points.push_back(p);
//    p.x= 20; p.y=2;     poly2.points.push_back(p);
//    fcpp_srv.addPolydefect(poly2);

//Datos escalados pero muy grandes
//    geometry_msgs::Polygon poly0;
//    p.x= 7/3; p.y=2/3;   poly0.points.push_back(p);
//    p.x= 3/3; p.y=15/3;   poly0.points.push_back(p);
//    p.x= 5/3; p.y=18/3;   poly0.points.push_back(p);
//    p.x= 6/3; p.y=20/3;   poly0.points.push_back(p);
//    p.x= 12/3; p.y=15.5/3; poly0.points.push_back(p);
//    fcpp_srv.addPolydefect(poly0);

//    geometry_msgs::Polygon poly1;
//    p.x= 7/3;   p.y=30/3;     poly1.points.push_back(p);
//    p.x= 2/3;   p.y=35/3;     poly1.points.push_back(p);
//    p.x= 5.5/3; p.y=38.5/3;   poly1.points.push_back(p);
//    fcpp_srv.addPolydefect(poly1);

//    geometry_msgs::Polygon poly2;
//    p.x= 10/3; p.y=35/3;     poly2.points.push_back(p);
//    p.x= 15/3; p.y=38.8/3;     poly2.points.push_back(p);
//    p.x= 19/3; p.y=35/3;   poly2.points.push_back(p);
//    p.x= 21/3; p.y=25/3;     poly2.points.push_back(p);
//    p.x= 20/3; p.y=2/3;     poly2.points.push_back(p);
//    fcpp_srv.addPolydefect(poly2);


    geometry_msgs::Polygon poly0;
    p.x= 7/3; p.y=8/3;   poly0.points.push_back(p);
    p.x= 3/3; p.y=15/3;   poly0.points.push_back(p);
    p.x= 5/3; p.y=18/3;   poly0.points.push_back(p);
    p.x= 6/3; p.y=20/3;   poly0.points.push_back(p);
    p.x= 12/3; p.y=15.5/3; poly0.points.push_back(p);
    fcpp_srv.addPolydefect(poly0);

    geometry_msgs::Polygon poly1;
    p.x= 7/3;   p.y=30/3;     poly1.points.push_back(p);
    p.x= 2.9/3;   p.y=35/3;     poly1.points.push_back(p);
    p.x= 5.5/3; p.y=38.5/3;   poly1.points.push_back(p);
    fcpp_srv.addPolydefect(poly1);

    geometry_msgs::Polygon poly2;
    p.x= 10/3; p.y=35/3;     poly2.points.push_back(p);
    p.x= 15/3; p.y=38/3;     poly2.points.push_back(p);
    p.x= 19/3; p.y=35/3;   poly2.points.push_back(p);
    p.x= 21/3; p.y=28/3;     poly2.points.push_back(p);
    p.x= 20/3; p.y=25/3;     poly2.points.push_back(p);
    fcpp_srv.addPolydefect(poly2);


//        geometry_msgs::Polygon poly0;
//        p.x= xmin; p.y=ymin;   poly0.points.push_back(p);
//        p.x= xmin; p.y=ymax;   poly0.points.push_back(p);
//        p.x= xmax; p.y=ymax;   poly0.points.push_back(p);
//        p.x= xmax; p.y=ymin;   poly0.points.push_back(p);
//        fcpp_srv.addPolydefect(poly0);


    fcpp_srv.loop();


  ros::spin();

  return 0;
}
