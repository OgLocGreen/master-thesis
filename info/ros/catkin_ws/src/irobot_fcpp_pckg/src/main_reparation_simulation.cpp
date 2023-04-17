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
//#include "working_zones.h"

#include "coords_info.h"

//Declaracion de estructuras para los defectos
enum dir_rep{YPOS, YNEG, XPOS, XNEG, OUT};

struct defecto_simple
{
    geometry_msgs::Polygon ros_poly;
    dir_rep direccion_rep;
    bool reparado=false;
};
struct defecto_zona
{
    std::vector<defecto_simple> trapdecomp_vec;
    geometry_msgs::Polygon ros_poly;

    bool reparado=false;
    dir_rep direccion_rep;
    int zona;
};
struct defecto
{
    std::vector<defecto_zona> defecto_divpor_zonas_vec;
    geometry_msgs::Polygon ros_poly;
    bool reparado=false;
};

///Archivo principal que llama a las demas clases y funciones para simular un calculo de las descomposiciones y trayectorias a seguir

int main(int argc, char **argv)
{
    ros::init(argc, argv, "main_trapdecompcgal");
    ros::NodeHandle nh;


/// 1.- Se inicializan los valores iniciales de la chapa y los defectos presentes
    double herr_proa=2.0;
    double herr_popa=4.0;
    double herr_babor=1.0;

    rectangle_limits chapa_limits;
    std::vector<geometry_msgs::Polygon> data_defectos_vec;

    createStructsObjectsAndCo(chapa_limits, data_defectos_vec);

/// 2.- Se obtienen las zonas de trabajo

    geometry_msgs::Polygon chapa_poly=rectlimits2rosPolygon(chapa_limits);

    std::vector<geometry_msgs::Polygon> working_zones_vec;

    working_zones_vec=getWorkingZones(chapa_limits,herr_babor, herr_proa, herr_popa);

/// 3.- Se muestran los datos de comienzo

    Mat img=Mat::ones(4000,2500,CV_8UC3);
    img=cv::Scalar(255,255,255);

    rgbcolor_struct color_chapa{0,0,0};
    rgbcolor_struct color_workingzones{106,106,106};
    rgbcolor_struct color_defectos{255,0,0};

    for(auto & elem: working_zones_vec)
    {
        dibujaPolygonSegmentsOpenCv(elem,  img,color_workingzones.r,
                                               color_workingzones.g,
                                               color_workingzones.b, 100,5);
    }

    dibujaPolygonSegmentsOpenCv(chapa_poly,img,color_chapa.r,
                                               color_chapa.g,
                                               color_chapa.b, 100);

    for(auto & elem: data_defectos_vec)
    {
        dibujaPolygonSegmentsOpenCv(elem,  img,color_defectos.r,
                                               color_defectos.g,
                                               color_defectos.b, 100);
    }
    cv2:flip(img, img, 0);
    namedWindow("Planteamiento inicial",WINDOW_NORMAL);
    imshow("Planteamiento inicial", img);
    waitKey();

/// 4.- Se dividen los defectos por zonas

    std::vector<defecto> vector_defectos;

    //Se carga la forma original
    for(auto & elem: data_defectos_vec)
    {
        defecto d;
        d.ros_poly=elem;
        vector_defectos.push_back(d);
    }

    //Se dividen por zonas
    for(auto & elem: vector_defectos)
    {
        std::vector<geometry_msgs::Polygon> vector_poly_result;
        std::vector<int> vector_id_cutter;

        vector_poly_result= intersectPolygonWithOtherPolygons(elem.ros_poly, working_zones_vec, vector_id_cutter);

        int i=0;
        for(auto & elem2: vector_poly_result)
        {
        defecto_zona dz;
        dz.ros_poly=elem2;
        dz.zona=vector_id_cutter.at(i);
        elem.defecto_divpor_zonas_vec.push_back(dz);
        i++;
        }
    }
    //Se dibujan los resultados
    Mat img2=Mat::ones(4000,2500,CV_8UC3);
    img2=cv::Scalar(255,255,255);

    for(auto & elem: vector_defectos)
    {
        for(auto & elem2: elem.defecto_divpor_zonas_vec)
        {
        dibujaPolygonSegmentsOpenCv(elem2.ros_poly, img2, 100);
        }
    }


flip(img2, img2, 0);
namedWindow("Division por zonas",WINDOW_NORMAL);
imshow("Division por zonas", img2);
waitKey();


/// 5.- A cada zona se le asocia el sentido de avance

for(auto & elem: vector_defectos)
{
    for (auto & elem2: elem.defecto_divpor_zonas_vec)
    {
        switch (elem2.zona)
        {
        case 0:
            elem2.direccion_rep=YPOS;
            break;
        case 1:
            elem2.direccion_rep=YNEG;
            break;
        case 2: case 3:
            elem2.direccion_rep=XNEG;
            break;
        case 4: case 5:
            elem2.direccion_rep=XPOS;
            break;
        case 6: case 7: case 8: case 9:
            elem2.direccion_rep=OUT;
        }
   }
}

/// 6.- Se descompone trapezoidalmente cada uno de los defectos

for(auto & elem: vector_defectos)
{
    for (auto & elemz: elem.defecto_divpor_zonas_vec)
    {
        TrapDecomposition decomposer(elemz.ros_poly);
        std::vector<geometry_msgs::Point32> new_polygon_vertices;
        std::vector<geometry_msgs::Polygon> trapezoids_result;

        switch (elemz.direccion_rep)//Distinta descomposicion en funcion de la direccion de reparacion
        {
        case XNEG: case XPOS:
            decomposer.getYDecomposition(trapezoids_result, new_polygon_vertices);
            break;


        case YPOS: case YNEG:
            decomposer.getXDecomposition(trapezoids_result, new_polygon_vertices);
            break;


        case OUT:
            break;
        }



        std::vector<defecto_simple> vec_defectosimple;
        for(auto & elemt: trapezoids_result)
        {
            defecto_simple ds;
            ds.direccion_rep=elemz.direccion_rep;
            ds.ros_poly=elemt;

            vec_defectosimple.push_back(ds);
        }
        elemz.trapdecomp_vec=vec_defectosimple;
   }
}

/// 7.- Se muestran las descomposiciones

Mat img3=Mat::ones(4000,2500,CV_8UC3);
img3=cv::Scalar(255,255,255);
Mat img4=Mat::ones(4000,2500,CV_8UC3);
img4=cv::Scalar(255,255,255);

for(auto & elem: vector_defectos)
{
    for (auto & elemz: elem.defecto_divpor_zonas_vec)
    {
        for( auto & elemt: elemz.trapdecomp_vec)
        {
           dibujaPolygonSegmentsOpenCv(elemt.ros_poly, img3, 100, 5);
        }
    }
}

/// 8.- Se representa un path-planning basico

for(auto & elem: vector_defectos){for (auto & elemz: elem.defecto_divpor_zonas_vec){
        for( auto & elemt: elemz.trapdecomp_vec)
        {
            TYPE_OF_PATH type_of_path;
            if(elemz.direccion_rep==XPOS || elemz.direccion_rep==XNEG)
                type_of_path=Y_CTE;
            else
                type_of_path=X_CTE;

            TrapPathPlanning path(elemt.ros_poly,0.15, type_of_path);
            std::vector<geometry_msgs::Point> path_result;
            path_result = path.generatePath();
            dibujaArrowsFromPointVectorOpenCv(path_result,img4,100);
        }}}
flip(img3, img3, 0);
namedWindow("Descomposicion trapezoidal",WINDOW_NORMAL);
imshow("Descomposicion trapezoidal", img3);
flip(img4, img4, 0);
namedWindow("Paths",WINDOW_NORMAL);
imshow("Paths", img4);
waitKey();


ROS_INFO("Hellou world 2!");
}
