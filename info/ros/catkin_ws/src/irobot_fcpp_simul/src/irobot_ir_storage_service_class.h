#ifndef FCPPSTORAGE_SERVICE_CLASS_H
#define FCPPSTORAGE_SERVICE_CLASS_H

#include "ros/ros.h"

#include "std_msgs/String.h"

#include "geometry_msgs/Polygon.h"
#include "geometry_msgs/Point32.h"
#include <geometry_msgs/PolygonStamped.h>
#include <geometry_msgs/PoseArray.h>
#include <visualization_msgs/Marker.h>
#include <geometry_msgs/Quaternion.h>
#include <std_msgs/Bool.h>
#include <jsk_recognition_msgs/PolygonArray.h>

#include "irobot_fcpp_simul/IROBOT_ir_data.h"
#include <irobot_fcpp_simul/ComputeDefectsDecompAction.h>
#include <irobot_inspection_pckg/polygonArray.h>
#include <irobot_inspection_pckg/getPartialPanoramaAction.h>
#include <irobot_inspection_pckg/getCompletePanoramaAction.h>
#include <irobot_inspection_pckg/getPolygonsAction.h>

#include "../../irobot_fcpp_pckg/src/trappathplanning.h"


#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>

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

//Declaracion de estructuras para los defectos
enum dir_rep{YPOS, YNEG, XPOS, XNEG, OUT};

//const geometry_msgs::Quaternion q0{};
//const geometry_msgs::Quaternion q90{};
//const geometry_msgs::Quaternion q180{};
//const geometry_msgs::Quaternion q270{};

//// Cuidado con los 0.0s que hay. Habria que sustituirlos por una variable

class IROBOT_ir_Storage_Service_Class
{
protected:

        string reference_frame_string;

        geometry_msgs::Quaternion q0;
        geometry_msgs::Quaternion q90;
        geometry_msgs::Quaternion q180;
        geometry_msgs::Quaternion q270;

    ///Poligonos y zonas

        //Vector de Defectos

        std::vector<irobot_fcpp_simul::defecto> defectos_vec;


        std::vector<geometry_msgs::Polygon> poly_vector;
        int n_defectos;


        std::vector<geometry_msgs::Polygon> working_Hzones_vector;
        std::vector<geometry_msgs::Polygon> working_Czones_vector;
        std::vector<geometry_msgs::Polygon> inspection_zones_vector;


        geometry_msgs::Polygon rotation_zone;
        rectangle_limits rl_rotation_zone;


      ///Paths de FCPP

        std::vector<geometry_msgs::PoseArray> paths_Hzones_vector;
        std::vector<geometry_msgs::PoseArray> paths_Czones_vector;

        std::vector<geometry_msgs::PoseArray> paths_inspection_zones_vector;

        //std::vector<std::vector<geometry_msgs::Pose>> paths_Czones_vector;
        std::vector<std::vector<geometry_msgs::PoseArray>> paths_inspection_vector;
        std::vector<std::vector<geometry_msgs::PoseArray>> paths_defects_vector;
        std::vector<std::vector<geometry_msgs::PoseArray>> paths_tool_defects_vector;


        bool path_calculated, path_inspection_calculated, path_viz_bool;

        std_msgs::Bool is_reparating;

    ///Datos de entrada

        //Caracteristicas chapa
        double longa_x, longa_y;

        //Características robot
        double longr_x, longr_y;

        //Características herr
        double longh_x, longh_y;
        double trash_x, trash_y;

        //Características cam
        double longc_x, longc_y;
        double trasc_x, trasc_y;

        double rot_radius;

///


        ros::NodeHandle n;
        ros::ServiceServer service;

///Rviz

        bool publish_vizmsgs_bool=false;
        bool publish_vizmsgs_firstactivation=true;

        ros::Publisher reparation_bool_pub;
        //Publicadores Rviz
        ros::Publisher poly_chapa_pub;
        ros::Publisher footprint_pub;
        ros::Publisher footprintH_pub;
        ros::Publisher footprintC_pub;
//      ros::Publisher footprintherr_pub;
        ros::Publisher rot_zone_pub;
        std::vector<ros::Publisher> vec_poligonos_pubs;
        std::vector<ros::Publisher> vec_trapecios_pubs;
        std::vector<ros::Publisher> vec_trapeciosarrays_pubs;
        std::vector<ros::Publisher> vec_zonas_cam_pubs;
        std::vector<ros::Publisher> vec_zonas_herr_pubs;
        std::vector<ros::Publisher> vec_path_zonas_herr_pubs;
        std::vector<ros::Publisher> vec_path_zonas_cam_pubs;
        std::vector<ros::Publisher> vec_path_defects_pubs;
        ros::Publisher ordered_path_pub;
        ros::Publisher ordered_toolpath_pub;

        ros::Publisher ordered_msgpath_pub;
        geometry_msgs::PoseArray ordered_path_array_msg;

        //Mensajes Rviz


        geometry_msgs::PolygonStamped poly_chapa_vizmsg;
        geometry_msgs::PolygonStamped poly_footprint_vizmsg;
        geometry_msgs::PolygonStamped poly_Hfootprint_vizmsg;
        geometry_msgs::PolygonStamped poly_Cfootprint_vizmsg;




        geometry_msgs::PolygonStamped poly_rotzone_vizmsg;
        std::vector<geometry_msgs::PolygonStamped> vec_poligonos_vizmsg;
        std::vector<geometry_msgs::PolygonStamped> vec_trapecios_vizmsg;
        std::vector<jsk_recognition_msgs::PolygonArray> vec_trapeciosarray_vizmsg;
        std::vector<geometry_msgs::PolygonStamped> vec_zonas_cam_vizmsg;
        std::vector<geometry_msgs::PolygonStamped> vec_zonas_herr_vizmsg;
        std::vector<visualization_msgs::Marker> vec_paths_zonasherr_vizmsg;
        std::vector<visualization_msgs::Marker> vec_path_zonascam_vizmsg;
        std::vector<visualization_msgs::Marker> vec_path_defects_vizmsg;
        visualization_msgs::Marker ordered_path_vizmsg;
        visualization_msgs::Marker ordered_toolpath_vizmsg;




        int defect_goal;
        int inspection_goal;








        bool service_function(irobot_fcpp_simul::IROBOT_ir_data::Request &req,
                              irobot_fcpp_simul::IROBOT_ir_data::Response &res);

        geometry_msgs::Polygon rectlimits2rosPolygon(rectangle_limits limits);

        void adjustRectlimits2maxmin(rectangle_limits &rl, double xmin, double xmax, double ymin, double ymax);
        bool isInsideRectLimits(double x, double y, rectangle_limits rl);

        void translatePoints(std::vector<geometry_msgs::Point> &vector, double tras_x, double tras_y);

        std::vector<geometry_msgs::PoseArray> preparePathForExecution(std::vector<geometry_msgs::PoseArray> &path);
        geometry_msgs::PoseArray inversePathOrder(geometry_msgs::PoseArray path);


        void updateVizMsgs();
        void initializeVizPubs();



        visualization_msgs::Marker PoseVector2VizMarker(std::vector<geometry_msgs::Pose> path);
        visualization_msgs::Marker PoseVector2VizMarker(geometry_msgs::PoseArray path);


        geometry_msgs::Polygon clockwisePolygon(geometry_msgs::Polygon orig_poly);


        void sortPathsByX(std::vector<geometry_msgs::PoseArray> &path);
        void sortPosesByX(geometry_msgs::PoseArray &path);


        void sortPathsByY(std::vector<geometry_msgs::PoseArray> &path);
        void sortPosesByY(geometry_msgs::PoseArray &path);



        geometry_msgs::Point nearestPointInsideRectLimits(double x, double y, rectangle_limits rl);
public:
        //Constructor clasico
        IROBOT_ir_Storage_Service_Class();



        void computePanorama(int id_zona);
        void mergePanoramas();
        void computePolyDetection();



        void addPolydefect(geometry_msgs::Polygon poly);

        geometry_msgs::Polygon getPolyDefectAt(int i);

        int getNumberOfDefects(){return poly_vector.size();}

        void computeWorkingZones();
        std::vector<geometry_msgs::Polygon> computeWorkingZones(double long_act_x, double long_act_y,
                                                                double tras_act_x, double tras_act_y);


        std::vector<geometry_msgs::Polygon> computeWorkingZones(double long_area_x, double long_area_y,
                                                                double long_robot_x, double long_robot_y,
                                                                double long_act_x, double long_act_y,
                                                                double tras_act_x, double tras_act_y);

        std::vector<geometry_msgs::Polygon> computeInspectionZones(double long_act_x, double long_act_y,
                                                                   double tras_act_x, double tras_act_y);

        std::vector<geometry_msgs::Polygon> computeInspectionZones(double long_area_x, double long_area_y,
                                                                double long_robot_x, double long_robot_y,
                                                                double long_act_x, double long_act_y,
                                                                double tras_act_x, double tras_act_y);


        cv::Mat computePossibleWorkingArea(cv::Mat img_areatotal, cv::Mat img_robot, cv::Mat img_herr, GradosRotacion rotation);
        cv::Mat rotatek90Mat(cv::Mat img, GradosRotacion rotation);

        void computeRotationZone();

        void computeDefectsDecomposition();

        void computeWorkingZoneFCPP(int id_zona);
        void computeInspectionZoneFCPP(int id_zona);
        void computeDefectFCPP(int id_defect);

        void loop();
};

        double getXMaxOfPath(geometry_msgs::PoseArray path);
        double getYMaxOfPath(geometry_msgs::PoseArray path);

#endif // FCPPSTORAGE_SERVICE_CLASS_H
