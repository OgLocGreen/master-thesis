#ifndef CUTTER_FUNCTIONS_H
#define CUTTER_FUNCTIONS_H

#endif

#include <geometry_msgs/Polygon.h>
#include <geometry_msgs/Point.h>

#include <CGAL/Cartesian.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Point_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/intersections.h>
#include <CGAL/Boolean_set_operations_2.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 Point_2;
typedef K::Segment_2 Segment_2;
typedef CGAL::Polygon_2<K> Polygon_2;
typedef K::Intersect_2 Intersect_2;

typedef CGAL::Polygon_with_holes_2<K>                Polygon_with_holes_2;
typedef std::list<Polygon_with_holes_2>                       Poly_vec_2;

//Funciones relacionadas con la interseccion entre poligonos.
    //Empleadas para estudiar la relación de la superficie del defecto con las distintas zonas de trabajo.


Polygon_2 rosPoly2cgalPoly(geometry_msgs::Polygon poly_ros)
{
    Polygon_2 poly_cgal_return;

    for(int i=poly_ros.points.size()-1; i>=0; i--)
    //for(int i=0; i<poly_ros.points.size(); i++)
    {
        Point_2 p_cgal(poly_ros.points.at(i).x,
                       poly_ros.points.at(i).y);
        poly_cgal_return.push_back(p_cgal);
    }

    return poly_cgal_return;
}
geometry_msgs::Polygon cgalPoly2rosPoly(Polygon_2 poly_cgal)
{
    geometry_msgs::Polygon poly_ros_return;

    for(int i=poly_cgal.size()-1; i>=0 ; i--)
    {
        geometry_msgs::Point32 p_ros;
        p_ros.x=to_double(poly_cgal.vertex(i).x());
        p_ros.y=to_double(poly_cgal.vertex(i).y());

        poly_ros_return.points.push_back(p_ros);
    }

    return poly_ros_return;
}


std::vector<geometry_msgs::Polygon> intersectPolygonWithOtherPolygons
                                   (geometry_msgs::Polygon poly,
                                    std::vector<geometry_msgs::Polygon> cutters_vec,
                                    std::vector<int> &vec_cutter_id)
{
    //Conversion a CGAL
    Polygon_2 cgal_poly = rosPoly2cgalPoly(poly);

    std::vector<Polygon_2> cutter_cgal_vec;
    for(auto & elem: cutters_vec)
    {
        cutter_cgal_vec.push_back(rosPoly2cgalPoly(elem));
    }

    //Interseccion
    std::vector<geometry_msgs::Polygon> cutpoly_vec;
    int i_cutter_id=0;
    for(auto & elem:cutter_cgal_vec)
    {
        // Compute the intersection of P and Q.
        Poly_vec_2                  intR;
        //Poly_vec_2::const_iterator  it;
        CGAL::intersection (cgal_poly, elem, std::back_inserter(intR));

        //std::cout << "The intersection:" << std::endl;
        for (auto it = intR.begin(); it != intR.end(); ++it)
        {
          //std::cout <<"interseccion ";
          //print_polygon_with_holes (*it);

          geometry_msgs::Polygon cutpoly_ros;
          //Polygon_2 cutpoly_cgal;

          Polygon_2 cutpoly_cgal = it->outer_boundary();

          cutpoly_ros=cgalPoly2rosPoly(cutpoly_cgal);
          cutpoly_vec.push_back(cutpoly_ros);
          //if(vec_cutter_id!=NULL)
        }
        if(intR.size()>0)vec_cutter_id.push_back(i_cutter_id);

        std::cout<<i_cutter_id<<std::endl;
        i_cutter_id++;
    }

    return cutpoly_vec;
}
