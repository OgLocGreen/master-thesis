#ifndef TRAPDECOMPOSITION_H
#define TRAPDECOMPOSITION_H

#define SITUATION_INITIAL 0
#define SITUATION_1VERTEX 1
#define SITUATION_2VERTICES 2
#define SITUATION_3ORMOREVERTICES 3
#define SITUATION_LOOKFORNEXT 4


#define VERTEX_NOT_USED 0
#define VERTEX_USED_AS_END 1
#define VERTEX_USED_AS_START 2
#define VERTEX_RESERVED 3

#include "geometry_msgs/Polygon.h"
#include "geometry_msgs/Point.h"
#include "geometry_msgs/Point32.h"

#include <cmath>


#include <CGAL/Cartesian.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Point_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Line_2.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/intersections.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
//typedef CGAL::Cartesian K;
typedef K::Point_2 Point_2;
typedef K::Segment_2 Segment_2;
typedef K::Line_2 Line_2;
typedef CGAL::Polygon_2<K> Polygon_2;
typedef K::Intersect_2 Intersect_2;


#define SITUATION_INITIAL 0
#define SITUATION_1VERTEX 1
#define SITUATION_2VERTICES 2
#define SITUATION_3ORMOREVERTICES 3
#define SITUATION_LOOKFORNEXT 4


#define VERTEX_NOT_USED 0
#define VERTEX_USED_AS_END 1
#define VERTEX_USED_AS_START 2
#define VERTEX_RESERVED 3
#define VERTEX_EMPTY 10

#define MAX_DISTANCE_IN_SEGMENT 999999;
#define MAX_DISTANCE 999999;
#define MIN_Y -999999;


//Estructura que representa un vertice
    //Contiene la posicion del mismo junto a sus segmentos adyacentes y una etiqueta informativa
struct vertexStruct
{
   geometry_msgs::Point posc; //Posicion del vertice
   Point_2 point;
//Segmentos a los que pertenece
   Segment_2 prev_seg;
   Segment_2 next_seg;

    int label = VERTEX_NOT_USED;
};

//Clase encarga de la descomposicion de poligonos irregulares en trapecios

class TrapDecomposition
{
public:
    TrapDecomposition(geometry_msgs::Polygon poly);

protected:
    geometry_msgs::Polygon original_shape;

   std::vector<Point_2> points_vector;
   Polygon_2 pgn;

   std::vector<Segment_2> segment_vector;

protected:
    double f_manhattan_dist(Point_2 p1, Point_2 p2);
    double f_manhattan_dist(double p1_x, double p1_y, double p2_x, double p2_y);

    static bool f_sortingVertexByX(vertexStruct v_a, vertexStruct v_b)
    {
        return (v_a.point.x() < v_b.point.x()); //Ascending order
    }

    bool isLabelInVertexVector(std::vector<vertexStruct> points_vector, int label);
    bool isLabelInVertexVector(std::vector<vertexStruct> points_vector, int label, int &i);

    geometry_msgs::Polygon clockwisePolygon(geometry_msgs::Polygon orig_poly);


public:
    void getXDecomposition(std::vector<geometry_msgs::Polygon> &trapezoids_result, std::vector<geometry_msgs::Point32> &new_polygon_vertices);
    void getYDecomposition(std::vector<geometry_msgs::Polygon> &trapezoids_result, std::vector<geometry_msgs::Point32> &new_polygon_vertices);


public:
    geometry_msgs::Polygon getPolygon(){return original_shape;}


public:
    geometry_msgs::Polygon orderPolygon(geometry_msgs::Polygon poly);
    void changeXYValues(geometry_msgs::Polygon &poly);
    void changeXYmembers();
};

#endif // TRAPDECOMPOSITION_H
