#ifndef WORKING_ZONES_H
#define WORKING_ZONES_H

#endif // WORKING_ZONES_H

#include <geometry_msgs/Polygon.h>

using namespace std;

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


std::vector<geometry_msgs::Polygon> getWorkingZones(rectangle_limits complete_zone,
                                         double herr_lat, double herr_proa, double herr_popa)
{

    double complete_longx=complete_zone.xmax-complete_zone.xmin;
    double complete_longy=complete_zone.ymax-complete_zone.ymin;

    double min_herrp=std::min(herr_proa, herr_popa);
    double max_herrp=std::max(herr_proa, herr_popa);

    std::vector<geometry_msgs::Polygon> working_zones;

    rectangle_limits zone1, zone2,
                zone3_top, zone4_top,
                zone5_bot, zone6_bot,
                zone7_out, zone8_out, zone9_out, zone10_out;

    //Zona 1
    zone1.xmin= herr_lat;
    zone1.ymin=herr_popa;
    zone1.xmax=complete_longx;
    zone1.ymax=complete_longy-herr_proa;

    //Zona 2
    zone2.xmin=0.0;
    zone2.ymin=herr_proa;
    zone2.xmax=zone1.xmin;
    zone2.ymax=complete_longy-herr_popa;

    //Zona 7
    zone7_out.xmin=0.0;
    zone7_out.ymin=0.0;
    zone7_out.xmax=herr_popa;
    zone7_out.ymax=herr_proa;

    //Zona 8
    zone8_out.xmin=0.0;
    zone8_out.ymin=complete_longy-herr_popa;
    zone8_out.xmax=herr_proa;
    zone8_out.ymax=complete_longy;

    //Zona 9
    zone9_out.xmin=complete_longx-herr_popa;
    zone9_out.ymin=complete_longy-herr_proa;
    zone9_out.xmax=complete_longx;
    zone9_out.ymax=complete_longy;

    //Zona 10
    zone10_out.xmin=complete_longx-herr_proa;
    zone10_out.ymin=0.0;
    zone10_out.xmax=complete_longx;
    zone10_out.ymax=herr_popa;


    //Zona 3
    zone3_top.xmin=zone1.xmin;
    zone3_top.ymin=complete_longy-herr_proa;//zone2.ymax;
    zone3_top.xmax=zone9_out.xmin;////hdywqbyhe
    zone3_top.ymax=complete_longy;


    //Zona 4
    zone4_top.xmin=zone8_out.xmax;
    zone4_top.ymin=zone2.ymax;
    zone4_top.xmax=zone2.xmax;
    zone4_top.ymax=complete_longy;

    //Zona 5
    zone5_bot.xmin=zone1.xmin;
    zone5_bot.ymin=0;//min_herrp;
    zone5_bot.xmax=zone10_out.xmin;
    zone5_bot.ymax=herr_popa;//max_herrp;

    //Zona 6
    zone6_bot.xmin=herr_popa;
    zone6_bot.ymin=0.0;
    zone6_bot.xmax=zone2.xmax;//complete_longx-herr_proa;
    zone6_bot.ymax=zone2.ymin;//min_herrp;


    working_zones.push_back(rectlimits2rosPolygon(zone1));     working_zones.push_back(rectlimits2rosPolygon(zone2));
    working_zones.push_back(rectlimits2rosPolygon(zone3_top)); working_zones.push_back(rectlimits2rosPolygon(zone4_top));
    working_zones.push_back(rectlimits2rosPolygon(zone5_bot)); working_zones.push_back(rectlimits2rosPolygon(zone6_bot));
    working_zones.push_back(rectlimits2rosPolygon(zone7_out)); working_zones.push_back(rectlimits2rosPolygon(zone8_out));
    working_zones.push_back(rectlimits2rosPolygon(zone9_out)); working_zones.push_back(rectlimits2rosPolygon(zone10_out));

    return working_zones;
}


