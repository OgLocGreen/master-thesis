#ifndef TRAPPATHPLANNING_H
#define TRAPPATHPLANNING_H



#include <geometry_msgs/Polygon.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Point32.h>

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

enum TYPE_OF_PATH{X_CTE, Y_CTE};
enum TYPE_OF_TRAP{TYPE_TRAP, TYPE_TRIANG1_2, TYPE_TRIANG2_1};

using namespace std;


//Clase que permite trazar trayectorias en los poligonos
//Por defecto realiza las pasadas en valores constantes de x.
class TrapPathPlanning
{
protected:
    double step;
    Segment_2 seg_inf, seg_sup;
    TYPE_OF_TRAP type_of_polygon;
    TYPE_OF_PATH type_of_path;

    std::vector<geometry_msgs::Point> last_computed_goals;

    static bool f_sortingPointsByX(geometry_msgs::Point p_1, geometry_msgs::Point p_2)
    {
        return (p_1.x < p_2.x); //Ascending order
    }
    double f_euclideanDist(geometry_msgs::Point p1, geometry_msgs::Point p2)
    {
        return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
    }
    void changeXYValues(geometry_msgs::Polygon &poly);



public:
    TrapPathPlanning(geometry_msgs::Polygon poly, double path_step, TYPE_OF_PATH type=X_CTE);


    std::vector<geometry_msgs::Point>generatePath();

    std::vector<geometry_msgs::Point> computePathStartingFromNearestPoint(geometry_msgs::Point p);
};

#endif // TRAPPATHPLANNING_H
