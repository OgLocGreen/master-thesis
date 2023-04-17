#ifndef FCPPSTORAGE_SERVICE_CLASS_H
#define FCPPSTORAGE_SERVICE_CLASS_H

#include "ros/ros.h"
#include "std_msgs/String.h"

#include "geometry_msgs/Polygon.h"
#include "geometry_msgs/Point32.h"

#include "irobot_fcpp_simul/FCPP_in.h"


//OpenCV
#include <opencv2/opencv.hpp>

using namespace cv;


#include <sstream>
#include <string>
#include <iostream>
#include <math.h>

enum GradosRotacion{rot0, rot90, rot180, rot270};

struct rectangle_limits
{
    double xmin, xmax, ymin, ymax;
};

//// Cuidado con los 0.0s que hay. Habria que sustituirlos por una variable

class FCPPStorage_Service_Class
{
protected:

        double xmin, xmax, ymin, ymax;

        int n_defectos;

        //Vector de Poligonos
        std::vector<geometry_msgs::Polygon> poly_vector;
        std::vector<geometry_msgs::Polygon> working_zones_vector;

        geometry_msgs::Polygon rotation_zone;

        //Características robot
        double herr_lat;
        double herr_proa;
        double herr_popa;
        double rot_radius;

        //Características robot2
        double longx_r, longy_r;
        double h_x, h_y;




        ros::NodeHandle n;
        ros::ServiceServer service;

        bool service_function(irobot_fcpp_simul::FCPP_in::Request &req,
                              irobot_fcpp_simul::FCPP_in::Response &res);

        geometry_msgs::Polygon rectlimits2rosPolygon(rectangle_limits limits);

        void adjustRectlimits2maxmin(rectangle_limits &rl, double xmin, double xmax, double ymin, double ymax);
        bool isInsideRectLimits(double x, double y, rectangle_limits rl);

public:
        //Constructor clasico
        FCPPStorage_Service_Class(double xm, double xM, double ym, double yM,
                                  double hlat, double hproa, double hpopa,
                                  double robot_radius);
        //Nuevo constructor//Sin parametros herr
        FCPPStorage_Service_Class(double long_robotX, double long_robotY, double long_chapaX, double long_chapaY,
                                  double tras_herrx, double tras_herry,
                                  double robot_radius);


        void addPolydefect(geometry_msgs::Polygon poly);

        geometry_msgs::Polygon getPolyDefectAt(int i);

        int getNumberOfDefects(){return poly_vector.size();}

        void computeWorkingZones();
        void computeWorkingZones2();

        void computeRotationZone();
        cv::Mat computePossibleWorkingArea(cv::Mat img_areatotal, cv::Mat img_robot, cv::Mat img_herr, GradosRotacion rotation);
        cv::Mat rotatek90Mat(cv::Mat img, GradosRotacion rotation);

        void loop();
};

#endif // FCPPSTORAGE_SERVICE_CLASS_H
