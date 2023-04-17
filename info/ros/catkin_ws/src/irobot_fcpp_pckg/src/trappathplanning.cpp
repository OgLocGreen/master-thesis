#include "trappathplanning.h"


void TrapPathPlanning::changeXYValues(geometry_msgs::Polygon &poly)
{
    for(auto & elem : poly.points )
    {
        geometry_msgs::Point32 aux_p;
        aux_p.x=elem.y;
        aux_p.y=elem.x;

        elem.x=aux_p.x;
        elem.y=aux_p.y;
    }
}

TrapPathPlanning::TrapPathPlanning(geometry_msgs::Polygon poly, double path_step, TYPE_OF_PATH type)
{
    step=path_step;
    type_of_path=type;

    if(type==Y_CTE)
    {
        changeXYValues(poly);
    }

    std::vector<geometry_msgs::Point> vertices;
    std::vector<geometry_msgs::Point> vertices_x_ini;
    std::vector<geometry_msgs::Point> vertices_x_end;

    //Se busca el valor mínimo de x (será el comienzo de los segmentos)

    double x_min= poly.points[0].x; //Se inicializa el minimo con el primero

    for(int i=0; i<poly.points.size(); i++)
    {
        geometry_msgs::Point p;
                             p.x=poly.points[i].x;
                             p.y=poly.points[i].y;
                             p.z=0;


       vertices.push_back(p);
    }

    std::sort(vertices.begin(), vertices.end(),f_sortingPointsByX);



    double x_ini = vertices.at(0).x;

    for(auto elem: vertices)
    {
        if (elem.x==x_ini)
            vertices_x_ini.push_back(elem);
        else
            vertices_x_end.push_back(elem);
    }

    geometry_msgs::Point p_ini_sup, p_end_sup;
    geometry_msgs::Point p_ini_inf, p_end_inf;


    type_of_polygon=TYPE_TRAP;
    //polygon=poly;

    //Guardado del punto/puntos de menor x
    if (vertices_x_ini.size()<2)
    {
        p_ini_sup=vertices_x_ini.at(0);
        p_ini_inf=vertices_x_ini.at(0);
        type_of_polygon=TYPE_TRIANG1_2;
    }
    else
    {
       if(vertices_x_ini.at(0).y>vertices_x_ini.at(1).y)
       {
           p_ini_sup=vertices_x_ini.at(0);
           p_ini_inf=vertices_x_ini.at(1);
       }
       else
       {
           p_ini_sup=vertices_x_ini.at(1);
           p_ini_inf=vertices_x_ini.at(0);
       }
    }

    //Guardado del punto/puntos de mayor x
    if (vertices_x_end.size()<2)
    {
        p_end_sup=vertices_x_end.at(0);
        p_end_inf=vertices_x_end.at(0);
        type_of_polygon=TYPE_TRIANG2_1;
    }
    else
    {
        if(vertices_x_end.at(0).y>vertices_x_end.at(1).y)
        {
            p_end_sup=vertices_x_end.at(0);
            p_end_inf=vertices_x_end.at(1);
        }
        else
        {
            p_end_sup=vertices_x_end.at(1);
            p_end_inf=vertices_x_end.at(0);
        }
    }


    //Se definen las rectas que definen el trapecio
       Point_2 p1_inf(p_ini_inf.x, p_ini_inf.y);
       Point_2 p2_inf(p_end_inf.x, p_end_inf.y);


       Segment_2 aux_seg_inf(p1_inf, p2_inf);
                 seg_inf=aux_seg_inf;


       Point_2 p1_sup(p_ini_sup.x, p_ini_sup.y);
       Point_2 p2_sup(p_end_sup.x, p_end_sup.y);

       Segment_2 aux_seg_sup(p1_sup, p2_sup);
                 seg_sup=aux_seg_sup;

}



std::vector<geometry_msgs::Point> TrapPathPlanning::generatePath()
{
        std::vector<geometry_msgs::Point> goals;

        double x_ini=CGAL::to_double(seg_sup.start().x());
        double x_end=CGAL::to_double(seg_sup.end().x());

        bool infsup_order=false;
        bool breakbool=false;

        for (double x_i=x_end; ; x_i=x_i - step)
        {
            geometry_msgs::Point sup_point, inf_point;



            if(x_i<=x_ini)
            {
                x_i=x_ini;
                breakbool=true;
            }

            Line_2 vert_line(Point_2(x_i,-10), //Generacion de la linea 'vertical' que se usa para intersectar con los segmentos 'superior' e 'inferior' del trapecio
                             Point_2(x_i,+10));

            CGAL::cpp11::result_of<Intersect_2(Segment_2, Line_2)>::type
            cut_sup=CGAL::intersection(seg_sup, vert_line);


            CGAL::cpp11::result_of<Intersect_2(Segment_2, Line_2)>::type
            cut_inf=CGAL::intersection(seg_inf, vert_line);


            Point_2* p_cut_sup= new Point_2(0,0);
            Point_2* p_cut_inf= new Point_2(0,0);
            if(cut_sup) p_cut_sup= boost::get<Point_2>(&*cut_sup);
            if(cut_inf) p_cut_inf = boost::get<Point_2>(&*cut_inf);

            Point_2 subpoint(CGAL::to_double(p_cut_sup->x()), CGAL::to_double(p_cut_sup->y()));
            Point_2 infpoint(CGAL::to_double(p_cut_inf->x()), CGAL::to_double(p_cut_inf->y()));

            sup_point.x=CGAL::to_double(subpoint.x());
            sup_point.y=CGAL::to_double(subpoint.y());

            inf_point.x=CGAL::to_double(infpoint.x());
            inf_point.y=CGAL::to_double(infpoint.y());

            if (infsup_order) //Se atiende al booleano para ir alterando el orden
            {
                if(cut_inf)goals.push_back(inf_point);
                if(cut_sup)goals.push_back(sup_point);
            }
            else
            {
                if(cut_sup)goals.push_back(sup_point);
                if(cut_inf)goals.push_back(inf_point);
            }

            infsup_order=!infsup_order;

            if (breakbool) break;
        }

    if(type_of_path==Y_CTE)
    {
        for (auto & elem: goals)
        {
            double aux_x=elem.x;
            elem.x=elem.y;
            elem.y=aux_x;
        }
    }

        last_computed_goals=goals;
        return goals;
}

std::vector<geometry_msgs::Point> TrapPathPlanning::computePathStartingFromNearestPoint(geometry_msgs::Point p)
{
    std::vector<geometry_msgs::Point> goals;
    geometry_msgs::Point p1, p2, pn, pn_1;
    p1=last_computed_goals.at(0);
    p2=last_computed_goals.at(1);
    pn_1=last_computed_goals.at(last_computed_goals.size()-2);
    pn=last_computed_goals.at(last_computed_goals.size()-1);

    int min_point_id;

    double min_dist=10000000000; //Sustituir por un valor

//   1 | | | 4 (n)
//     | | |
//   2 |_| | 3 (n-1)

    if(min_dist>f_euclideanDist(p1, p))
    {
        min_dist=f_euclideanDist(p1, p);
        min_point_id=1;
    }
    if(min_dist>f_euclideanDist(p2, p))
    {
        min_dist=f_euclideanDist(p2, p);
        min_point_id=2;
    }
    if(min_dist>f_euclideanDist(pn_1, p))
    {
        min_dist=f_euclideanDist(pn_1, p);
        min_point_id=3;
    }
    if(min_dist>f_euclideanDist(pn, p))
    {
        min_dist=f_euclideanDist(pn, p);
        min_point_id=4;
    }

    switch (min_point_id) {
    case 1:
    {
        return last_computed_goals;
        break;
    }
    case 2:
    {
        bool alternate=true;
        for(int i=0; i<last_computed_goals.size(); i++)
        {
            if (alternate)
                goals.push_back(last_computed_goals.at(i+1));
            else
                goals.push_back(last_computed_goals.at(i-1));

            alternate=!alternate;
        }
        return goals;
        break;
    }
    case 3:
    {
        for(int i=last_computed_goals.size()-1; i>=0; i--)
        {
            goals.push_back(last_computed_goals.at(i));
        }
        return goals;
        break;
    }
    case 4:
    {
        bool alternate=true;
        for(int i=last_computed_goals.size()-1; i>=0; i--)
        {
            if (alternate)
                goals.push_back(last_computed_goals.at(i-1));
            else
                goals.push_back(last_computed_goals.at(i+1));
            alternate=!alternate;
        }
        return goals;
        break;
    }
    }



}
