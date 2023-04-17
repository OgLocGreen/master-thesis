#include "ros/ros.h"
#include "action_server_package/ChapaStorage.h"
#include "geometry_msgs/Point.h"
#include "geometry_msgs/Pose2D.h"

bool chapa_params(action_server_package::ChapaStorage::Request  &req,
         action_server_package::ChapaStorage::Response &res)
{
  
  res.number_of_chapas=1;

  float pos_ini_robot_x=0;//6.0;
  float pos_ini_robot_y=0;//4.0;

  /*
  float xc=10.0;
  float yc=19.0;

  float deg15=0.261799;
*/

  float xc=4;
  float yc=6;

  float deg15=0;

  switch(req.id_chapa)
  {
      ///Mi mundo##############################################################################
  /*    res.number_of_chapas=2;
      case 0:
              //res.coordA=geometry_msgs::Point(-1.0, 0.0,   0.0);
              res.coordA.x=-1; res.coordA.y= 0;
              res.coordB.x=-3; res.coordB.y= 2;
              res.coordC.x= 0; res.coordC.y= 5;
              res.coordD.x= 2; res.coordD.y= 3;

              //SUSTITUIR POR UNA FUNCIÓN QUE CALCULE DADAS LAS COORDENADAS
              res.long_chapa=4.242640687;//sqrt(18)
              res.width_chapa=2.828427125;//sqrt(8)

              break;
      case 1:
              
              res.coordA.x=-3; res.coordA.y=-11;              
              res.coordB.x=-5; res.coordB.y=-11;
              res.coordC.x=-5; res.coordC.y=-6;
              res.coordD.x=-3; res.coordD.y=-6;


              //res.coordA=Point(-5,-11,   0);
              //res.coordB=Point(-5,-6,   0);
              //res.coordC=Point(-3,-6,   0);
              //res.coordD=Point(-3,-11,   0);


              //SUSTITUIR POR UNA FUNCIÓN QUE CALCULE DADAS LAS COORDENADAS
              res.long_chapa=5;
              res.width_chapa=2;

              break;
              */
      ///Fabrica##############################################################################
// res.number_of_chapas=2;
//       case 0:
//               //res.coordA=geometry_msgs::Point(-1.0, 0.0,   0.0);
// /*              res.coordA.x=9.3541-6; res.coordA.y= 6.00544-4;
//               res.coordB.x=6.359631-6; res.coordB.y= 6.187534-4;
//               res.coordC.x=6.845215-6; res.coordC.y=14.172783-4;
//               res.coordD.x=9.839684-6; res.coordD.y=13.990689-4;*/

//               res.coordA.x=9.3541-pos_ini_robot_x; res.coordA.y= 6.00544-pos_ini_robot_y;
//               res.coordB.x=6.359631-pos_ini_robot_x; res.coordB.y= 6.187534-pos_ini_robot_y;
//               res.coordC.x=6.845215-pos_ini_robot_x; res.coordC.y=14.172783-pos_ini_robot_y;
//               res.coordD.x=9.839684-pos_ini_robot_x; res.coordD.y=13.990689-pos_ini_robot_y;

//               //SUSTITUIR POR UNA FUNCIÓN QUE CALCULE DADAS LAS COORDENADAS
//               res.long_chapa=8;//sqrt(18)
//               res.width_chapa=3;//sqrt(8)

//               break;
//       case 1:
              
//               res.coordA.x=13-pos_ini_robot_x; res.coordA.y=16.5-pos_ini_robot_y;              
//               res.coordB.x=10.475587-pos_ini_robot_x; res.coordB.y=18.120907-pos_ini_robot_y;
//               res.coordC.x=14.798005-pos_ini_robot_x; res.coordC.y=24.852675-pos_ini_robot_y;
//               res.coordD.x=17.322418-pos_ini_robot_x; res.coordD.y=23.231768-pos_ini_robot_y;


              /*res.coordA=Point(-5,-11,   0);
              res.coordB=Point(-5,-6,   0);
              res.coordC=Point(-3,-6,   0);
              res.coordD=Point(-3,-11,   0);*/
              

              // //SUSTITUIR POR UNA FUNCIÓN QUE CALCULE DADAS LAS COORDENADAS
              // res.long_chapa=8;
              // res.width_chapa=3;

              // break;

            ///Fabrica  DAORJE##############################################################################
 res.number_of_chapas=2;
                 case 0:
               //res.coordA=geometry_msgs::Point(-1.0, 0.0,   0.0);
     /*              res.coordA.x=9.3541-6; res.coordA.y= 6.00544-4;
                   res.coordB.x=6.359631-6; res.coordB.y= 6.187534-4;
                   res.coordC.x=6.845215-6; res.coordC.y=14.172783-4;
                   res.coordD.x=9.839684-6; res.coordD.y=13.990689-4;*/

                    res.coordA.x=xc/*-pos_ini_robot_x*/ + 1.5*cos(deg15) + 4*sin(deg15);
                    res.coordA.y=yc/*-pos_ini_robot_y*/ + 1.5*sin(deg15) - 4*cos(deg15);

                    res.coordB.x=xc/*-pos_ini_robot_x*/ - 1.5*cos(deg15) + 4*sin(deg15);
                    res.coordB.y=yc/*-pos_ini_robot_y*/ - 1.5*sin(deg15) - 4*cos(deg15);

                    res.coordC.x=xc/*-pos_ini_robot_x*/ - 1.5*cos(deg15) - 4*sin(deg15);
                    res.coordC.y=yc/*-pos_ini_robot_y*/ - 1.5*sin(deg15) + 4*cos(deg15);

                    res.coordD.x=xc/*-pos_ini_robot_x*/ + 1.5*cos(deg15) - 4*sin(deg15);
                    res.coordD.y=yc/*-pos_ini_robot_y*/ + 1.5*sin(deg15) + 4*cos(deg15);

     //               //SUSTITUIR POR UNA FUNCIÓN QUE CALCULE DADAS LAS COORDENADAS
                    res.long_chapa=3.76;//sqrt(18)
                    res.width_chapa=2.51;//sqrt(8)



                break;
       case 1:
              
               res.coordA.x=13-pos_ini_robot_x; res.coordA.y=16.5-pos_ini_robot_y;
               res.coordB.x=10.475587-pos_ini_robot_x; res.coordB.y=18.120907-pos_ini_robot_y;
               res.coordC.x=14.798005-pos_ini_robot_x; res.coordC.y=24.852675-pos_ini_robot_y;
               res.coordD.x=17.322418-pos_ini_robot_x; res.coordD.y=23.231768-pos_ini_robot_y;


              /*res.coordA=Point(-5,-11,   0);
              res.coordB=Point(-5,-6,   0);
              res.coordC=Point(-3,-6,   0);
              res.coordD=Point(-3,-11,   0);*/
              

              //SUSTITUIR POR UNA FUNCIÓN QUE CALCULE DADAS LAS COORDENADAS
              // res.long_chapa=8;
              // res.width_chapa=3;

              // break;



        ///Simulacion  simple del lab##############################################################################
        
        // case 0:
        //   pos_ini_robot_x=1.5;
        //   pos_ini_robot_y=0.0;
        //   //res.coordA=geometry_msgs::Point(-1.0, 0.0,   0.0);
        //   res.coordA.x=4-pos_ini_robot_x; res.coordA.y=2-pos_ini_robot_y;
        //   res.coordB.x=1-pos_ini_robot_x; res.coordB.y=2-pos_ini_robot_y;
        //   res.coordC.x=1-pos_ini_robot_x; res.coordC.y=6.5-pos_ini_robot_y;
        //   res.coordD.x=4-pos_ini_robot_x; res.coordD.y=6.5-pos_ini_robot_y;

        //   //SUSTITUIR POR UNA FUNCIÓN QUE CALCULE DADAS LAS COORDENADAS
        //   res.long_chapa=4.5;//sqrt(18)
        //   res.width_chapa=3;//sqrt(8)

        //   break;
        
        ///ARUCOS##############################################################################
        
        // case 0:
        //   //res.coordA=geometry_msgs::Point(-1.0, 0.0,   0.0);
        //   res.coordA.x=12-pos_ini_robot_x; res.coordA.y=7-pos_ini_robot_y;
        //   res.coordB.x=7-pos_ini_robot_x; res.coordB.y=7-pos_ini_robot_y;
        //   res.coordC.x=7-pos_ini_robot_x; res.coordC.y=22-pos_ini_robot_y;
        //   res.coordD.x=12-pos_ini_robot_x; res.coordD.y=22-pos_ini_robot_y;

        //   //SUSTITUIR POR UNA FUNCIÓN QUE CALCULE DADAS LAS COORDENADAS
        //   res.long_chapa=15;//sqrt(18)
        //   res.width_chapa=5;//sqrt(8)

        //   break;

      default:
              res.coordA.x=0; res.coordA.y=0;
              res.coordB.x=0; res.coordB.y=0;
              res.coordC.x=0; res.coordC.y=0;
              res.coordD.x=0; res.coordD.y=0;       
              res.long_chapa=0;
              res.width_chapa=0;
              break;
  } 
/*  res.sum = req.a + req.b;
  ROS_INFO("request: x=%ld, y=%ld", (long int)req.a, (long int)req.b);
  ROS_INFO("sending back response: [%ld]", (long int)res.sum);*/

  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "chapa_storage_server");
  ros::NodeHandle n;

  ros::ServiceServer service = n.advertiseService("chapa_storage", chapa_params);
  ROS_INFO("ChapaStorage server is ready");
  ros::spin();

  return 0;
}
