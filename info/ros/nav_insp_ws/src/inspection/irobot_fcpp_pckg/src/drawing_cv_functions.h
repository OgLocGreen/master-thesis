#ifndef DRAWING_FUNCTIONS_H
#define DRAWING_FUNCTIONS_H

#endif // DRAWING_FUNCTIONS_H


#include "geometry_msgs/Polygon.h"
#include "geometry_msgs/Point.h"
#include "geometry_msgs/Point32.h"

#include <sstream>

//OpenCV
#include <opencv2/opencv.hpp>

using namespace cv;

//Funciones empleadas para la representacion de las distintas figuras

struct rgbcolor_struct
{
    double r;
    double g;
    double b;
};

void dibujaPolygonSegmentsOpenCv(geometry_msgs::Polygon poligono, Mat imagen, float k=50, float k_line=10)
{
    //RNG rng(12345);//random color
    double r255=rand()%205+50;//rng.uniform(0,255);
    double g255=rand()%205+50;
    double b255=rand()%205+50;

    for (int i=0; i<poligono.points.size()-1;i++)
    {

        Point p1((poligono.points[i].x)*k,(poligono.points[i].y)*k);
        Point p2((poligono.points[i+1].x)*k,(poligono.points[i+1].y)*k);
        line(imagen, p1,p2,CV_RGB(r255, g255, b255),k_line);
}

    Point p1((poligono.points[poligono.points.size()-1].x)*k,(poligono.points[poligono.points.size()-1].y)*k);
    Point p2((poligono.points[0].x)*k,(poligono.points[0].y)*k);
    line(imagen, p1,p2,CV_RGB(r255, g255, b255),k_line);
        //circle(traj, Point(x, y), 1, CV_RGB(color[0], color[1], color[2]), 2);
    //circle(imagen, Point(original_shape.points[i].x,original_shape.points[i].y),1,CV_RGB(0, 255, 0), 2)

}

void dibujaPolygonSegmentsOpenCv(geometry_msgs::Polygon poligono, Mat imagen, double r, double g, double b, float k=50, float k_line=10)
{
    //RNG rng(12345);//random color
    //double r255=rand()%205+50;//rng.uniform(0,255);
    //double g255=rand()%205+50;
    //double b255=rand()%205+50;

    for (int i=0; i<poligono.points.size()-1;i++)
    {

        Point p1((poligono.points[i].x)*k,(poligono.points[i].y)*k);
        Point p2((poligono.points[i+1].x)*k,(poligono.points[i+1].y)*k);
        line(imagen, p1,p2,CV_RGB(r, g, b),k_line);

}

    Point p1((poligono.points[poligono.points.size()-1].x)*k,(poligono.points[poligono.points.size()-1].y)*k);
    Point p2((poligono.points[0].x)*k,(poligono.points[0].y)*k);
    line(imagen, p1,p2,CV_RGB(r, g, b),k_line);
        //circle(traj, Point(x, y), 1, CV_RGB(color[0], color[1], color[2]), 2);
    //circle(imagen, Point(original_shape.points[i].x,original_shape.points[i].y),1,CV_RGB(0, 255, 0), 2)

}
void dibujaPolygonVertexOpenCv(geometry_msgs::Polygon poligono, Mat imagen, float k=50)
{

    for (int i=0; i<=poligono.points.size()-1;i++)
    {

        Point p1((poligono.points[i].x)*k,(poligono.points[i].y)*k);
        circle(imagen, p1,5,CV_RGB(255, 0, 0),-1);
    }


    //line(imagen, p1,p2,CV_RGB(0, 255, 0));
        //circle(traj, Point(x, y), 1, CV_RGB(color[0], color[1], color[2]), 2);
    //circle(imagen, Point(original_shape.points[i].x,original_shape.points[i].y),1,CV_RGB(0, 255, 0), 2)

}

void dibujaArrowsFromPointVectorOpenCv(std::vector<geometry_msgs::Point> vector, Mat imagen, float k=50)
{
    //bool step_by_step=true;
    for (int i=1; i<=vector.size()-1;i++)
    {

        Point p_start((vector.at(i-1).x)*k,(vector.at(i-1).y)*k);
        Point p_arrow((vector.at(i).x)*k,(vector.at(i).y)*k);
        //circle(imagen, p1,2,CV_RGB(0, 255, 0),1);
        //arrowedLine(imagen,p_start,p_arrow,CV_RGB(0, 255, 0),1 ,8,0,0.05);
        line(imagen,p_start,p_arrow,CV_RGB(0, 255, 0),3);
    }


    //line(imagen, p1,p2,CV_RGB(0, 255, 0));
        //circle(traj, Point(x, y), 1, CV_RGB(color[0], color[1], color[2]), 2);
    //circle(imagen, Point(original_shape.points[i].x,original_shape.points[i].y),1,CV_RGB(0, 255, 0), 2)

}
