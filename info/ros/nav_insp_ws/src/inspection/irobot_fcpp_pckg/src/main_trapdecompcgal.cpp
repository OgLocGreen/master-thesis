#include <ros/ros.h>



#include "drawing_cv_functions.h"

#include <geometry_msgs/Point32.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Polygon.h>


#include <CGAL/Cartesian.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Point_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/intersections.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 Point_2;
typedef K::Segment_2 Segment_2;
typedef CGAL::Polygon_2<K> Polygon_2;
typedef K::Intersect_2 Intersect_2;



#include "trapdecomposition.h"
#include "trappathplanning.h"
#include "cutter_functions.h"

#include "coords_info.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "main_trapdecompcgal");
    ros::NodeHandle nh;

//    Point_2 points[] = { Point_2(0,0), Point_2(5.1,0), Point_2(1,1), Point_2(0.5,6)};
//    Polygon_2 pgn(points, points+4);


//    Segment_2 seg=pgn.edge(0);

//    Segment_2 seg2(Point_2(2,-1000),Point_2(2,+1000));

//    CGAL::cpp11::result_of<Intersect_2(Segment_2, Segment_2)>::type
//    prueba=CGAL::intersection(seg, seg2);

//    Point_2* p = boost::get<Point_2>(&*prueba);

//    double x = CGAL::to_double(p->x());
//    std::cout << p->x() << std::endl;

    geometry_msgs::Polygon poly_example;

    geometry_msgs::Point32 p;

//p.x=2; p.y=2; p.z=0;
//poly_example.points.push_back(p);
//p.x=3; p.y=6;
//poly_example.points.push_back(p);
//p.x=8; p.y=4;
//poly_example.points.push_back(p);
//p.x=7; p.y=2.5;
//poly_example.points.push_back(p);
//p.x=9; p.y=1;
//poly_example.points.push_back(p);





//p.x=2; p.y=6; p.z=0;
//poly_example.points.push_back(p);
//p.x=4.2; p.y=9;
//poly_example.points.push_back(p);
//p.x=9; p.y=9.1;
//poly_example.points.push_back(p);
//p.x=8; p.y=7;
//poly_example.points.push_back(p);
//p.x=5.6; p.y=6.9;
//poly_example.points.push_back(p);
//p.x=5; p.y=6.1;
//poly_example.points.push_back(p);
//p.x=5.7; p.y=6.5;
//poly_example.points.push_back(p);
//p.x=6; p.y=5;
//poly_example.points.push_back(p);
//p.x=4; p.y=4;
//poly_example.points.push_back(p);



//    p.x=2; p.y=8; p.z=0;
//    poly_example.points.push_back(p);
//    p.x=7; p.y=10;
//    poly_example.points.push_back(p);
//    p.x=5.2; p.y=12;
//    poly_example.points.push_back(p);
//    p.x=10; p.y=13;
//    poly_example.points.push_back(p);
//    p.x=15; p.y=10;
//    poly_example.points.push_back(p);
//    p.x=16; p.y=15;
//    poly_example.points.push_back(p);
//    p.x=18; p.y=14;
//    poly_example.points.push_back(p);
//    p.x=17; p.y=10;
//    poly_example.points.push_back(p);
//    p.x=19; p.y=9;
//    poly_example.points.push_back(p);
//    p.x=21; p.y=14;
//    poly_example.points.push_back(p);
//    p.x=23; p.y=9;
//    poly_example.points.push_back(p);
//    p.x=18.2; p.y=5;
//    poly_example.points.push_back(p);
//    p.x=12; p.y=6;
//    poly_example.points.push_back(p);
//    p.x=4; p.y=2;
//    poly_example.points.push_back(p);
//    p.x=5; p.y=5;
//    poly_example.points.push_back(p);

    //Apañado
    p.x=2; p.y=8; p.z=0;
    poly_example.points.push_back(p);
    p.x=7; p.y=10;
    poly_example.points.push_back(p);
    p.x=5; p.y=12;
    poly_example.points.push_back(p);
    p.x=10.1; p.y=13;
    poly_example.points.push_back(p);
    p.x=15; p.y=10.75;
    poly_example.points.push_back(p);
    p.x=16; p.y=15.5;
    poly_example.points.push_back(p);
    p.x=18; p.y=14;
    poly_example.points.push_back(p);
    p.x=17; p.y=10.25;
    poly_example.points.push_back(p);
    p.x=19; p.y=9;
    poly_example.points.push_back(p);
    p.x=21; p.y=14.1;
    poly_example.points.push_back(p);
    p.x=23; p.y=9;
    poly_example.points.push_back(p);
    p.x=18.2; p.y=5;
    poly_example.points.push_back(p);
    p.x=12.1; p.y=6;
    poly_example.points.push_back(p);
    p.x=4; p.y=2.1;
    poly_example.points.push_back(p);
    p.x=5.3; p.y=5.4;
    poly_example.points.push_back(p);






//    geometry_msgs::Polygon cutter;
//    p.x=5.0; p.y=0;
//    cutter.points.push_back(p);
//    p.x=5.0; p.y=20;
//    cutter.points.push_back(p);
//    p.x=10.0; p.y=20;
//    cutter.points.push_back(p);
//    p.x=10.0; p.y=0;
//    cutter.points.push_back(p);

//    std::vector<geometry_msgs::Polygon> vector_poly_cutters;
//    vector_poly_cutters.push_back(cutter);

//    std::vector<geometry_msgs::Polygon> vector_poly_result;
    //vector_poly_result= intersectPolygonWithOtherPolygons(poly_example, vector_poly_cutters);


    //prueboncio=rosPoly2cgalPoly(poly_example);
    //poly_example=cgalPoly2rosPoly(prueboncio);


    //changeXYValues(poly_example);
    //poly_example=orderPolygon(poly_example);

      TrapDecomposition badBunnyBabyBaBaBa(poly_example);
      std::vector<geometry_msgs::Point32> new_polygon_vertices;
      std::vector<geometry_msgs::Polygon> trapezoids_result;

      badBunnyBabyBaBaBa.getXDecomposition(trapezoids_result, new_polygon_vertices);



      namedWindow("Poligono",WINDOW_NORMAL);
      Mat imagen(2000,2000,CV_8UC3, Scalar(255,255,255));
      Mat imagen2(2000,2000,CV_8UC3, Scalar(255,255,255));

          dibujaPolygonSegmentsOpenCv(poly_example, imagen,0,0,0);

//          dibujaPolygonSegmentsOpenCv(vector_poly_cutters.at(0), imagen);
//          dibujaPolygonSegmentsOpenCv(vector_poly_result.at(0), imagen);


          geometry_msgs::Polygon poly_new;

          geometry_msgs::Point32 p_new;
          for (int i=0; i<new_polygon_vertices.size();i++)
          {
              p_new.x=new_polygon_vertices.at(i).x;//////CAMBIAR CUANDO SE CAMBIE DE TIPO DE REPRESENTACION.
              p_new.y=new_polygon_vertices.at(i).y;
              poly_new.points.push_back(p_new);
          }
          //dibujaPolygonVertexOpenCv(poly_new, imagen);
          dibujaPolygonVertexOpenCv(poly_new, imagen2);

     cv2:flip(imagen, imagen, 0);
     imshow("Poligono", imagen);

     imwrite("/home/irobot-user/Imágenes/poly.jpg", imagen);



     Mat aux_imagen2(2000,2000,CV_8UC3, Scalar(255,255,255));
     namedWindow("Poligonitos",WINDOW_NORMAL);
     //flip(imagen2, aux_imagen2, 0);
     //imshow("Poligonitos",aux_imagen2);
     waitKey();

     geometry_msgs::Point initial_point;
                          initial_point.x=0;
                          initial_point.y=0;

     for(auto &elem : trapezoids_result)
     {

         dibujaPolygonSegmentsOpenCv(elem, imagen2,100,100,100, 50,2);
         //flip(imagen2, aux_imagen2, 0);
         //imshow("Poligonitos",aux_imagen2);




         //waitKey();
//            TrapPathPlanning path(elem,0.5, Y_CTE);
//            std::vector<geometry_msgs::Point> path_result;
//            path_result = path.generatePath();
//            geometry_msgs::Point p;
//            p.x=30; p.y=0; p.z=0;
//            path_result = path.computePathStartingFromNearestPoint(p);

//            dibujaArrowsFromPointVectorOpenCv(path_result,imagen2,50);
         //dibujaPolygonSegmentsOpenCv(elem, imagen2);

//         initial_point.x=path_result.at(path_result.size()-1).x;
//         initial_point.y=path_result.at(path_result.size()-1 ).y;

         //flip(imagen2, aux_imagen2, 0);
         imshow("Poligonitos",imagen2);
         waitKey();

     }
     flip(imagen2, imagen2, 0);
     imshow("Poligonitos",imagen2);
    waitKey();

    imwrite("/home/irobot-user/Imágenes/decomp.jpg", imagen2);
    ///Path planning











    ROS_INFO("Hello world!");
}
