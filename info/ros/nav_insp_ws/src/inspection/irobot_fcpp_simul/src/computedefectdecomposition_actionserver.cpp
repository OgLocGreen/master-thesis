#include "ros/ros.h"
#include <actionlib/server/simple_action_server.h>
#include <irobot_fcpp_simul/ComputeDefectsDecompAction.h>
#include <irobot_fcpp_simul/FCPP_in.h>
#include "irobot_fcpp_simul/IROBOT_ir_data.h"


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



#include "../../irobot_fcpp_pckg/src/trapdecomposition.h"
#include "../../irobot_fcpp_pckg/src/trappathplanning.h"
#include "../../irobot_fcpp_pckg/src/cutter_functions.h"
//#include "working_zones.h"

#include "../../irobot_fcpp_pckg/src/coords_info.h"







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

class ComputeDefectDecompositionAction
{
protected:

  ros::NodeHandle nh_;
  actionlib::SimpleActionServer<irobot_fcpp_simul::ComputeDefectsDecompAction> as_; // NodeHandle instance must be created before this line. Otherwise strange error occurs.
  std::string action_name_;

  // create messages that are used to published feedback/result
  //action_server_package::BaseRotationFeedback feedback_;
  irobot_fcpp_simul::ComputeDefectsDecompResult result_;

public:

  //Probar con el executeCB_old? Creo que solo descompone un polígono. Habría que mirar que id le paso desde fuera
  ComputeDefectDecompositionAction(std::string name) :
    as_(nh_, name, boost::bind(&ComputeDefectDecompositionAction::executeCB, this, _1), false),
    action_name_(name)
  {
    as_.start();
  }

  ~ComputeDefectDecompositionAction(void)
  {
  }

  void executeCB(const irobot_fcpp_simul::ComputeDefectsDecompGoalConstPtr &goal)
  {
    // helper variables
    ros::Rate r(1);
    bool success = true;

    irobot_fcpp_simul::defecto d_msg;

    // start executing the action

      // check that preempt has not been requested by the client
      if (as_.isPreemptRequested() || !ros::ok())
      {
        //robot.stop();
        ROS_INFO("%s: Preempted", action_name_.c_str());
        // set the action state to preempted
        as_.setPreempted();
        success = false;

      }

      else
      {

        /// 1.- Se obtiene el poligono del defecto y el vector con las zonas de trabajo
        int id_defecto=goal->chapa_id;




        geometry_msgs::Polygon poly_defect = goal->poly_defect;

        double xmin_work, xmax_work, ymin_work, ymax_work;
        xmin_work=.0;//srv.response.xmin_chapa;
        xmax_work=goal->xmax;//srv.response.xmax_chapa;
        ymin_work=.0; //srv.response.ymin_chapa;
        ymax_work=goal->ymax;


          std::vector<geometry_msgs::Polygon> working_zones_vec;
                                              working_zones_vec.push_back(goal->zone0);
                                              working_zones_vec.push_back(goal->zone90);
                                              working_zones_vec.push_back(goal->zone180);
                                              working_zones_vec.push_back(goal->zone270);



        ROS_INFO("Informacion del servicio de defectos obtenida");
        /// 2.- Se dividen el defecto por zonas

          defecto d;
          d.ros_poly=poly_defect;

          std::vector<geometry_msgs::Polygon> vector_poly_result;
          std::vector<int> vector_id_cutter;

          vector_poly_result= intersectPolygonWithOtherPolygons(poly_defect, working_zones_vec, vector_id_cutter);
          ROS_INFO("numero de poligonos debido a las zonas de trabajo: %d", vector_poly_result.size());
          ROS_INFO("vector_id_cutter: %d", vector_id_cutter.size());


          int i=0;
          for(auto & elem: vector_poly_result)
          {
              defecto_zona dz;
              dz.ros_poly=elem;
              dz.zona=vector_id_cutter.at(i);
              d.defecto_divpor_zonas_vec.push_back(dz);
              i++;
          }
          ROS_INFO("Division del defecto por zonas realizada");

        /// 3.- A cada zona se le asocia el sentido de avance
          for (auto & elem: d.defecto_divpor_zonas_vec)
          {
              switch (elem.zona)
              {
//              case 0:
//                  elem.direccion_rep=YPOS;
//                  break;
//              case 1:
//                  elem.direccion_rep=YNEG;
//                  break;
//              case 2: case 3:
//                  elem.direccion_rep=XNEG;
//                  break;
//              case 4: case 5:
//                  elem.direccion_rep=XPOS;
//                  break;
//              case 6: case 7: case 8: case 9:
//                  elem.direccion_rep=OUT;
              case 0:
                  elem.direccion_rep=XPOS;
                  break;
              case 1:
                  elem.direccion_rep=YPOS;
                  break;
              case 2:
                  elem.direccion_rep=XNEG;
                  break;
              case 3:
                  elem.direccion_rep=YNEG;
                  break;
              }
         }

        /// 4.- Se descompone trapezoidalmente el defecto

          for (auto & elemz: d.defecto_divpor_zonas_vec)
          {
              TrapDecomposition decomposer(elemz.ros_poly);
              std::vector<geometry_msgs::Point32> new_polygon_vertices;
              std::vector<geometry_msgs::Polygon> trapezoids_result;

              switch (elemz.direccion_rep)//Distinta descomposicion en funcion de la direccion de reparacion
              {
              case XNEG: case XPOS:
                  ROS_INFO("Ydecomposition");
                  decomposer.getYDecomposition(trapezoids_result, new_polygon_vertices);
                  break;

              case YPOS: case YNEG:
                  ROS_INFO("Xdecomposition");
                  decomposer.getXDecomposition(trapezoids_result, new_polygon_vertices);
                  break;

              case OUT:
                  break;
              }

              ROS_INFO("Descomposición trapezoid_results: %d", trapezoids_result.size());
              ROS_INFO("Descomposición new_polygon_vertices: %d", new_polygon_vertices.size());

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
          ROS_INFO("Descomposicion trapezoidal realizada");


        //Paso de la info a mensajes de ROS
        d_msg.ros_poly=d.ros_poly;
        //d_msg.defecto_divpor_zonas.reserve(d.defecto_divpor_zonas_vec.size());
        for(int i=0; i<(d.defecto_divpor_zonas_vec.size()); i++)
        {
            irobot_fcpp_simul::defecto_zona dz;
            dz.ros_poly=d.defecto_divpor_zonas_vec.at(i).ros_poly;
            dz.zona=d.defecto_divpor_zonas_vec.at(i).zona;
            dz.direccion_rep=d.defecto_divpor_zonas_vec.at(i).direccion_rep;

            d_msg.defecto_divpor_zonas.push_back(dz);

            for(int i2=0; i2<(d.defecto_divpor_zonas_vec.at(i).trapdecomp_vec.size()); i2++)
            {
                irobot_fcpp_simul::defecto_simple ds;
                ds.ros_poly=d.defecto_divpor_zonas_vec.at(i).trapdecomp_vec.at(i2).ros_poly;
                ds.direccion_rep=d.defecto_divpor_zonas_vec.at(i).trapdecomp_vec.at(i2).direccion_rep;

                d_msg.defecto_divpor_zonas.at(i).trap_vec.push_back(ds);
            }
        }
      }

      // this sleep is not necessary, the sequence is computed at 1 Hz for demonstration purposes
        r.sleep();


        if(success)
        {
            result_.defecto=d_msg;
            ROS_INFO("%s: Succeeded", action_name_.c_str());
            // set the action state to succeeded
            as_.setSucceeded(result_);
        }

  }

  void executeCB_old(const irobot_fcpp_simul::ComputeDefectsDecompGoalConstPtr &goal)
  {
    // helper variables
    ros::Rate r(1);
    bool success = true;

    irobot_fcpp_simul::defecto d_msg;

    // start executing the action

      // check that preempt has not been requested by the client
      if (as_.isPreemptRequested() || !ros::ok())
      {
        //robot.stop();
        ROS_INFO("%s: Preempted", action_name_.c_str());
        // set the action state to preempted
        as_.setPreempted();
        success = false;

      }

      else
      {

        /// 1.- Se obtiene el poligono del defecto y el vector con las zonas de trabajo
        int id_defecto=goal->chapa_id;


        //ros::ServiceClient client = nh_.serviceClient<irobot_fcpp_simul::FCPP_in>("fcpp_data_service");
        ros::ServiceClient client = nh_.serviceClient<irobot_fcpp_simul::IROBOT_ir_data>("irobot_ir_data");

        //irobot_fcpp_simul::FCPP_in srv;
        irobot_fcpp_simul::IROBOT_ir_data srv;

        srv.request.id_poly=id_defecto;
        srv.request.get_poly_i=true;
        srv.request.get_working_zonesh=true;

        if (!client.call(srv))
        {   ROS_ERROR("Failed to call service!!!!!");   return;   }

        geometry_msgs::Polygon poly_defect = srv.response.poly_i;

        double xmin_work, xmax_work, ymin_work, ymax_work;
        xmin_work=0.0;//srv.response.xmin_chapa;
        xmax_work=srv.response.long_areax;//srv.response.xmax_chapa;
        ymin_work=0.0;//srv.response.ymin_chapa;
        ymax_work=srv.response.long_areay;


          std::vector<geometry_msgs::Polygon> working_zones_vec;
                                              working_zones_vec.push_back(srv.response.zoneh0);
                                              working_zones_vec.push_back(srv.response.zoneh90);
                                              working_zones_vec.push_back(srv.response.zoneh180);
                                              working_zones_vec.push_back(srv.response.zoneh270);

        ROS_INFO("Informacion del servicio de defectos obtenida");
        /// 2.- Se dividen el defecto por zonas

          defecto d;
          d.ros_poly=poly_defect;

          std::vector<geometry_msgs::Polygon> vector_poly_result;
          std::vector<int> vector_id_cutter;

          vector_poly_result= intersectPolygonWithOtherPolygons(poly_defect, working_zones_vec, vector_id_cutter);

          int i=0;
          for(auto & elem: vector_poly_result)
          {
              defecto_zona dz;
              dz.ros_poly=elem;
              dz.zona=vector_id_cutter.at(i);
              d.defecto_divpor_zonas_vec.push_back(dz);
              i++;
          }
          ROS_INFO("Division del defecto por zonas realizada");

        /// 3.- A cada zona se le asocia el sentido de avance
          for (auto & elem: d.defecto_divpor_zonas_vec)
          {
              switch (elem.zona)
              {
              case 0:
                  elem.direccion_rep=YPOS;
                  break;
              case 1:
                  elem.direccion_rep=YNEG;
                  break;
              case 2: case 3:
                  elem.direccion_rep=XNEG;
                  break;
              case 4: case 5:
                  elem.direccion_rep=XPOS;
                  break;
              case 6: case 7: case 8: case 9:
                  elem.direccion_rep=OUT;
              }
         }

        /// 4.- Se descompone trapezoidalmente el defecto

          for (auto & elemz: d.defecto_divpor_zonas_vec)
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
                  decomposer.getXDecomposition(trapezoids_result, new_polygon_vertices); //Aquí tiene problema de muchas iteraciones??
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
          ROS_INFO("Descomposicion trapezoidal realizada");


        //Paso de la info a mensajes de ROS
        d_msg.ros_poly=d.ros_poly;
        //d_msg.defecto_divpor_zonas.reserve(d.defecto_divpor_zonas_vec.size());
        for(int i=0; i<(d.defecto_divpor_zonas_vec.size()); i++)
        {
            irobot_fcpp_simul::defecto_zona dz;
            dz.ros_poly=d.defecto_divpor_zonas_vec.at(i).ros_poly;
            dz.zona=d.defecto_divpor_zonas_vec.at(i).zona;
            dz.direccion_rep=d.defecto_divpor_zonas_vec.at(i).direccion_rep;

            d_msg.defecto_divpor_zonas.push_back(dz);

            for(int i2=0; i2<(d.defecto_divpor_zonas_vec.at(i).trapdecomp_vec.size()); i2++)
            {
                irobot_fcpp_simul::defecto_simple ds;
                ds.ros_poly=d.defecto_divpor_zonas_vec.at(i).trapdecomp_vec.at(i2).ros_poly;
                ds.direccion_rep=d.defecto_divpor_zonas_vec.at(i).trapdecomp_vec.at(i2).direccion_rep;

                d_msg.defecto_divpor_zonas.at(i).trap_vec.push_back(ds);
            }
        }
      }

      // this sleep is not necessary, the sequence is computed at 1 Hz for demonstration purposes
        r.sleep();


        if(success)
        {
            result_.defecto=d_msg;
            ROS_INFO("%s: Succeeded", action_name_.c_str());
            // set the action state to succeeded
            as_.setSucceeded(result_);
        }

  }


};







int main(int argc, char **argv)
{
    ros::init(argc, argv, "computedefectdecomposition");

    ComputeDefectDecompositionAction trap_decomp("ComputeDefects");
    ROS_INFO("Servidor de la accion de descomposion ---> LISTO");
    ros::spin();

    return 0;
}
