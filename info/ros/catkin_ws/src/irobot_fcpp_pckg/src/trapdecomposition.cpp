#include "trapdecomposition.h"

double TrapDecomposition::f_manhattan_dist(Point_2 p1, Point_2 p2)
{
    return f_manhattan_dist(CGAL::to_double(p1.x()), CGAL::to_double(p1.y()), CGAL::to_double(p2.x()), CGAL::to_double(p2.y()));
}

double TrapDecomposition::f_manhattan_dist(double p1_x, double p1_y, double p2_x, double p2_y)
{

    return (std::abs(p1_x-p2_x)+std::abs(p1_y-p2_y));
}

bool TrapDecomposition::isLabelInVertexVector(std::vector<vertexStruct> points_vector, int label)
{
    //Chequea si existen vertices con la etiqueta indicada como parametro
    int unused;
    return isLabelInVertexVector(points_vector, label, unused);
}

bool TrapDecomposition::isLabelInVertexVector(std::vector<vertexStruct> vertex_vector, int label, int &i)
{
    i=0;
    for(auto & elem: vertex_vector)
    {
        if(elem.label==label)
            return true;
     i++;
    }
}

geometry_msgs::Polygon TrapDecomposition::clockwisePolygon(geometry_msgs::Polygon orig_poly) //Función que ordena los puntos de un poligono de ROS en sentido de las agujas del reloj
{
//Recibe un poligono y lo devuelve ordenado

    double sum_x=0;
    double sum_y=0;

    for(int i=0; i<orig_poly.points.size(); i++)
    {
        sum_x+=orig_poly.points[i].x;
        sum_y+=orig_poly.points[i].y;
    }
    geometry_msgs::Point center;
                         center.x=sum_x/orig_poly.points.size();
                         center.y=sum_y/orig_poly.points.size();

   //atan2(orig_poly.points[i].y - M.y, orig_poly.points[i].x - M.x);

   std::vector<double> polarangle_vector;
   for(int i=0; i<orig_poly.points.size(); i++)
   {
    double polar_angle=atan2(orig_poly.points[i].y - center.y,
                             orig_poly.points[i].x - center.x);
    polarangle_vector.push_back(polar_angle);
   }

   std::vector<double> sorted_polarangle_vector=polarangle_vector;

   std::sort(sorted_polarangle_vector.begin(), sorted_polarangle_vector.end());

   geometry_msgs::Polygon return_poly;
   for(int i=0; i<orig_poly.points.size(); i++)
   {
       std::vector<double>::iterator it=std::find(polarangle_vector.begin(), polarangle_vector.end(), sorted_polarangle_vector.at(i));
       int index = std::distance(polarangle_vector.begin(), it);

       geometry_msgs::Point32 p;
                              p.x=orig_poly.points[index].x;
                              p.y=orig_poly.points[index].y;
                              p.z=0;
       return_poly.points.push_back(p);
   }

   return return_poly;
}

void TrapDecomposition::changeXYValues(geometry_msgs::Polygon &poly)
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

void TrapDecomposition::changeXYmembers()
{
    changeXYValues(original_shape);
    original_shape=orderPolygon(original_shape);

    geometry_msgs::Polygon poly=original_shape;


    points_vector.clear();
    pgn.clear();
    segment_vector.clear();

//Se guardan los veertices en un vector de vertices y en un objeto poligono
    for(auto & elem:poly.points)
    {
        Point_2 auxP(elem.x, elem.y);
        points_vector.push_back(auxP);

        pgn.push_back(auxP);
    }

//Se construye el vector de segmentos
    segment_vector.push_back(Segment_2(points_vector.at(0),points_vector.at(1)));//1er elemento
    for(int i=1; i<points_vector.size()-1; i++)
        segment_vector.push_back(Segment_2(points_vector.at(i),points_vector.at(i+1)));        //2o - N-1 segmento
    segment_vector.push_back(Segment_2(points_vector.at(points_vector.size()-1),points_vector.at(0)));  //N segmento
}

 geometry_msgs::Polygon TrapDecomposition::orderPolygon(geometry_msgs::Polygon poly)
{
   geometry_msgs::Polygon poly_return;

    //Buscar el más a la izda, y ordenar a partir de él
    int i_minx=0;
    int ix=0;
    double minx=999999;
    for(auto & elem : poly.points )
    {
        if(elem.x<minx)
        {
            i_minx=ix;
        }
        ix++;
    }

        int i_size=0;

        for(int i=i_minx; i>0; i--)
        {
            i_size++;
            if (i_size>poly.points.size()) break;
            poly_return.points.push_back(poly.points.at(i));
        }

        for(int i=0; i<i_minx; i++)
        {
            i_size++;
            if (i_size>poly.points.size()) break;
            poly_return.points.push_back(poly.points.at(i));
        }
    return poly_return;
}



TrapDecomposition::TrapDecomposition(geometry_msgs::Polygon poly) //Constructor
{
    original_shape=poly;


//Se guardan los veertices en un vector de vertices y en un objeto poligono
    for(auto & elem:poly.points)
    {
        Point_2 auxP(elem.x, elem.y);
        points_vector.push_back(auxP);

        pgn.push_back(auxP);
    }

//Se construye el vector de segmentos
    segment_vector.push_back(Segment_2(points_vector.at(0),points_vector.at(1)));//1er elemento
    for(int i=1; i<points_vector.size()-1; i++)
        segment_vector.push_back(Segment_2(points_vector.at(i),points_vector.at(i+1)));        //2o - N-1 segmento
    segment_vector.push_back(Segment_2(points_vector.at(points_vector.size()-1),points_vector.at(0)));  //N segmento

}

void TrapDecomposition::getXDecomposition(std::vector<geometry_msgs::Polygon> &trapezoids_result, std::vector<geometry_msgs::Point32> &new_polygon_vertices)
{
    ///Recibe un poligono y devuelve el conjunto de trapecios que lo componen
    /// Se supone no obstaculos intermedios
    /// Las proyecciones se realizan sobre el eje x ("rectas verticales")

    //Evaluacion de proyeccion por dentro del poligono
    double evaluating_step=0.025;       //distancia en Y a la que se evalua punto
    double x_extreme=100;               //extremo con el que se traza segmento para comprobar si el punto esta dentro del poligono
    double aux_evaluate=10.0;


    std::vector<vertexStruct> new_vertex_vector;

    std::vector<Point_2> new_points_vector;    //Crear un vector con los vertices del poligono
    std::vector<int> segment_id_of_vertex_vector;           //Crear un vector con los vertices del poligono

    int num_v=points_vector.size();     //Numero de segmentos y vertices

    for(int i_v=0; i_v<num_v; i_v++)//Se recorren todos los vertices
    {
        std::vector<Point_2> aux_candidate_vertices_vector; //Vector auxiliar de vertices candidatos para cada vertice original explorado
        //std::vector<int> aux_candidate_id_vector;//Vector analogo al de arriba que incluya el id del segmento del poligono en el que se encuentra
        std::vector<Segment_2> aux_candidate_segment_vector;

        //Calculo de la posicion en el vector segmentos adyacentes
        int prev_s, next_s;
            prev_s=i_v-1;
            next_s=i_v;
        if(prev_s<0)        prev_s=num_v-1;
        //if(next_s>(num_v-1))  next_s=0;

        //std::cout<<prev_s<<"---"<<next_s<<std::endl;

        //Booleano que se activará si hay un nuevo vertice que incluir
        bool thereIsNewVertex_bool=false;


        for(int i_s=0; i_s<num_v; i_s++)//Se recorren todos segmentos (excepto los adyacentes)
        {
            if (i_s==prev_s || i_s==next_s) continue;

            Line_2 v_prolong(points_vector.at(i_v),
                             Point_2(points_vector.at(i_v).x(), points_vector.at(i_v).y() +aux_evaluate));


            if (CGAL::do_intersect(segment_vector.at(i_s), v_prolong))//Si corta
            {
             //Se comprueba si lo hace por dentro del poligono
                CGAL::cpp11::result_of<Intersect_2(Segment_2, Line_2)>::type
                cut=CGAL::intersection(segment_vector.at(i_s), v_prolong);

                Point_2* p_cut = boost::get<Point_2>(&*cut);

                Point_2 evaluate_point;

                if (CGAL::to_double(p_cut->y())>points_vector.at(i_v).y())
                {
                    Point_2 aux_evp(points_vector.at(i_v).x(), points_vector.at(i_v).y() + evaluating_step);
                    evaluate_point=aux_evp;
                }

                if(CGAL::to_double(p_cut->y())<points_vector.at(i_v).y())
                {
                    Point_2 aux_evp(points_vector.at(i_v).x(), points_vector.at(i_v).y() - evaluating_step);
                    evaluate_point=aux_evp;
                }

                if(CGAL::bounded_side_2(pgn.vertices_begin(), pgn.vertices_end(), evaluate_point,pgn.traits_member())
                   == CGAL::ON_BOUNDED_SIDE)
                {
                    aux_candidate_vertices_vector.push_back(Point_2(p_cut->x(), p_cut->y()));
                    aux_candidate_segment_vector.push_back(segment_vector.at(i_s));
                    thereIsNewVertex_bool=true;
                }
            }

        }//for(int i_s=0; i_s<num_s; i_s++)  //Se recorren todos segmentos (excepto los adyacentes)

        if (thereIsNewVertex_bool)
        {
            if (aux_candidate_vertices_vector.size()==1) //Si solo hay uno...
            {
                new_points_vector.push_back(aux_candidate_vertices_vector.at(0)); //Se toma solo el primero


                vertexStruct v;

                v.point=aux_candidate_vertices_vector.at(0);
                v.prev_seg=aux_candidate_segment_vector.at(0);
                v.next_seg=aux_candidate_segment_vector.at(0);

                new_vertex_vector.push_back(v);
            }
            else //Si hay más de uno...
            {
                //Se debe buscar el vertice superior más cercano y/o el vertice inferior más cercano

                int idv_min_dist_ysup, idv_min_dist_yinf;
                double min_dist_ysup=MAX_DISTANCE; double min_dist_yinf=MAX_DISTANCE; //cambiar por otro valor

                //Se recorre el vector de candidatos en busca de ellos
                bool insert_supvert=false;
                bool insert_infvert=false;

                for (int i=0; i<aux_candidate_vertices_vector.size();i++)
                {
                   Point_2 p_candidato_aux= aux_candidate_vertices_vector.at(i);
                   double y_candidato=CGAL::to_double(p_candidato_aux.y());
                   double y_vertice=CGAL::to_double(points_vector.at(i_v).y());
                   double dif=std::abs(y_vertice - y_candidato);

                    //Diferencia positiva-->punto arriba.   Diferencia neg--> punto abajo
                    if(dif<min_dist_ysup && (y_candidato>y_vertice)) //Vertice superior     //ESTAAAA BIEN ESTO???. HAY QUE BUSCAR EL MIN NO EL MAX
                    {
                        min_dist_ysup=dif;
                        idv_min_dist_ysup=i;
                        insert_supvert=true;
                    }
                    else if(dif<min_dist_yinf && (y_candidato<y_vertice))//Vertice inferior
                    {
                        min_dist_yinf=dif;
                        idv_min_dist_yinf=i;
                        insert_infvert=true;
                    }
                }

                //Insercción, si es necesaria, del vertice superior
                if(insert_supvert)
                {
                    new_points_vector.push_back(aux_candidate_vertices_vector.at(idv_min_dist_ysup));
                    //segment_id_of_vertex_vector.push_back(aux_candidate_id_vector.at(89898));//CAMBIAAAAR


                    vertexStruct v;

                    v.point=aux_candidate_vertices_vector.at(idv_min_dist_ysup);
                    v.prev_seg=aux_candidate_segment_vector.at(idv_min_dist_ysup);
                    v.next_seg=aux_candidate_segment_vector.at(idv_min_dist_ysup);

                    new_vertex_vector.push_back(v);
                }
                //Insercción, si es necesaria, del vertice inferior
                if(insert_infvert)
                {
                    new_points_vector.push_back(aux_candidate_vertices_vector.at(idv_min_dist_yinf));
                    //segment_id_of_vertex_vector.push_back(aux_candidate_id_vector.at(454445));//CAMBIAAAAR

                    vertexStruct v;

                    v.point=aux_candidate_vertices_vector.at(idv_min_dist_yinf);
                    v.prev_seg=aux_candidate_segment_vector.at(idv_min_dist_yinf);
                    v.next_seg=aux_candidate_segment_vector.at(idv_min_dist_yinf);

                    new_vertex_vector.push_back(v);
                }
            }
        }//if (thereIsNewVertex_bool)
    }//for(int i_v=1; i_v<num_v; i_v++)//Se recorren todos los vertices

    //Llenado de new_polygon_vertices
    for(int i=0; i<points_vector.size(); i++)
    {
        geometry_msgs::Point32 p;
        p.x=CGAL::to_double(points_vector.at(i).x());
        p.y=CGAL::to_double(points_vector.at(i).y());
        new_polygon_vertices.push_back(p);
    }
//    for(int i=0; i<new_points_vector.size(); i++)
//    {
//        geometry_msgs::Point32 p;
//        p.x=CGAL::to_double(new_points_vector.at(i).x());
//        p.y=CGAL::to_double(new_points_vector.at(i).y());
//        new_polygon_vertices.push_back(p);
//    }
    for(int i=0; i<new_vertex_vector.size(); i++)
    {
        geometry_msgs::Point32 p;
        p.x=CGAL::to_double(new_vertex_vector.at(i).point.x());
        p.y=CGAL::to_double(new_vertex_vector.at(i).point.y());
        new_polygon_vertices.push_back(p);
    }


///---Vértices   ^     --------------------------------------------------------------------------------------
///              |

///---Polígonos  |     --------------------------------------------------------------------------------------
///              V

    //return;

    ///Se juntan los nuevos y los originales

    for(int i=0; i<points_vector.size(); i++)
    {
        vertexStruct v;
        v.point=points_vector.at(i);

//        int id_seg_next, id_seg_prev;

//        id_seg_next=i;

//        if(i!=0)
//            id_seg_prev=i-1;
//        else
//            id_seg_prev=segment_vector.size()-1;

        int prev_s, next_s;
            prev_s=i-1;
            next_s=i;
        if(prev_s<0)        prev_s=points_vector.size()-1;
        //if(next_s>(points_vector.size()-1))  next_s=0;
//std::cout<<std::endl<<prev_s<<"  "<<next_s<<"~"<<std::endl;
        v.prev_seg=segment_vector.at(prev_s);
        v.next_seg=segment_vector.at(next_s);

        new_vertex_vector.push_back(v);
    }

    /// Ordenar el vector de vértices en funcion de x
    int i_cout=0;
   // for(auto & elem: new_vertex_vector) //Impresion de los valores
    //   {std::cout<<i_cout<<"   "<<elem.point<< " in segment prev:"<<elem.prev_seg<<"--> next:"<<elem.next_seg<<std::endl;i_cout++;}
    //std::cout<<std::endl<<std::endl;

    std::vector<vertexStruct> sorted_polygon_vertices=new_vertex_vector;

    std::sort(sorted_polygon_vertices.begin(), sorted_polygon_vertices.end(), f_sortingVertexByX);

    i_cout=0;
   // for(auto & elem: sorted_polygon_vertices) //Impresion de los valores
   //    {std::cout<<i_cout<<"   "<<elem.point<< " in segment prev:"<<elem.prev_seg<<"--> next:"<<elem.next_seg<<std::endl;i_cout++;}
    //std::cout<<std::endl<<std::endl;


//std::cout<<"VERTEX_NOT_USED 0"<<std::endl;
//std::cout<<"VERTEX_USED_AS_END 1"<<std::endl;
//std::cout<<"VERTEX_USED_AS_START 2"<<std::endl;
//std::cout<<"VERTEX_RESERVED 3"<<std::endl;
//std::cout<<"VERTEX_EMPTY 10"<<std::endl<<std::endl;
   ///Dado el vector de vertices se crean los trapecios

   bool not_all_vertex_included=true;
   bool need_relook=false;//Booleano que se activa cuando se crea un poligono de tamaño 1
   bool relooking_bool=false;


   //Se comienza por el vertice con menor x

   int situation;//Entero que indicará la situacion en la que se ecuentra el algoritmo

   double min_x=CGAL::to_double(sorted_polygon_vertices.at(0).point.x()); //Siguiente valor de x a evaluar
   vertexStruct next_iniV=sorted_polygon_vertices.at(0);
   double next_x=min_x;

   int iteraciones=0;
   while(not_all_vertex_included)
   {
       iteraciones++;
       geometry_msgs::Polygon poly_i;//Poligono que se construirá en este ciclo

       std::vector<vertexStruct> aux_ini_v_vector;//Vector con los vertices candidatos a iniciar un nuevo trapecio

       if (need_relook) //Activado si alcanza el x max se busca un x entre los no usados
       {
           //Se busca un vertice no usado para iniciar de nuevo a construir trapecios

           //int posc=std::distance(sorted_polygon_vertices.begin(),
           //                       std::find(sorted_polygon_vertices.begin()->label,sorted_polygon_vertices.end()->label,VERTEX_NOT_USED));
           int relooked_vid;
           isLabelInVertexVector(sorted_polygon_vertices, VERTEX_NOT_USED, relooked_vid);
            //next_x=sorted_polygon_vertices.at(posc).posc.x;
            next_iniV=sorted_polygon_vertices.at(relooked_vid);
            next_x=CGAL::to_double(next_iniV.point.x());

           need_relook=false;
           relooking_bool=true;
       }
       else
       {
           relooking_bool=false;
       }

       for (auto & elem : sorted_polygon_vertices) //Se buscan los vertices en esa coordenada...
       {
           if (elem.point.x() == CGAL::to_double(next_iniV.point.x()) && elem.label!=VERTEX_USED_AS_START)//...que no hayan servido como comienzo de otro poligono
           {
               aux_ini_v_vector.push_back(elem);
           }
       }

       //std::sort(aux_ini_v_vector.begin(), aux_ini_v_vector.end(), sortingVertexByYFunction); //Los vertices candidatos se ordenan segun valor en Y


       //Se realizarán distintas acciones en función del número de vertices de inicio
       int n_ini_v=aux_ini_v_vector.size();
       if (n_ini_v>2) situation=SITUATION_3ORMOREVERTICES;
       else situation=n_ini_v;



       switch (situation)
       {
           case SITUATION_1VERTEX://~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~1VERTEX~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
           {


           //Se añade el vertice inicial
                 vertexStruct initialV=aux_ini_v_vector.at(0);
           //Estructuras para vertice final
                 vertexStruct finalV_innext, finalV_inprev;
                 finalV_innext.label=VERTEX_EMPTY;
                 finalV_inprev.label=VERTEX_EMPTY;

                 geometry_msgs::Point32 p;
                                      p.x=CGAL::to_double(initialV.point.x());
                                      p.y=CGAL::to_double(initialV.point.y());
                  poly_i.points.push_back(p);

                  for(auto & elem : sorted_polygon_vertices)//Se busca el que corresponde para marcarlo
                  {
                    if( elem.point==initialV.point )
                        elem.label=VERTEX_USED_AS_START;
                  }


           //Se buscan los dos vertices finales

                double min_dist_s1=MAX_DISTANCE_IN_SEGMENT; double min_dist_s2=MAX_DISTANCE_IN_SEGMENT; //cambiar por otro valor

                for (auto & elem : sorted_polygon_vertices) //Busqueda de vertices en esa coordenada
                    {
                        if(elem.point==initialV.point) continue; //Si el vertice es el mismo que el inicial se salta este bucle

                        if (!relooking_bool && elem.label==VERTEX_USED_AS_START) continue; //Si el vertice está marcado como START se salta este bucle


                        //Se comprueba si el vertice se encuentra en el segmento anterior o posterior al del inicio
                        bool is_in_prevseg= ( initialV.prev_seg == elem.prev_seg || initialV.prev_seg == elem.next_seg )
                                            && ( initialV.point.x()<elem.point.x());
                        bool is_in_nextseg= ( initialV.next_seg == elem.prev_seg || initialV.next_seg == elem.next_seg )
                                            && ( initialV.point.x()<elem.point.x());

                        if (is_in_prevseg)//Escoger el más cercano que pertenezca a un segmento
                        {
                            double manhattan_dist=f_manhattan_dist(initialV.point,elem.point);

                            if(manhattan_dist<min_dist_s1)
                            {
                                min_dist_s1=manhattan_dist;
                                finalV_inprev=elem;
                            }
                        }

                        if (is_in_nextseg)//Escoger el más cercano que pertenezca al otro
                        {
                            double manhattan_dist=f_manhattan_dist(initialV.point,elem.point);

                            if(manhattan_dist<min_dist_s2)
                            {
                                min_dist_s2=manhattan_dist;
                                finalV_innext=elem;
                            }
                        }

                     }

               //Se incluye el vertice mas cercano en el segmento 1
               geometry_msgs::Point32 p_s1;
                if (finalV_inprev.label!=VERTEX_EMPTY)
               {

                                           p_s1.x=CGAL::to_double(finalV_inprev.point.x());
                                           p_s1.y=CGAL::to_double(finalV_inprev.point.y());
                   poly_i.points.push_back(p_s1);
                   //Se marcan los vertices usados como final
                   for (auto & elem : sorted_polygon_vertices)
                   {  if(elem.point==finalV_inprev.point) elem.label=VERTEX_USED_AS_END;  }

                }
               //Se incluye el vertice mas cercano en el segmento 2
               geometry_msgs::Point32 p_s2;
                if (finalV_innext.label!=VERTEX_EMPTY)
               {

                                          p_s2.x=CGAL::to_double(finalV_innext.point.x());
                                          p_s2.y=CGAL::to_double(finalV_innext.point.y());
                  poly_i.points.push_back(p_s2);
                  //Se marcan los vertices usados como final
                  for (auto & elem : sorted_polygon_vertices)
                  {  if(elem.point==finalV_innext.point) elem.label=VERTEX_USED_AS_END;  }

               }

              //Si no se han encontrado ninguna continuación
              if(finalV_inprev.label==VERTEX_EMPTY && finalV_innext.label==VERTEX_EMPTY)
              {
                       //Si hay alguno reservado se va a esa posicion a continuar con 2 vertices
                          int id_reserved;
                          if(isLabelInVertexVector(sorted_polygon_vertices, VERTEX_RESERVED, id_reserved))
                          {

                            Point_2 reserved_p=sorted_polygon_vertices.at(id_reserved).point;
                            sorted_polygon_vertices.at(id_reserved).label=VERTEX_NOT_USED;

                            next_x=to_double(sorted_polygon_vertices.at( id_reserved ).point.x()); //Siguiente X el del reservado encontrado
                            next_iniV=sorted_polygon_vertices.at(id_reserved);


                            //En esa X se busca el vertice superior en X y se marca como sin usar
                            int id_of_reservedcouple=0;
                            int aux_id_of_reservedcouple=0;

                            double min_y_dist=MAX_DISTANCE;

                            for (auto & elem : sorted_polygon_vertices) //Busqueda de vertices en esa coordenada
                            {
                               if(elem.point.x() == reserved_p.x() &&
                                  elem.point.y() >  reserved_p.y()) //En esa x y el y superior más cercano
                               {
                                if(std::abs(CGAL::to_double(elem.point.y()-reserved_p.y()))<min_y_dist)
                                {
                                    min_y_dist=std::abs(CGAL::to_double(elem.point.y()-reserved_p.y()));
                                    id_of_reservedcouple=aux_id_of_reservedcouple;
                                }
                               }
                                aux_id_of_reservedcouple++;
                            }

                            sorted_polygon_vertices.at(id_of_reservedcouple).label=VERTEX_NOT_USED;
                            //Se marca como sin usar el superior al reservado




                            break;

                          }
                       //Si no hay ninguno reservado se comprueba si queda alguno sin usar
                          else if(isLabelInVertexVector(sorted_polygon_vertices, VERTEX_NOT_USED))
                          {
                              need_relook=true;//si se encuentran se activa el booleano para revisitar posiciones
                          }


              }//if(finalV_inprev.label==VERTEX_EMPTY && finalV_innext.label==VERTEX_EMPTY)



              //Se guarda la siguiente coordenada x
              if(finalV_inprev.label!=VERTEX_EMPTY)
              {
              next_iniV=finalV_inprev;
              next_x=p_s1.x;
              }
              else if(finalV_innext.label!=VERTEX_EMPTY)
              {
                  next_iniV=finalV_innext;
                  next_x=p_s2.x;
              }
              //Y se guarda el poligono en el vector de poligonos
              if(poly_i.points.size()<2)
              {need_relook=true; break;}

              trapezoids_result.push_back(poly_i);


               break;
           }
           case SITUATION_3ORMOREVERTICES://~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~3or+VERTEX~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
           {
            //Implementar
           //Marcar como reservado en el aux ini y en sorted polygon

           //Si se parte de 3 o + vertices se cogen los dos superiores y se pasa a SITUATION_2VERTICES
           //El resto se marcan como VERTEX_RESERVED


           double y1=MIN_Y;
           double y2=MIN_Y;

           for (auto & elem: aux_ini_v_vector)
           {
               if(elem.point.y()>y1)
               {
                   y1=to_double(elem.point.y());
               }
           }
           for (auto & elem: aux_ini_v_vector)
           {
               if(elem.point.y()>y2 && to_double(elem.point.y())<y1)
               {
                   y2=to_double(elem.point.y());
               }
           }

           for(auto & elem: aux_ini_v_vector)
           {
               if (elem.point.y()<y2)//Si no son los dos primeros
               {
                   elem.label=VERTEX_RESERVED;

                   for(auto & elem2: sorted_polygon_vertices)
                   {
                       if(elem2.point==elem.point)
                           elem2.label=VERTEX_RESERVED;
                   }
          }
           situation=SITUATION_2VERTICES;}//Se continua directamente en 2 vertices

           }
           case SITUATION_2VERTICES://~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~3VERTICES~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
           {

              vertexStruct ini_sup_v, ini_inf_v;

              //Se aniaden los 2 iniciales
              bool found_ini=false;//Booleano que indica si se ha econtrado el primero
              for(auto & elem : aux_ini_v_vector)
              {
                  if(elem.label!=VERTEX_RESERVED && found_ini)
                  {
                      ini_inf_v=elem;

                      geometry_msgs::Point32 p;
                                             p.x=to_double(elem.point.x());
                                             p.y=to_double(elem.point.y());
                      poly_i.points.push_back(p);//Al solo haber dos se aniaden ya al poligono

                      break;
                  }

                  if(elem.label!=VERTEX_RESERVED && !found_ini)
                  {
                      ini_sup_v=elem;
                      found_ini=true;

                      geometry_msgs::Point32 p;
                                             p.x=to_double(elem.point.x());
                                             p.y=to_double(elem.point.y());
                      poly_i.points.push_back(p);//Al solo haber dos se aniaden ya al poligono
                  }
              }

           //Se buscan los que corresponden para marcarlo
              for(auto & elem : sorted_polygon_vertices)
              {
              if(elem.point==ini_sup_v.point)
                elem.label=VERTEX_USED_AS_START;
              if(elem.point==ini_inf_v.point)
                elem.label=VERTEX_USED_AS_START;
              }

              //Comprobacion de que el inferior es el inferior y el superior el superior
              if(ini_sup_v.point.y()<ini_inf_v.point.y())
              {
                  vertexStruct aux_v;

                  aux_v=ini_inf_v;

                  ini_inf_v=ini_sup_v;
                  ini_sup_v=aux_v;
              }

              vertexStruct fin_sup_v, fin_inf_v;
              bool fin_sup_exits=false;
              bool fin_inf_exits=false;
              double min_dist_sup=MAX_DISTANCE_IN_SEGMENT; double min_dist_inf=MAX_DISTANCE_IN_SEGMENT; //cambiar por otro valor
              for (auto & elem : sorted_polygon_vertices) //Busqueda de vertices en esa coordenada
                  {
                      if(elem.point.x()<ini_sup_v.point.x()) continue;

                      //Comparte segmento con sup
                      bool same_seg_as_sup= elem.prev_seg == ini_sup_v.next_seg;

                      //Comparte segmento con inf
                      bool same_seg_as_inf= elem.next_seg == ini_inf_v.prev_seg;

                      if (same_seg_as_sup && (ini_sup_v.point.x()<elem.point.x()))//Escoger el más cercano que pertenezca a un segmento
                      {
                          double manhattan_dist=std::abs(f_manhattan_dist(ini_sup_v.point,
                                                                 elem.point));

                          if(manhattan_dist<min_dist_sup && manhattan_dist!=0 && elem.label!= VERTEX_USED_AS_START)
                            //dist min                      no el mimso                                  no usado
                          {
                              min_dist_sup=manhattan_dist;
                              fin_sup_v=elem;
                              fin_sup_exits=true;
                          }
                      }

                      if (same_seg_as_inf && (ini_inf_v.point.x()<elem.point.x()))//Escoger el más cercano que pertenezca al otro
                      {

                          double manhattan_dist=std::abs(f_manhattan_dist(ini_inf_v.point,
                                                                 elem.point));//Funcion que la calcule?

                          if(manhattan_dist<min_dist_inf && manhattan_dist!=0 && elem.label!= VERTEX_USED_AS_START)
                            //dist min                      no el mimso                                  no usado
                          {
                              min_dist_inf=manhattan_dist;
                              fin_inf_v=elem;
                              fin_inf_exits=true;
                          }
                      }

                   }



           //Se incluye el vertice mas cercano en el segmento 1
              geometry_msgs::Point32 p_sup;
              if (fin_sup_exits)
              {
                 p_sup.x=CGAL::to_double(fin_sup_v.point.x());
                 p_sup.y=CGAL::to_double(fin_sup_v.point.y());
                 poly_i.points.push_back(p_sup);

                 //Se marcan los vertices usados como final
                 for(auto & elem: sorted_polygon_vertices)
                 {
                     if(elem.point==fin_sup_v.point)elem.label=VERTEX_USED_AS_END;
                 }
              }

           //Se incluye el vertice mas cercano en el segmento 2
             geometry_msgs::Point32 p_inf;
             if (fin_inf_exits)
             {

                 p_inf.x=CGAL::to_double(fin_inf_v.point.x());
                 p_inf.y=CGAL::to_double(fin_inf_v.point.y());
                 poly_i.points.push_back(p_inf);

                 //Se marcan los vertices usados como final
                 for(auto & elem: sorted_polygon_vertices)
                 {
                     if(elem.point==fin_inf_v.point)elem.label=VERTEX_USED_AS_END;
                 }
              }
             else
             {
                 //Si no hay ninguno en el segundo segmento quiere decir que ese punto intermedio no conecta con nada
                 for(auto & elem: sorted_polygon_vertices)
                 {
                     if(elem.point==fin_sup_v.point)elem.label=VERTEX_NOT_USED;
                     if(elem.point==ini_sup_v.point)elem.label=VERTEX_NOT_USED;
                     if(elem.point==fin_inf_v.point)elem.label=VERTEX_NOT_USED;

                }//Se desmarca el reciente marcado como fin
                 for(auto & elem: sorted_polygon_vertices)
                 {
                     for(auto & elem_ini : aux_ini_v_vector)
                     {
                         if(elem_ini.point==elem.point && elem.label==VERTEX_RESERVED) elem.label=VERTEX_NOT_USED;
                     }
                 }
                 //Y se desmarca también el vertice valido usado como inicio ///DUDAAAAAAAS
//                         for(auto & elem : sorted_polygon_vertices)//Se busca el que corresponde para marcarlo
//                         {
//                         if (elem.point==ini_sup_v.point)
//                                 elem.label=VERTEX_USED_AS_END; //Marcar como usados en el vector de check
//                         }
                 break;
             }

            //Se guarda la siguiente coordenada x
            next_x=std::max(p_sup.x,p_inf.x);
            next_iniV=fin_sup_v;

            //(Funcion que elimine puntos repetidos del poligono?????)
            //Y se guarda el poligono en el vector de poligonos

            poly_i=clockwisePolygon(poly_i);
            trapezoids_result.push_back(poly_i);







               break;
           }
       }
       not_all_vertex_included=isLabelInVertexVector(sorted_polygon_vertices, VERTEX_NOT_USED); //Comprobacion de todas las labels = VERTEX_NOT_USED
        if (iteraciones<50)
        {
            //for(auto & elem: sorted_polygon_vertices) std::cout<<elem.label<<"-";
            //std::cout<<std::endl;
        }
       if (iteraciones>1000)
        {
            std::cout<<"      Muchas iteraciones     "<<std::endl;
            return;
        }
   }



}

void TrapDecomposition::getYDecomposition(std::vector<geometry_msgs::Polygon> &trapezoids_result, std::vector<geometry_msgs::Point32> &new_polygon_vertices)
{
//    //Se guarda una copia del original
//    geometry_msgs::Polygon aux_poly;
//    aux_poly= original_shape;

//    //Se rota
//    changeXYValues(original_shape);
//    original_shape=orderPolygon(original_shape);


    changeXYmembers();


    //Descomposicion en X
    getXDecomposition(trapezoids_result, new_polygon_vertices);

    //Se deshace la rotacion en los resultados
    for(int i=0; i<trapezoids_result.size(); i++)
    {
        changeXYValues(trapezoids_result.at(i));
    }

    changeXYmembers();
    //original_shape=aux_poly;

}
