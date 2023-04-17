#ifndef COORDS_INFO_H
#define COORDS_INFO_H

#endif // COORDS_INFO_H

#include <geometry_msgs/Polygon.h>
#include <geometry_msgs/Point32.h>
#include "working_zones.h"

void createStructsObjectsAndCo(rectangle_limits &chapa_limits, std::vector<geometry_msgs::Polygon> &defectos_vector)
{
    //Limites de la chapa
    chapa_limits.xmin= 0.0;
    chapa_limits.xmax=23.0;
    chapa_limits.ymin= 0.0;
    chapa_limits.ymax=39.0;




//    //Defectos
//    geometry_msgs::Point32 p; p.z=0.0;

//    geometry_msgs::Polygon poly0;
//    p.x= 7; p.y=2;   poly0.points.push_back(p);
//    p.x= 3; p.y=15;   poly0.points.push_back(p);
//    p.x= 5; p.y=18;   poly0.points.push_back(p);
//    p.x= 6; p.y=20;   poly0.points.push_back(p);
//    p.x= 9; p.y=15.5; poly0.points.push_back(p);
//    defectos_vector.push_back(poly0);

//    geometry_msgs::Polygon poly1;
//    p.x= 7;   p.y=30;     poly1.points.push_back(p);
//    p.x= 2;   p.y=35;     poly1.points.push_back(p);
//    p.x= 5.5; p.y=38.5;   poly1.points.push_back(p);
//    defectos_vector.push_back(poly1);

//    geometry_msgs::Polygon poly2;
//    p.x= 17; p.y=35;     poly2.points.push_back(p);
//    p.x= 18; p.y=37;     poly2.points.push_back(p);
//    p.x= 19; p.y=35.5;   poly2.points.push_back(p);
//    p.x= 21; p.y=36;     poly2.points.push_back(p);
//    p.x= 20; p.y=34;     poly2.points.push_back(p);
//    defectos_vector.push_back(poly2);

    //Defectos
    geometry_msgs::Point32 p; p.z=0.0;

    geometry_msgs::Polygon poly0;
    p.x= 7; p.y=2;   poly0.points.push_back(p);
    p.x= 3; p.y=15;   poly0.points.push_back(p);
    p.x= 5; p.y=18;   poly0.points.push_back(p);
    p.x= 6; p.y=20;   poly0.points.push_back(p);
    p.x= 12; p.y=15.5; poly0.points.push_back(p);
    defectos_vector.push_back(poly0);

    geometry_msgs::Polygon poly1;
    p.x= 7;   p.y=30;     poly1.points.push_back(p);
    p.x= 2;   p.y=35;     poly1.points.push_back(p);
    p.x= 5.5; p.y=38.5;   poly1.points.push_back(p);
    defectos_vector.push_back(poly1);

    geometry_msgs::Polygon poly2;
    p.x= 10; p.y=35;     poly2.points.push_back(p);
    p.x= 15; p.y=38.8;     poly2.points.push_back(p);
    p.x= 19; p.y=35;   poly2.points.push_back(p);
    p.x= 21; p.y=25;     poly2.points.push_back(p);
    p.x= 20; p.y=2;     poly2.points.push_back(p);
    defectos_vector.push_back(poly2);

}


