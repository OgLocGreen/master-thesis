#include "irobot_ir_storage_service_class.h"


IROBOT_ir_Storage_Service_Class::IROBOT_ir_Storage_Service_Class()
{
    //Se definen los quaterniones que se usarán más adelante
     q0.x=q0.y=q0.z=0.0; q0.w=1.0;

     q90.x=q90.y=0.0; q90.w=q90.z= 0.707;

     q180.x=q180.y=q180.w=0.0; q180.z=1.0;

     q270.x=q270.y=0.0; q270.w= -0.707; q270.z= 0.707;




    defect_goal=0;
    inspection_goal=0;



    //Se reserva espacio para los vectores de paths
    paths_Hzones_vector.resize(4);
    //paths_Hzones_vector.reserve(4);
    paths_Czones_vector.resize(4);
    paths_inspection_zones_vector.reserve(2);

    vec_path_zonascam_vizmsg.reserve(4);
    vec_paths_zonasherr_vizmsg.resize(4);
    //computeRotationZone();

//    vec_trapeciosarray_vizmsg.reserve(10);

    paths_defects_vector.resize(10);
    paths_tool_defects_vector.resize(10);

    paths_inspection_vector.resize(10);

    reference_frame_string="origin_of_the_universe";

    reparation_bool_pub = n.advertise<std_msgs::Bool>("topic_booleano_reparacion", 1000);
}

void IROBOT_ir_Storage_Service_Class::computePanorama(int id_zona)
{
    ros::NodeHandle nh;

    //create the action client
    // true causes the client to spin its own thread
    actionlib::SimpleActionClient<irobot_inspection_pckg::getPartialPanoramaAction> ac("getPartialPanorama", true);

    ROS_INFO("Waiting for getPano Action server to start.");
    // wait for the action server to start
    ac.waitForServer(); //will wait for infinite time

    ROS_INFO("getPartialPanorama Action server started, sending goal.");



    // send a goal to the action


        irobot_inspection_pckg::getPartialPanoramaGoal goal;
        goal.folder_path.data="/home/irobot-user/imgs_homografia/";


        ac.sendGoal(goal);

        //wait for the action to return
        bool finished_before_timeout = ac.waitForResult(ros::Duration(3600.0));

        if (finished_before_timeout)
        {
          actionlib::SimpleClientGoalState state = ac.getState();
          ROS_INFO("Action finished: %s",state.toString().c_str());
        }
        else
          ROS_INFO("Action did not finish before the time out.");

//        irobot_inspection_pckg::polygonArray arraypoly;
//        arraypoly=ac.getResult()->poly_array;

//        for(auto & poly: arraypoly.polygons)
        //            addPolydefect(poly);


}

void IROBOT_ir_Storage_Service_Class::mergePanoramas()
{
    ros::NodeHandle nh;

    //create the action client
    // true causes the client to spin its own thread
    actionlib::SimpleActionClient<irobot_inspection_pckg::getCompletePanoramaAction> ac("getCompletePanorama", true);

    ROS_INFO("Waiting for getCompletePanorama Action server to start.");
    // wait for the action server to start
    ac.waitForServer(); //will wait for infinite time

    ROS_INFO("getCompletePanorama Action server started, sending goal.");


    // send a goal to the action


        irobot_inspection_pckg::getCompletePanoramaGoal goal;
        goal.folder_pano_path.data="/home/irobot-user/imgs_panorama/";



        ac.sendGoal(goal);

        //wait for the action to return
        bool finished_before_timeout = ac.waitForResult(ros::Duration(3600.0));

        if (finished_before_timeout)
        {
          actionlib::SimpleClientGoalState state = ac.getState();
          ROS_INFO("Action finished: %s",state.toString().c_str());
        }
        else
          ROS_INFO("Action did not finish before the time out.");
}

void IROBOT_ir_Storage_Service_Class::computePolyDetection()
{
    ros::NodeHandle nh;

    //create the action client
    // true causes the client to spin its own thread
    actionlib::SimpleActionClient<irobot_inspection_pckg::getPolygonsAction> ac("getpolygon", true);

    ROS_INFO("Waiting for getPolygons Action server to start.");
    // wait for the action server to start
    ac.waitForServer(); //will wait for infinite time

    ROS_INFO("GetPolygons Action server started, sending goal.");


    // send a goal to the action


        irobot_inspection_pckg::getPolygonsGoal goal;
        goal.path.data="/home/sara/Documentos/Panoramas/panoramaCompleto.png"; // NOMBRE QUE PASE COMO ENTRADA AL ESTADO
        goal.sheet_size_x=longa_x;
        goal.sheet_size_y=longa_y;

        ac.sendGoal(goal);

        //wait for the action to return
        bool finished_before_timeout = ac.waitForResult(ros::Duration(3600.0));

        if (finished_before_timeout)
        {
          actionlib::SimpleClientGoalState state = ac.getState();
          ROS_INFO("Action finished: %s",state.toString().c_str());
        }
        else
          ROS_INFO("Action did not finish before the time out.");

        irobot_inspection_pckg::polygonArray arraypoly;
        arraypoly=ac.getResult()->poly_array;

        for(auto & poly: arraypoly.polygons)
            addPolydefect(poly);
            //addPolydefect(clockwisePolygon(poly));

   }

geometry_msgs::Polygon IROBOT_ir_Storage_Service_Class::clockwisePolygon(geometry_msgs::Polygon orig_poly) //Función que ordena los puntos de un poligono de ROS en sentido de las agujas del reloj
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

void IROBOT_ir_Storage_Service_Class::sortPathsByX(std::vector<geometry_msgs::PoseArray> &path)
{
    // sort using a custom function object
    struct {
        bool operator()(geometry_msgs::PoseArray array1, geometry_msgs::PoseArray array2) const
        {
            return (getXMaxOfPath(array1) > getXMaxOfPath(array2));
        }
    } customsortX;

    std::sort(path.begin(), path.end(), customsortX);
}

double getXMaxOfPath(geometry_msgs::PoseArray path)
{
    double xmax=-999;
    for(auto & elem: path.poses)
    {
        if(elem.position.x>xmax)
            xmax=elem.position.x;
    }
    return xmax;
}

void IROBOT_ir_Storage_Service_Class::sortPathsByY(std::vector<geometry_msgs::PoseArray> &path)
{
    // sort using a custom function object
    struct {
        bool operator()(geometry_msgs::PoseArray array1, geometry_msgs::PoseArray array2) const
        {
            return (getYMaxOfPath(array1) > getYMaxOfPath(array2));
        }
    } customsortY;

    std::sort(path.begin(), path.end(), customsortY);
}

double getYMaxOfPath(geometry_msgs::PoseArray path)
{
    double ymax=-999;
    for(auto & elem: path.poses)
    {
        if(elem.position.y>ymax)
            ymax=elem.position.y;
    }
    return ymax;
}


void IROBOT_ir_Storage_Service_Class::addPolydefect(geometry_msgs::Polygon poly)
{
    poly_vector.push_back(poly);
}

geometry_msgs::Polygon IROBOT_ir_Storage_Service_Class::getPolyDefectAt(int i)
{
    return poly_vector.at(i);
}

void IROBOT_ir_Storage_Service_Class::loop()
{
    service = n.advertiseService("irobot_ir_data", &IROBOT_ir_Storage_Service_Class::service_function, this);
    ROS_INFO("Servicio de almacenamiento de los datos de entrada para el FCPP---> LISTO");
    while (ros::ok())
    {

//        reparation_bool_pub.publish(is_reparating);

        if(publish_vizmsgs_bool==true)
        {
//            if(publish_vizmsgs_firstactivation==true)
//            {
//                initializeVizPubs();
//                publish_vizmsgs_firstactivation=false;
//            }

            poly_chapa_pub.publish(poly_chapa_vizmsg);



            rot_zone_pub.publish(poly_rotzone_vizmsg);

            footprintH_pub.publish(poly_Hfootprint_vizmsg);

            for(int i=0;i<vec_zonas_herr_pubs.size();i++)
            {
                vec_path_zonas_herr_pubs.at(i).publish(vec_paths_zonasherr_vizmsg.at(i));
            }

//            for(int i=0;i<vec_zonas_cam_pubs.size();i++)
//            {
//                vec_path_zonas_cam_pubs.at(i).publish(vec_path_zonascam_vizmsg.at(i));
//            }

            for(int i=0;i<vec_path_defects_pubs.size();i++)
            {
                vec_path_defects_pubs.at(i).publish(vec_path_defects_vizmsg.at(i));
            }


            ordered_msgpath_pub.publish(ordered_path_array_msg);

            ordered_path_pub.publish(ordered_path_vizmsg);
            ordered_toolpath_pub.publish(ordered_toolpath_vizmsg);

    //       footprintherr_pub.publish(herr_footprint_msg);

            for(int i=0;i<vec_zonas_herr_pubs.size();i++)
            {
                vec_zonas_herr_pubs.at(i).publish(vec_zonas_herr_vizmsg.at(i));
            }

            for(int i=0;i<vec_zonas_cam_pubs.size();i++)
            {
                vec_zonas_cam_pubs.at(i).publish(vec_zonas_cam_vizmsg.at(i));
            }

            for(int i=0;i<vec_poligonos_pubs.size();i++)
            {
                vec_poligonos_pubs.at(i).publish(vec_poligonos_vizmsg.at(i));
            }

            for(int i=0;i<vec_trapecios_pubs.size();i++)
            {
                vec_trapecios_pubs.at(i).publish(vec_trapecios_vizmsg.at(i));
            }

            for (int i=0;i<vec_trapeciosarrays_pubs.size(); i++)
            {
                vec_trapeciosarrays_pubs.at(i).publish(vec_trapeciosarray_vizmsg.at(i));
            }

        }



        ros::spinOnce();
    }
}

bool IROBOT_ir_Storage_Service_Class::service_function(irobot_fcpp_simul::IROBOT_ir_data::Request &req,
                                                 irobot_fcpp_simul::IROBOT_ir_data::Response &res)
{
ROS_INFO("-----> Inicio de llamada al servicio de almacenamiento");

    if(req.load_inputdata)
    {
        ///Carga de los datos de entrada

        this->longa_x=req.long_areax; this->longa_y=req.long_areay;//Chapa

        this->longr_x=req.long_robotx; this->longr_y=req.long_roboty;//Robot

        this->longh_x=req.long_herrx; this->longh_y=req.long_herry;//Herramienta
        this->trash_x=req.tras_herrx; this->trash_y=req.tras_herry;

        this->longc_x=req.long_camx; this->longc_y=req.long_camy;//Cámara
        this->trasc_x=req.tras_camx; this->trasc_y=req.tras_camy;


        rot_radius=sqrt(longr_x*0.5*longr_x*0.5+longr_y*0.5*longr_y*0.5)+0.25/*por seguridad*/;
        this->computeRotationZone();

        ROS_INFO("Cargados nuevos datos de entrada al servicio de almacenamiento");
    }

    if(req.load_polygon)
    {
        ///Carga de poligono

        this->addPolydefect(req.input_poly);

        ROS_INFO("Cargado un nuevo poligono");
    }

    ///----------------


    if(req.get_input_data)
    {
        ///Respuesta con los datos de entrada

        res.long_areax=this->longa_x; res.long_areay=this->longa_y;//Chapa

        res.long_robotx=this->longr_x; res.long_roboty=this->longr_y;//Robot

        res.long_herrx=this->longh_x; res.long_herry=this->longh_y;//Herramienta
        res.tras_herrx=this->trash_x; res.tras_herry=this->trash_y;

        res.long_camx=this->longc_x; res.long_camy=this->longh_y;//Cámara
        res.tras_camx=this->trasc_x; res.tras_camy=this->trash_y;


        ROS_INFO("Devueltos los datos de entrada al servicio de almacenamiento");
    }



    if (req.get_inspection_zones)
    {
        ///Respuesta con los datos de la zonas de trabajo para reparar
        if(inspection_zones_vector.size()<1)
        {
            inspection_zones_vector=computeInspectionZones(this->longh_x, this->longh_y, this->trash_x, this->trash_y);
            ROS_INFO("Calculando las zonas de trabajo para la inspeccion...");
        }
        res.zoneh0=inspection_zones_vector.at(0);
        res.zoneh180=inspection_zones_vector.at(1);

        ROS_INFO("Devueltos las zonas de trabajo para la inspeccion ");
    }

    if(req.get_working_zonesh)
    {
        ///Respuesta con los datos de la zonas de trabajo para reparar
        if(working_Hzones_vector.size()<1)
        {
            working_Hzones_vector=computeWorkingZones(this->longh_x, this->longh_y, this->trash_x, this->trash_y);
            ROS_INFO("Calculando las zonas de trabajo para la reparacion...");
        }
        res.zoneh0=working_Hzones_vector.at(0);
        res.zoneh90=working_Hzones_vector.at(1);
        res.zoneh180=working_Hzones_vector.at(2);
        res.zoneh270=working_Hzones_vector.at(3);

        ROS_INFO("Devueltos las zonas de trabajo para la reparacion ");
    }


    if(req.get_working_zonesc)
    {
        ///Respuesta con los datos de la zonas de trabajo para inspeccionar
        if(working_Czones_vector.size()<1)
        {
            working_Czones_vector=computeInspectionZones(this->longc_x, this->longc_y, this->trasc_x, this->trasc_y);
            ROS_INFO("Calculando las zonas de trabajo para la inspeccion...");
        }

        res.zonec0=working_Czones_vector.at(0);
        res.zonec90=working_Czones_vector.at(1);
        res.zonec180=working_Czones_vector.at(2);
        res.zonec270=working_Czones_vector.at(3);


        ROS_INFO("Devueltas las zonas de trabajo para la inspeccion ");
    }

    if(req.get_poly_i)
    {
        res.poly_i=poly_vector.at(req.id_poly);
    }


    if(req.get_defect_i)
    {
        ///Respuesta con los datos de la zonas de trabajo para inspeccionar
        if(defectos_vec.size()<1)//Si nunca se le ha llamado
        {
            computeDefectsDecomposition();
            ROS_INFO("Calculando la estructura de defectos por primera vez...");
        }

        res.defecto_i=defectos_vec.at(req.id_defecto);
        res.n_defectos=defectos_vec.size();


        ROS_INFO("Devuelto el defecto solicitado ");
    }
//////
    if (req.get_inspection_path)
    {
       res.inspection_i_paths = paths_Czones_vector;

       int a= 0;

       ROS_INFO("Devuelto el path de la inspeccion seleccionada ");

    }
//////
    if(req.get_defect_path)
    {

//        for (auto & elemarray : paths_defects_vector.at(defect_goal))
//        {
//                res.defect_i_paths.push_back(elemarray);
//        }

        res.defect_i_paths=preparePathForExecution(paths_defects_vector.at(defect_goal));

        std::vector<geometry_msgs::PoseArray> aux_tool_path=preparePathForExecution(paths_tool_defects_vector.at(defect_goal));



        geometry_msgs::PoseArray aux_posearray;
        for(int i=0; i<res.defect_i_paths.size();i++)
        {
            for(auto & elem: res.defect_i_paths.at(i).poses)
                aux_posearray.poses.push_back(elem);
        }

        visualization_msgs::Marker vizmsg_aux=PoseVector2VizMarker(aux_posearray);
        ordered_path_array_msg=aux_posearray;
        ordered_path_vizmsg=vizmsg_aux;


        geometry_msgs::PoseArray aux_toolposearray;
        for(int i=0; i<aux_tool_path.size();i++)
        {
            for(auto & elem: aux_tool_path.at(i).poses)
                aux_toolposearray.poses.push_back(elem);
        }

        visualization_msgs::Marker viztoolmsg_aux=PoseVector2VizMarker(aux_toolposearray);
        ordered_toolpath_vizmsg=viztoolmsg_aux;




        ROS_INFO("Devuelto el path del defecto seleccionado ");
    }




    if(req.get_rot_zone)
    {
        ///Respuesta con los datos de entrada
        res.zone_rot=this->rotation_zone;

        ROS_INFO("Devuelta la zona de rotacion segura ");
    }


    if(req.activate_vizs)
    {
        updateVizMsgs();


        ROS_INFO("Activadas las visualizaciones de Rviz");



    }


    if(req.compute_fcpp_defect_i)
    {
        ///Calcular el path para el defecto i
        computeDefectFCPP(req.id_defecto);
    }

    if(req.compute_fcpp_inspection_zone_i)
    {
        ///Calcular el path para la zona i
        computeInspectionZoneFCPP(req.id_zona);
    }

    if(req.compute_fcpp_zone_i)
    {
        ///Calcular el path para la zona i
        computeWorkingZoneFCPP(req.id_zona);
    }


    if (req.change_inspection_goal)
    {
        inspection_goal = req.id_zona;
        ROS_INFO("Modificado el path objetivo");
    }

    if(req.change_defect_reparation_goal)
    {
        defect_goal=req.id_defecto;
        ROS_INFO("Modificado el path objetivo");
    }

    if (req.compute_adquireimgs)
    {
        ROS_INFO("Llamada a la accion de adquisición de imagenes");
    }

    if (req.compute_panorama)
    {
        computePanorama(req.id_zona);
        ROS_INFO("Realizado cálculo del panorama");
    }

    if (req.merge_panoramas)
    {
        mergePanoramas();
        ROS_INFO("Completado el panorama combinado");
    }

    if (req.compute_detectpolys)
    {
        computePolyDetection();
        ROS_INFO("Realizada detección de imagenes");
    }


ROS_INFO("Fin de la llamada al servicio de almacenamiento <-------");
ROS_INFO("---");
    return true;

}

std::vector<geometry_msgs::Polygon> IROBOT_ir_Storage_Service_Class::computeWorkingZones(double long_act_x, double long_act_y,
                                                                                         double tras_act_x, double tras_act_y)
{
    return computeWorkingZones(this->longa_x, this->longa_y,
                               this->longr_x, this->longr_y,
                               long_act_x, long_act_y,
                               tras_act_x, tras_act_y);
}


std::vector<geometry_msgs::Polygon> IROBOT_ir_Storage_Service_Class::computeInspectionZones(double long_act_x, double long_act_y,
                                                                                         double tras_act_x, double tras_act_y)
{
    return computeInspectionZones(this->longa_x, this->longa_y,
                               this->longr_x, this->longr_y,
                               long_act_x, long_act_y,
                               tras_act_x, tras_act_y);
}


std::vector<geometry_msgs::Polygon> IROBOT_ir_Storage_Service_Class::computeInspectionZones(double long_area_x, double long_area_y,
                                                                                         double long_robot_x, double long_robot_y,
                                                                                         double long_act_x, double long_act_y,
                                                                                         double tras_act_x, double tras_act_y)
{
    ///Parametros chapa
    double hc=long_area_x*100*0.5; //*100 en esta funcion se trabaja en cm
    double lc=long_area_y*100*0.5;

    //double hc=150; double lc=300;

    Vec3b c_fondo(25,25,25);
    Vec3b c_chapa(38,17,187);//granate

    Vec3b c_zona0(17,178,33);//verde
    Vec3b c_zona90(178,84,17); //azul
    Vec3b c_zona180(4,185,221); //amarillo
    Vec3b c_zona270(221,4,127); //violeta


    double tras_origen=50;


    int hc2_pix=2*(hc+tras_origen); //y
    int lc2_pix=2*(lc+tras_origen); //x


    cv::Mat img=Mat(hc2_pix,lc2_pix,CV_8UC3, c_fondo);
    cv::Mat img_int=Mat::zeros(hc2_pix,lc2_pix,CV_8UC1);

    for(int h=-hc; h<hc ; h++ )
    {
        for(int l=-lc; l<lc ; l++)
        {
            int h_pix=h+(int)hc+tras_origen;
            int l_pix=l+(int)lc+tras_origen;
            img.at<Vec3b>(h_pix, l_pix)=c_chapa;
            img_int.at<uchar>(h_pix, l_pix)=1;
        }
    }
//        imshow("debug", img);
//        cv::waitKey();


    //Muestra una imagen

    ///Parametros robot
    double offset_xd=tras_act_x;
    double offset_yd=tras_act_y;

    double l_sherpaxl=44*0.5; double h_sherpaxl=58*0.5;

    double lmax= (lc - offset_xd)*0.5;
    double hmax= (hc - offset_yd)*0.5;

    double lr=long_robot_x*0.5;//l_sherpaxl;
    double hr=long_robot_y*0.5;//h_sherpaxl;

    //Máscara robot
    cv::Mat img_r=Mat::ones(2*hr+1, 2*lr+1, CV_8UC1);


    ///Parametros herramienta
     double xd=lr+offset_xd;
     double yd=hr+offset_yd;
     std::cout<<yd<<std::endl;

     //Máscara de la herr
     cv::Mat img_h=Mat::zeros(2*abs(yd)+1, 2*abs(xd)+1, CV_8UC1);
             //img_h.at<uchar>(abs(yd)+1-yd, abs(xd)+1+xd)=1; //?
             img_h.at<uchar>(1,1)=1; //double long_act_x, double long_act_y


             // Zona navegable con ejes paralelos
                      cv::Mat zona0 = computePossibleWorkingArea(img_int, img_r, img_h, rot0);
                      cv::Mat mat_disp=img;

                      double cota_max;

                      double xmin_aux, ymin_aux, xmax_aux, ymax_aux;
                      xmax_aux=ymax_aux=0;
                      xmin_aux=ymin_aux=10000000;

                      for(int f=0; f<zona0.rows; f++)
                      {
                          for(int c=0; c<zona0.cols; c++)
                          {
                              if(zona0.at<uchar>(f,c)==1)
                              {
                                  mat_disp.at<Vec3b>(f,c)=c_zona0;
                                 if(f>xmax_aux) xmax_aux=f;
                                 if(f<xmin_aux) xmin_aux=f;
                                 if(c<ymin_aux) ymin_aux=c;
                                 if(c>ymax_aux) ymax_aux=c;
                              }
                          }
                      }
                      rectangle_limits z0_rl;
                      z0_rl.xmin=(xmin_aux-tras_origen)*.01; z0_rl.xmax=(xmax_aux-tras_origen)*.01;
                      z0_rl.ymin=(ymin_aux-tras_origen)*.01; z0_rl.ymax=(ymax_aux-tras_origen)*.01;

                      if(z0_rl.ymin<=0.0)
                          cota_max=z0_rl.ymax;
                      else
                          cota_max=z0_rl.ymin;

             //         imshow("disp0", mat_disp);
             //         cv::waitKey();


                      // I am going

                      // Zona navegable con giro 180
                      xmax_aux=ymax_aux=0;
                      xmin_aux=ymin_aux=10000000;
                      cv::Mat zona180 = computePossibleWorkingArea(img_int, img_r, img_h, rot180);
                      for(int f=0; f<zona180.rows; f++)
                      {
                          for(int c=0; c<zona180.cols; c++)
                          {
                              if(/*zona180.at<uchar>(f,c)==1 && */zona0.at<uchar>(f,c)==1)//0 /*&& zona90.at<uchar>(f,c)==0 && zona180.at<uchar>(f,c)==0*/)
                              {
                                  mat_disp.at<Vec3b>(f,c)=c_zona180;
                                  if(f>xmax_aux) xmax_aux=f;
                                  if(f<xmin_aux) xmin_aux=f;
                                  if(c<ymin_aux) ymin_aux=c;
                                  if(c>ymax_aux) ymax_aux=c;
                              }
                          }
                      }
                      rectangle_limits z180_rl;
                      z180_rl.xmin=(xmin_aux-tras_origen)*.01; z180_rl.xmax=(xmax_aux-tras_origen)*.01;
                      z180_rl.ymin=(ymin_aux-tras_origen)*.01; z180_rl.ymax=(ymax_aux-tras_origen)*.01;

                      if(z180_rl.ymin<=0.0)
                          z180_rl.ymax=cota_max;
                      else
                          z180_rl.ymin=cota_max;



                      double xmin=0.0; double xmax=long_area_x;
                      double ymin=0.0; double ymax=long_area_y;
                      adjustRectlimits2maxmin(z0_rl,   xmin, xmax, ymin, ymax);
                      adjustRectlimits2maxmin(z180_rl, xmin, xmax, ymin, ymax);

                      rectangle_limits z90_rl;
                      rectangle_limits z270_rl;

                      std::vector<geometry_msgs::Polygon> inspection_zones_vector;
                      inspection_zones_vector.push_back(rectlimits2rosPolygon(z0_rl));
                      inspection_zones_vector.push_back(rectlimits2rosPolygon(z90_rl));
                      inspection_zones_vector.push_back(rectlimits2rosPolygon(z180_rl));
                      inspection_zones_vector.push_back(rectlimits2rosPolygon(z270_rl));
                      return inspection_zones_vector;


}

std::vector<geometry_msgs::Polygon> IROBOT_ir_Storage_Service_Class::computeWorkingZones(double long_area_x, double long_area_y,
                                                                                         double long_robot_x, double long_robot_y,
                                                                                         double long_act_x, double long_act_y,
                                                                                         double tras_act_x, double tras_act_y)
{
        ///Parametros chapa
        double hc=long_area_x*100*0.5; //*100 en esta funcion se trabaja en cm
        double lc=long_area_y*100*0.5;

        //double hc=150; double lc=300;

        Vec3b c_fondo(25,25,25);
        Vec3b c_chapa(38,17,187);//granate

        Vec3b c_zona0(17,178,33);//verde
        Vec3b c_zona90(178,84,17); //azul
        Vec3b c_zona180(4,185,221); //amarillo
        Vec3b c_zona270(221,4,127); //violeta


        double tras_origen=200;


        int hc2_pix=2*(hc+tras_origen); //y
        int lc2_pix=2*(lc+tras_origen); //x


        cv::Mat img=Mat(hc2_pix,lc2_pix,CV_8UC3, c_fondo);
        cv::Mat img_int=Mat::zeros(hc2_pix,lc2_pix,CV_8UC1);

        for(int h=-hc; h<hc ; h++ )
        {
            for(int l=-lc; l<lc ; l++)
            {
                int h_pix=h+(int)hc+tras_origen;
                int l_pix=l+(int)lc+tras_origen;
                img.at<Vec3b>(h_pix, l_pix)=c_chapa;
                img_int.at<uchar>(h_pix, l_pix)=1;
            }
        }
//        imshow("debug", img);
//        cv::waitKey();


        //Muestra una imagen

        ///Parametros robot
        double offset_xd=tras_act_x;
        double offset_yd=tras_act_y;

        double l_sherpaxl=44*0.5; double h_sherpaxl=58*0.5;

        double lmax= (lc - offset_xd)*0.5;
        double hmax= (hc - offset_yd)*0.5;

        double lr=long_robot_x*0.5;//l_sherpaxl;
        double hr=long_robot_y*0.5;//h_sherpaxl;

        //Máscara robot
        cv::Mat img_r=Mat::ones(2*hr+1, 2*lr+1, CV_8UC1);


        ///Parametros herramienta
         double xd=lr+offset_xd;
         double yd=hr+offset_yd;
         std::cout<<yd<<std::endl;

         //Máscara de la herr
         cv::Mat img_h=Mat::zeros(2*abs(yd)+1, 2*abs(xd)+1, CV_8UC1);
                 //img_h.at<uchar>(abs(yd)+1-yd, abs(xd)+1+xd)=1; //?
                 img_h.at<uchar>(1,1)=1; //double long_act_x, double long_act_y

///ZONA 0
// Zona navegable con ejes paralelos
         cv::Mat zona0 = computePossibleWorkingArea(img_int, img_r, img_h, rot0);
         cv::Mat mat_disp=img;

         double cota_max;

         double xmin_aux, ymin_aux, xmax_aux, ymax_aux;
         xmax_aux=ymax_aux=0;
         xmin_aux=ymin_aux=10000000;

         for(int f=0; f<zona0.rows; f++)
         {
             for(int c=0; c<zona0.cols; c++)
             {
                 if(zona0.at<uchar>(f,c)==1)
                 {
                     mat_disp.at<Vec3b>(f,c)=c_zona0;
                    if(f>xmax_aux) xmax_aux=f;
                    if(f<xmin_aux) xmin_aux=f;
                    if(c<ymin_aux) ymin_aux=c;
                    if(c>ymax_aux) ymax_aux=c;
                 }
             }
         }
         rectangle_limits z0_rl;
         z0_rl.xmin=(xmin_aux-tras_origen)*.01; z0_rl.xmax=(xmax_aux-tras_origen)*.01;
         z0_rl.ymin=(ymin_aux-tras_origen)*.01; z0_rl.ymax=(ymax_aux-tras_origen)*.01;

         if(z0_rl.ymin<=0.0)
             cota_max=z0_rl.ymax;
         else
             cota_max=z0_rl.ymin;

//         imshow("disp0", mat_disp);
//         cv::waitKey();


         // I am going

         // Zona navegable con giro 180
         xmax_aux=ymax_aux=0;
         xmin_aux=ymin_aux=10000000;
         cv::Mat zona180 = computePossibleWorkingArea(img_int, img_r, img_h, rot180);
         for(int f=0; f<mat_disp.rows; f++)
         {
             for(int c=0; c<mat_disp.cols; c++)
             {
                 if(zona180.at<uchar>(f,c)==1 && zona0.at<uchar>(f,c)==0)//0 /*&& zona90.at<uchar>(f,c)==0 && zona180.at<uchar>(f,c)==0*/)
                 {
                     mat_disp.at<Vec3b>(f,c)=c_zona180;
                     if(f>xmax_aux) xmax_aux=f;
                     if(f<xmin_aux) xmin_aux=f;
                     if(c<ymin_aux) ymin_aux=c;
                     if(c>ymax_aux) ymax_aux=c;
                 }
             }
         }
         rectangle_limits z180_rl;
         z180_rl.xmin=(xmin_aux-tras_origen)*.01; z180_rl.xmax=(xmax_aux-tras_origen)*.01;
         z180_rl.ymin=(ymin_aux-tras_origen)*.01; z180_rl.ymax=(ymax_aux-tras_origen)*.01;

         if(z180_rl.ymin<=0.0)
             z180_rl.ymax=cota_max;
         else
             z180_rl.ymin=cota_max;

         // Zona navegable con giro 90
         cv::Mat zona90 = computePossibleWorkingArea(img_int, img_r, img_h, rot90);
         xmax_aux=ymax_aux=0;
         xmin_aux=ymin_aux=10000000;
         for(int f=0; f<mat_disp.rows; f++)
         {
             for(int c=0; c<mat_disp.cols; c++)
             {
                 if(zona90.at<uchar>(f,c)==1 && zona0.at<uchar>(f,c)==0 && zona180.at<uchar>(f,c)==0)
                 {
                     mat_disp.at<Vec3b>(f,c)=c_zona90;
                     if(f>xmax_aux) xmax_aux=f;
                     if(f<xmin_aux) xmin_aux=f;
                     if(c<ymin_aux) ymin_aux=c;
                     if(c>ymax_aux) ymax_aux=c;
                 }
             }
         }
         rectangle_limits z90_rl;
         z90_rl.xmin=(xmin_aux-tras_origen)*.01; z90_rl.xmax=(xmax_aux-tras_origen)*.01;
         z90_rl.ymin=(ymin_aux-tras_origen)*.01; z90_rl.ymax=(ymax_aux-tras_origen)*.01;


         if(z90_rl.ymin<=0.0)
             z90_rl.ymax=cota_max;
         else
             z90_rl.ymin=cota_max;


//         imshow("disp90", mat_disp);
//         cv::waitKey();

         // Zona navegable con giro 270
         xmax_aux=ymax_aux=0;
         xmin_aux=ymin_aux=10000000;
         cv::Mat zona270 = computePossibleWorkingArea(img_int, img_r, img_h, rot270);
         for(int f=0; f<mat_disp.rows; f++)
         {
             for(int c=0; c<mat_disp.cols; c++)
             {
                 if(zona270.at<uchar>(f,c)==1 && zona0.at<uchar>(f,c)==0 && zona90.at<uchar>(f,c)==0 && zona180.at<uchar>(f,c)==0)
                 {
                     mat_disp.at<Vec3b>(f,c)=c_zona270;
                     if(f>xmax_aux) xmax_aux=f;
                     if(f<xmin_aux) xmin_aux=f;
                     if(c<ymin_aux) ymin_aux=c;
                     if(c>ymax_aux) ymax_aux=c;
                 }
             }
         }
         rectangle_limits z270_rl;
         z270_rl.xmin=(xmin_aux-tras_origen)*.01; z270_rl.xmax=(xmax_aux-tras_origen)*.01;
         z270_rl.ymin=(ymin_aux-tras_origen)*.01; z270_rl.ymax=(ymax_aux-tras_origen)*.01;

         if(z270_rl.ymin<=0.0)
             z270_rl.ymax=cota_max;
         else
             z270_rl.ymin=cota_max;

//         imshow("disp180", mat_disp);
//          cv::waitKey();

////Se vuelve a calcular la zona 0
//         xmax_aux=ymax_aux=0;
//         xmin_aux=ymin_aux=10000000;

//         for(int f=0; f<zona0.rows; f++)
//         {
//             for(int c=0; c<zona0.cols; c++)
//             {
//                 if(zona0.at<uchar>(f,c)==1 && !isInsideRectLimits((f-tras_origen)*.01,(c-tras_origen)*.01, z90_rl)
//                                            && !isInsideRectLimits((f-tras_origen)*.01,(c-tras_origen)*.01, z180_rl)
//                                            && !isInsideRectLimits((f-tras_origen)*.01,(c-tras_origen)*.01, z270_rl))
//                 {
//                     //mat_disp.at<Vec3b>(f,c)=c_zona0;
//                    if(f>xmax_aux) xmax_aux=f;
//                    if(f<xmin_aux) xmin_aux=f;
//                    if(c<ymin_aux) ymin_aux=c;
//                    if(c>ymax_aux) ymax_aux=c;
//                 }
//             }
//         }
//         rectangle_limits z0_rl;
//         z0_rl.xmin=(xmin_aux-tras_origen)*.01; z0_rl.xmax=(xmax_aux-tras_origen)*.01;
//         z0_rl.ymin=(ymin_aux-tras_origen)*.01; z0_rl.ymax=(ymax_aux-tras_origen)*.01;

        //Zonas numeradas del 1-10 en la funcion

//    cv::imshow("imagen",mat_disp);
//    cv::waitKey();

    double xmin=0.0; double xmax=long_area_x;
    double ymin=0.0; double ymax=long_area_y;
    adjustRectlimits2maxmin(z0_rl,   xmin, xmax, ymin, ymax);
    adjustRectlimits2maxmin(z90_rl,  xmin, xmax, ymin, ymax);
    adjustRectlimits2maxmin(z180_rl, xmin, xmax, ymin, ymax);
    adjustRectlimits2maxmin(z270_rl, xmin, xmax, ymin, ymax);

    std::vector<geometry_msgs::Polygon> working_zones_vector;
    working_zones_vector.push_back(rectlimits2rosPolygon(z0_rl));     working_zones_vector.push_back(rectlimits2rosPolygon(z90_rl));
    working_zones_vector.push_back(rectlimits2rosPolygon(z180_rl));   working_zones_vector.push_back(rectlimits2rosPolygon(z270_rl));
    return working_zones_vector;
}

cv::Mat IROBOT_ir_Storage_Service_Class::computePossibleWorkingArea(cv::Mat img_areatotal, cv::Mat img_robot, cv::Mat img_herr, GradosRotacion rotation)
{
//    cv::Mat img_robot2, img_herr2;
//    cv::flip(img_robot,img_robot2,0);
//    cv::flip(img_herr,img_herr2,0);

    std::vector<cv::Mat> return_vector;

    cv::Mat a1;//Solo para inicializarlos


    img_robot=rotatek90Mat(img_robot,rotation);
    cv::erode(img_areatotal, a1, img_robot);
    return_vector.push_back(a1);

    cv::Mat a2;
    img_herr=rotatek90Mat(img_herr,rotation);
    cv::erode(img_areatotal,a2, img_herr); //hay que rotar la de la herramienta
    return_vector.push_back(a2);

    cv::Mat a3;
    a3=a1 & a2;
    return_vector.push_back(a3);


    cv::Mat a4;
    cv::dilate(a3, a4, img_herr);

    return a4;
}

cv::Mat IROBOT_ir_Storage_Service_Class::rotatek90Mat(cv::Mat img, GradosRotacion rotation)
{
    cv::Mat mat_return;
    switch (rotation)
    {
    case rot0:
        mat_return=img;
        break;
    case rot90:
        cv::rotate(img, mat_return, ROTATE_90_COUNTERCLOCKWISE);
//        transpose(img, mat_return);
//        flip(mat_return, mat_return, +1);
        break;
    case rot180:
        cv::rotate(img, mat_return, ROTATE_180);
//        flip(img, mat_return, -1);
        break;
    case rot270:
        cv::rotate(img, mat_return, ROTATE_90_CLOCKWISE);
//        transpose(img, mat_return);
//        flip(mat_return, mat_return, 0);
        break;
    }

    return mat_return;
}

void IROBOT_ir_Storage_Service_Class::computeRotationZone()
{
    rectangle_limits zone;

    //Zonas numeradas del 1-10 en la funcion

    //Zona 1
    zone.xmin=0.0+rot_radius;
    zone.ymin=0.0+rot_radius;
    zone.xmax=longa_x-rot_radius;
    zone.ymax=longa_y-rot_radius;

    rl_rotation_zone=zone;

    rotation_zone=rectlimits2rosPolygon(zone);
}

void IROBOT_ir_Storage_Service_Class::computeDefectsDecomposition()
{

      ros::NodeHandle nh;

      //create the action client
      // true causes the client to spin its own thread
      actionlib::SimpleActionClient<irobot_fcpp_simul::ComputeDefectsDecompAction> ac("ComputeDefects", true);

      ROS_INFO("Waiting for ComputeDefectsDecomp Action server to start.");
      // wait for the action server to start
      ac.waitForServer(); //will wait for infinite time

      ROS_INFO("ComputeDefectsDecomp Action server started, sending goal.");


      // send a goal to the action

      for(int i=0; i<poly_vector.size(); i++)
      {
          irobot_fcpp_simul::defecto d_msg;
          irobot_fcpp_simul::ComputeDefectsDecompGoal goal;
                                                      //goal.chapa_id=i;
                                                      goal.poly_defect=poly_vector.at(i);

                                                      goal.xmax=this->longa_x;
                                                      goal.ymax=this->longa_y;

                                                      goal.zone0=this->working_Hzones_vector.at(0);
                                                      goal.zone90=this->working_Hzones_vector.at(1);
                                                      goal.zone180=this->working_Hzones_vector.at(2);
                                                      goal.zone270=this->working_Hzones_vector.at(3);

          ac.sendGoal(goal);

          //wait for the action to return
          bool finished_before_timeout = ac.waitForResult(ros::Duration(30.0));

          if (finished_before_timeout)
          {
            actionlib::SimpleClientGoalState state = ac.getState();
            ROS_INFO("Action finished: %s",state.toString().c_str());
          }
          else
            ROS_INFO("Action did not finish before the time out.");


          d_msg=ac.getResult()->defecto;
          defectos_vec.push_back(d_msg);
     }

      //Subir los vectores de defectos a un servicio




}

void IROBOT_ir_Storage_Service_Class::computeInspectionZoneFCPP(int id_zona)
{

    paths_Czones_vector.clear();
    paths_Czones_vector.resize(4);

    std::string robot_model_name="summit_xl_a";
    std::string tf_robot_name="summit_xl_a_base_link";
    std::string tf_reference_frame_name="chapa_orig";

    TYPE_OF_PATH type_of_path;

    switch(id_zona)
    {
        case 0: case 2:          case 180:
            type_of_path=Y_CTE;break;           //En teoria al reves pero asi es como funciona

        case 1: case 3: case 90: case 270:
            type_of_path=X_CTE;break;
    }

    int id_vector;
    if(id_zona==0)id_vector=0;
    if(id_zona==90 || id_zona == 1)id_vector=1;
    if(id_zona==180 || id_zona == 2)id_vector=2;
    if(id_zona==270 || id_zona == 3)id_vector=3;

    //Separacion entre carriles
    double step=1; //Estaba 0.5

    if (type_of_path==X_CTE)
        step=longh_x*1.5; //long_herr_y=0.5--->Valor tan alto para hacer visible descomposicion en zonas?
    if(type_of_path==Y_CTE)
        step=longh_y*1.5;


   TrapPathPlanning path(working_Czones_vector.at(id_vector),step, type_of_path);

   std::vector<geometry_msgs::Point> path_result;

   geometry_msgs::Point ref_p;
                        ref_p.x=this->longa_x; ref_p.y=this->longa_y;

   path_result =path.generatePath();
   path_result =path.computePathStartingFromNearestPoint(ref_p);


   double transf_tras_x, transf_tras_y;


   //Calcula traslacion
   switch (id_vector)
   {
       case 0://0
            transf_tras_x=1*this->trash_x*0.01;
            transf_tras_y=-1*this->trash_y*0.01;
           break;
       case 1://90
            transf_tras_x=+1*this->trash_y*0.01;
            transf_tras_y=-1*this->trash_x*0.01;
           break;
       case 2://180
            transf_tras_x=1*this->trash_x*0.01;
            transf_tras_y=-1*this->trash_y*0.01;
           break;
       case 3://270
            transf_tras_x=-1*this->trash_y*0.01;
            transf_tras_y=+1*this->trash_x*0.01;
           break;

   }


   translatePoints(path_result,transf_tras_x,transf_tras_y);

   for(auto & elem: path_result)
   {
       geometry_msgs::Pose pose_aux;
       pose_aux.position=elem;

       switch (id_vector)
       {
           case 0://0
               pose_aux.orientation=q0;
               break;
           case 1://90
               pose_aux.orientation=q90;
               break;
           case 2://180
               pose_aux.orientation=q180;
               break;
           case 3://270
               pose_aux.orientation=q270;
               break;

       }


       paths_Czones_vector.at(id_vector).poses.push_back(pose_aux);
   }
    paths_Czones_vector.at(id_vector).header.frame_id="origin_of_the_universe";


   path_inspection_calculated=true;
}

void IROBOT_ir_Storage_Service_Class::computeWorkingZoneFCPP(int id_zona)
{

      std::string robot_model_name="summit_xl_a";
      std::string tf_robot_name="summit_xl_a_base_link";
      std::string tf_reference_frame_name="chapa_orig";

  TYPE_OF_PATH type_of_path;

    switch(id_zona)
    {
        case 0: case 2:          case 180:
            type_of_path=Y_CTE;break;           //En teoria al reves pero asi es como funciona

        case 1: case 3: case 90: case 270:
            type_of_path=X_CTE;break;
    }


    int id_vector;
    if(id_zona==0)id_vector=0;
    if(id_zona==90)id_vector=1;
    if(id_zona==180)id_vector=2;
    if(id_zona==270)id_vector=3;



    //Separacion entre carriles
    double step=0.5; //Estaba 0.1

    if (type_of_path==X_CTE)
        step=longh_x*1; //long_herr_y=0.5--->Valor tan alto para hacer visible descomposicion en zonas?
    if(type_of_path==Y_CTE)
        step=longh_y*1;


   TrapPathPlanning path(working_Hzones_vector.at(id_vector),step, type_of_path);

   std::vector<geometry_msgs::Point> path_result;

   geometry_msgs::Point ref_p;
                        ref_p.x=this->longa_x; ref_p.y=this->longa_y;

   path_result =path.generatePath();
   path_result =path.computePathStartingFromNearestPoint(ref_p);



//   geometry_msgs::Pose herr_respecto_orig=getRobotPose("projected_coupled_tool",tf_reference_frame_name);
//   geometry_msgs::Pose base_respecto_orig=getRobotPose(tf_robot_name,tf_reference_frame_name);
//   //Trasladar puntos para que los ejecute el robot


//   translatePoints(path_result, -1*(herr_respecto_orig.position.x-base_respecto_orig.position.x),
//                                -1*(herr_respecto_orig.position.y-base_respecto_orig.position.y));

   double transf_tras_x, transf_tras_y;


   //Calcula traslacion
   switch (id_vector)
   {
       case 0://0
            transf_tras_x=-1*this->trash_x*0.01;
            transf_tras_y=-1*this->trash_y*0.01;
           break;
       case 1://90
            transf_tras_x=+1*this->trash_y*0.01;
            transf_tras_y=-1*this->trash_x*0.01;
           break;
       case 2://180
            transf_tras_x=1*this->trash_x*0.01;
            transf_tras_y=1*this->trash_y*0.01;
           break;
       case 3://270
            transf_tras_x=-1*this->trash_y*0.01;
            transf_tras_y=+1*this->trash_x*0.01;
           break;
   }


   translatePoints(path_result,transf_tras_x,transf_tras_y);

   for(auto & elem: path_result)
   {
       geometry_msgs::Pose pose_aux;
       pose_aux.position=elem;

       switch (id_vector)
       {
           case 0://0
               pose_aux.orientation=q0;
               break;
           case 1://90
               pose_aux.orientation=q90;
               break;
           case 2://180
               pose_aux.orientation=q180;
               break;
           case 3://270
               pose_aux.orientation=q270;
               break;
       }


       paths_Hzones_vector.at(id_vector).poses.push_back(pose_aux);
   }
    paths_Hzones_vector.at(id_vector).header.frame_id="origin_of_the_universe";


   path_calculated=true;
}

void IROBOT_ir_Storage_Service_Class::computeDefectFCPP(int id_defect)
{


    std::string robot_model_name="summit_xl_a";
    std::string tf_robot_name="summit_xl_a_base_link";
    std::string tf_reference_frame_name="chapa_orig";

TYPE_OF_PATH type_of_path;

    if (id_defect<0 || id_defect>defectos_vec.size()-1)
        return;

  switch(id_defect)
  {
      case 0: case 2:          case 180:
          type_of_path=Y_CTE;break;           //En teoria al reves pero asi es como funciona

      case 1: case 3: case 90: case 270:
          type_of_path=X_CTE;break;
  }

  for(int zona_i=0; zona_i<4; zona_i++)
  {
      for(auto & elem: defectos_vec.at(id_defect).defecto_divpor_zonas)
      {
          geometry_msgs::Point ref_p;
                               ref_p.x=this->longa_x; ref_p.y=this->longa_y;


           geometry_msgs::Point last_pose;
           last_pose.x=ref_p.x;
           last_pose.y=ref_p.y;

          if(elem.zona==zona_i)
          {
              for( auto & elemt: elem.trap_vec)
              {
                  //Calcular path planning desde el punto más cercano
                   ROS_INFO("Nuevo trapecio");

                  TYPE_OF_PATH type_of_path;
                  if(elem.direccion_rep==XPOS || elem.direccion_rep==XNEG)
                      type_of_path=Y_CTE;
                  else
                      type_of_path=X_CTE;

                  TrapPathPlanning path(elemt.ros_poly,0.15, type_of_path);
                  std::vector<geometry_msgs::Point> path_result;

                  path_result = path.generatePath();

                  path_result =path.computePathStartingFromNearestPoint(ref_p);


                    //guardado del path original
                  geometry_msgs::PoseArray trap_toolfcpp_path;
                  trap_toolfcpp_path.header.frame_id="origin_of_the_universe";
                  for(auto & elem: path_result)
                  {
                      geometry_msgs::Pose pose_aux;
                      pose_aux.position=elem;
                      switch (zona_i)
                      {
                          case 0://0
                              pose_aux.orientation=q0;
                              break;
                          case 1://90
                              pose_aux.orientation=q90;
                              break;
                          case 2://180
                              pose_aux.orientation=q180;
                              break;
                          case 3://270
                              pose_aux.orientation=q270;
                              break;
                      }

                      trap_toolfcpp_path.poses.push_back(pose_aux);

                      last_pose.x=pose_aux.position.x;
                      last_pose.y=pose_aux.position.y;


                  }


                  paths_tool_defects_vector.at(id_defect).push_back(trap_toolfcpp_path);






                  double transf_tras_x, transf_tras_y;


                  //Calcula traslacion
                  switch (zona_i)
                  {
                      case 0://0
                           transf_tras_x=-1*this->trash_x*0.01;
                           transf_tras_y=-1*this->trash_y*0.01;
                          break;
                      case 1://90
                           transf_tras_x=+1*this->trash_y*0.01;
                           transf_tras_y=-1*this->trash_x*0.01;
                          break;
                      case 2://180
                           transf_tras_x=1*this->trash_x*0.01;
                           transf_tras_y=1*this->trash_y*0.01;
                          break;
                      case 3://270
                           transf_tras_x=-1*this->trash_y*0.01;
                           transf_tras_y=+1*this->trash_x*0.01;
                          break;
                  }


                  translatePoints(path_result,transf_tras_x,transf_tras_y);





                  geometry_msgs::PoseArray trap_fcpp_path;
                  trap_fcpp_path.header.frame_id="origin_of_the_universe";
                  for(auto & elem: path_result)
                  {
                      geometry_msgs::Pose pose_aux;
                      pose_aux.position=elem;
                      switch (zona_i)
                      {
                          case 0://0
                              pose_aux.orientation=q0;
                              break;
                          case 1://90
                              pose_aux.orientation=q90;
                              break;
                          case 2://180
                              pose_aux.orientation=q180;
                              break;
                          case 3://270
                              pose_aux.orientation=q270;
                              break;
                      }

                      trap_fcpp_path.poses.push_back(pose_aux);

                  }

                  paths_defects_vector.at(id_defect).push_back(trap_fcpp_path);

              }

         }
      }
}
  //preparePathsForExecution(path_defects_vector.at(id_defect));

}

void IROBOT_ir_Storage_Service_Class::translatePoints(std::vector<geometry_msgs::Point> &vector, double tras_x, double tras_y)
{
    for(auto & elem: vector)
    {
        elem.x=elem.x+tras_x;
        elem.y=elem.y+tras_y;
    }
}

std::vector<geometry_msgs::PoseArray> IROBOT_ir_Storage_Service_Class::preparePathForExecution(std::vector<geometry_msgs::PoseArray> &pathsarray)
{

    //Se dividen los paths por zonas
    std::vector<geometry_msgs::PoseArray> prepared_path;
    std::vector<geometry_msgs::PoseArray> paths0, paths90, paths180, paths270;

    for (auto & elem: pathsarray)
    {
        geometry_msgs::Quaternion rot=elem.poses.at(0).orientation;
        if (rot.x==q0.x && rot.y==q0.y && rot.z==q0.z && rot.w==q0.w)
            paths0.push_back(elem);
        if (rot.x==q90.x && rot.y==q90.y && rot.z==q90.z && rot.w==q90.w)
            paths90.push_back(elem);
        if (rot.x==q180.x && rot.y==q180.y && rot.z==q180.z && rot.w==q180.w)
            paths180.push_back(elem);
        if (rot.x==q270.x && rot.y==q270.y && rot.z==q270.z && rot.w==q270.w)
            paths270.push_back(elem);
    }

    //Se ordenan los paths en función de su maxima y o x

    sortPathsByY(paths0);
    sortPathsByY(paths180);

    sortPathsByX(paths90);
    sortPathsByX(paths270);

    //Ordenadas las poses (?)(compute from nearest point)
                    //En principio de Y a y e X a x

    // Poses repetidas (de momento ignoramos)

    //Marcar las primeras poses de cada path para desactivar la herramienta?
    //Servicio en paralelo al de almacenamiento. setrepare.




    for (auto & elem: paths0)
    {
       if(elem.poses.front().position.y<elem.poses.back().position.y)
           prepared_path.push_back(inversePathOrder(elem));
       else

       prepared_path.push_back(elem);
    }



    geometry_msgs::Pose before_last_pose=prepared_path.back().poses.at(prepared_path.back().poses.size()-2);
    geometry_msgs::Pose last_pose=prepared_path.back().poses.back();

    if(paths180.size()!=0 && isInsideRectLimits(last_pose.position.x, last_pose.position.y, rl_rotation_zone))//Añadir comprobacion de si hay ptras poses
    {
        geometry_msgs::Pose pose_aux=last_pose;

        geometry_msgs::Point p=nearestPointInsideRectLimits(last_pose.position.x,last_pose.position.y,rl_rotation_zone);
        pose_aux.position=p;
        pose_aux.position.z=-1;//marcada

        prepared_path.back().poses.push_back(pose_aux);

    }



    for (auto & elem: paths180)
    {
//        auto iterator=elem.poses.begin();
//        for (auto & elem2: elem.poses)
//        {
//            if ((elem2.position.x==before_last_pose.position.x && elem2.position.y==before_last_pose.position.y) ||
//                (elem2.position.x==last_pose.position.x && elem2.position.y==last_pose.position.y))
//                elem.poses.erase(iterator);
//            iterator++;
//        }

        if(elem.poses.front().position.y<elem.poses.back().position.y)
            prepared_path.push_back(inversePathOrder(elem));
        else

        prepared_path.push_back(elem);
    }

    last_pose=prepared_path.back().poses.back();

    if(paths90.size()!=0 &&isInsideRectLimits(last_pose.position.x, last_pose.position.y, rl_rotation_zone))
    {
        geometry_msgs::Pose pose_aux=last_pose;

        geometry_msgs::Point p=nearestPointInsideRectLimits(last_pose.position.x,last_pose.position.y,rl_rotation_zone);
        pose_aux.position=p;
        pose_aux.position.z=-1;//marcada

        prepared_path.back().poses.push_back(pose_aux);

    }

    for (auto & elem: paths90)
    {
//        auto iterator=elem.poses.begin();
//        for (auto & elem2: elem.poses)
//        {
//            if ((elem2.position.x==before_last_pose.position.x && elem2.position.y==before_last_pose.position.y) ||
//                (elem2.position.x==last_pose.position.x && elem2.position.y==last_pose.position.y))
//                elem.poses.erase(iterator);
//            iterator++;
//        }

        if(elem.poses.front().position.x<elem.poses.back().position.x)
            prepared_path.push_back(inversePathOrder(elem));
        else
        prepared_path.push_back(elem);
    }

    last_pose=prepared_path.back().poses.back();

    if(paths270.size()!=0 && isInsideRectLimits(last_pose.position.x, last_pose.position.y, rl_rotation_zone))
    {
        geometry_msgs::Pose pose_aux=last_pose;

        geometry_msgs::Point p=nearestPointInsideRectLimits(last_pose.position.x,last_pose.position.y,rl_rotation_zone);
        pose_aux.position=p;
        pose_aux.position.z=-1;//marcada

        prepared_path.back().poses.push_back(pose_aux);

    }


    for (auto & elem: paths270)
    {
//        auto iterator=elem.poses.begin();
//        for (auto & elem2: elem.poses)
//        {
//            if ((elem2.position.x==before_last_pose.position.x && elem2.position.y==before_last_pose.position.y) ||
//                (elem2.position.x==last_pose.position.x && elem2.position.y==last_pose.position.y))
//                elem.poses.erase(iterator);
//            iterator++;
//        }

        if(elem.poses.front().position.x<elem.poses.back().position.x)
            prepared_path.push_back(inversePathOrder(elem));
        else
            prepared_path.push_back(elem);
    }


    return prepared_path;
}

geometry_msgs::PoseArray IROBOT_ir_Storage_Service_Class::inversePathOrder(geometry_msgs::PoseArray path)
{
    geometry_msgs::PoseArray return_path;

    for(int i=path.poses.size()-1; i>=0;i--)
        return_path.poses.push_back(path.poses.at(i));

    return_path.header=path.header;

    return return_path;
}



geometry_msgs::Polygon IROBOT_ir_Storage_Service_Class::rectlimits2rosPolygon(rectangle_limits limits)
{
    geometry_msgs::Polygon poly_return;

    geometry_msgs::Point32 p;
    p.z=0.0;
    p.x=limits.xmin;
    p.y=limits.ymin;
                    poly_return.points.push_back(p);
    p.x=limits.xmin;
    p.y=limits.ymax;
                    poly_return.points.push_back(p);
    p.x=limits.xmax;
    p.y=limits.ymax;
                    poly_return.points.push_back(p);
    p.x=limits.xmax;
    p.y=limits.ymin;
                    poly_return.points.push_back(p);

                    return poly_return;
}

void IROBOT_ir_Storage_Service_Class::adjustRectlimits2maxmin(rectangle_limits &rl, double xmin, double xmax, double ymin, double ymax)
{
    if (rl.xmin<xmin)rl.xmin=xmin;
    if (rl.xmax>xmax)rl.xmax=xmax;
    if (rl.ymax>ymax)rl.ymax=ymax;
    if (rl.ymin<ymin)rl.ymin=ymin;
}

bool IROBOT_ir_Storage_Service_Class::isInsideRectLimits(double x, double y, rectangle_limits rl)
{
    if(x>=rl.xmin && y>=rl.ymin && y<=rl.ymax && x<=rl.xmax)
      return true;

    return false;
}

geometry_msgs::Point IROBOT_ir_Storage_Service_Class::nearestPointInsideRectLimits(double x, double y, rectangle_limits rl)
{
    geometry_msgs::Point return_point;
                         return_point.x=x; return_point.y=y;
    if(x<rl.xmin)
        return_point.x=rl.xmin;
    if(x>rl.xmax)
        return_point.x=rl.xmax;

    if(y<rl.ymin)
        return_point.y=rl.ymin;
    if(y>rl.ymax)
        return_point.y=rl.ymax;


    return return_point;

}

void IROBOT_ir_Storage_Service_Class::updateVizMsgs()
{
        //TO-DO: PERMITIR LLAMADA A LA GFUNCIÓN MÁS DE UNA VEZ

    std::string reference_frame_string="origin_of_the_universe";//"summit_xl_a_base_link";//"chapa_orig"; ////Darlo en el constructor y guardarlo como atributo????
    std::string robot_frame_string="summit_xl_a_base_link";

    rectangle_limits rl;
    rl.xmax= longa_x;
    rl.xmin= 0.0;
    rl.ymin= 0.0;
    rl.ymax= longa_y;

//    Poligonos con las zonas

    geometry_msgs::PolygonStamped psz;

    psz.header.frame_id=reference_frame_string;

    for(auto &elem:working_Czones_vector)
    {
        psz.polygon=elem;
        vec_zonas_cam_vizmsg.push_back(psz);
    }

    for(auto &elem:working_Hzones_vector)
    {
        psz.polygon=elem;
        vec_zonas_herr_vizmsg.push_back(psz);
    }


///Footprints
//    //Poligono footprint de la herramienta
//    geometry_msgs::PolygonStamped herr_footprint_msg;
//    double med_sim=0.05;
//    geometry_msgs::Point32 p32;
//    p32.z=0;
//    p32.x=-med_sim; p32.y=-med_sim;
//    herr_footprint_msg.polygon.points.push_back(p32);
//    p32.x=-med_sim; p32.y=med_sim;
//    herr_footprint_msg.polygon.points.push_back(p32);
//    p32.x=+med_sim; p32.y=med_sim;
//    herr_footprint_msg.polygon.points.push_back(p32);
//    p32.x=+med_sim; p32.y=-med_sim;
//    herr_footprint_msg.polygon.points.push_back(p32);



//    herr_footprint_msg.header.frame_id="projected_coupled_tool";

//Poligono footprint del robot

    geometry_msgs::Point32 p32;
    p32.z=0;
    p32.x=-longr_x*0.5; p32.y=-longr_y*0.5;
    poly_footprint_vizmsg.polygon.points.push_back(p32);
    p32.x=-longr_x*0.5; p32.y=longr_y*0.5;
    poly_footprint_vizmsg.polygon.points.push_back(p32);
    p32.x=longr_x*0.5; p32.y=longr_y*0.5;
    poly_footprint_vizmsg.polygon.points.push_back(p32);
    p32.x=longr_x*0.5; p32.y=-longr_y*0.5;
    poly_footprint_vizmsg.polygon.points.push_back(p32);

    poly_footprint_vizmsg.header.frame_id=robot_frame_string;



    //    //Poligono footprint de la herramienta
    geometry_msgs::PolygonStamped herr_footprint_msg;
    double med_sim=0.05;

    p32.z=0;
    p32.x=-longh_x +trash_x; p32.y=-longh_y+trash_y;
    poly_Hfootprint_vizmsg.polygon.points.push_back(p32);
    p32.x=-longh_x + trash_x; p32.y=longh_y+trash_y;
    poly_Hfootprint_vizmsg.polygon.points.push_back(p32);
    p32.x=+longh_x + trash_x; p32.y=longh_y+trash_y;
    poly_Hfootprint_vizmsg.polygon.points.push_back(p32);
    p32.x=+longh_x + trash_x; p32.y=-longh_y + trash_y;
    poly_Hfootprint_vizmsg.polygon.points.push_back(p32);



    //    herr_footprint_msg.header.frame_id=robot_frame_string;//"projected_coupled_tool"; ///LOS VALORES DEL LAUNCH Y LOS QUE SE PASAN A FLEXBE DEBERIAN COINCIDIR


//    Poligono con la chapa
    geometry_msgs::Polygon poly_chapa=rectlimits2rosPolygon(rl);


    poly_chapa_vizmsg.polygon=poly_chapa;
    poly_chapa_vizmsg.header.frame_id=reference_frame_string;


//Poligono zona de rotacion

     poly_rotzone_vizmsg.polygon=rotation_zone;
     poly_rotzone_vizmsg.header.frame_id=reference_frame_string;


//    //Poligono de los defectos




    int i=0;
    for(auto & elem: defectos_vec)
    {
        jsk_recognition_msgs::PolygonArray aux_polyarray;

        aux_polyarray.header.frame_id=reference_frame_string;




        geometry_msgs::PolygonStamped polys;
                                      polys.polygon=elem.ros_poly;
                                      polys.header.frame_id=reference_frame_string;

        vec_poligonos_vizmsg.push_back(polys);

        int info_i=0;
        int zona_i=0;
        for(auto & elemz: elem.defecto_divpor_zonas)
        {
            ROS_INFO("-----Zona %f", zona_i);
            for(auto & elemt: elemz.trap_vec)
            {
                geometry_msgs::PolygonStamped traps;
                traps.polygon=elemt.ros_poly;
                traps.header.frame_id=reference_frame_string;

                vec_trapecios_vizmsg.push_back(traps);

                aux_polyarray.polygons.push_back(traps);
                aux_polyarray.labels.push_back(info_i);
                aux_polyarray.likelihood.push_back(1);


                ROS_INFO("Trapecio %f", zona_i);
                info_i++;
            }
            zona_i++;
        }
        i++;

        vec_trapeciosarray_vizmsg.push_back(aux_polyarray);

    }




    //Prueba con los markers


        for(int i=0; i<4; i++)
        {
            visualization_msgs::Marker vizmsg_aux=PoseVector2VizMarker(paths_Hzones_vector.at(i));
            vec_paths_zonasherr_vizmsg.at(i)=vizmsg_aux;
        }

//        for(int i=0; i<4; i++)
//        {
//            visualization_msgs::Marker vizmsg_aux=PoseVector2VizMarker(paths_Czones_vector.at(i));
//            vec_path_zonascam_vizmsg.at(i)=vizmsg_aux;
//        }


        for(int d=0; d<defectos_vec.size(); d++)
        {
            int t_abs=0;
            for(int z=0; z<defectos_vec.at(d).defecto_divpor_zonas.size(); z++)
            {
                for(int t=0; t<defectos_vec.at(d).defecto_divpor_zonas.at(z).trap_vec.size();t++)
                {
                    visualization_msgs::Marker vizmsg_aux=PoseVector2VizMarker(paths_defects_vector.at(d).at(t_abs));

                    vec_path_defects_vizmsg.push_back(vizmsg_aux);//De momento así. Dividir viz más adelante
                    t_abs++;
                }
            }

        }


    initializeVizPubs();

    publish_vizmsgs_bool=true;

}

void IROBOT_ir_Storage_Service_Class::initializeVizPubs()
{
    std::string topic_poligono_defecto="topic_poligono_defecto";
    std::string topic_poligono_trapecio="topic_defecto";
    std::string topic_poligono_trapecio2="_trapecio";
    std::string topic_poligono_trapecios="topic_trapecios_defecto";
    std::string topic_poligono_zonasC="topic_poligono_zonaC";
    std::string topic_poligono_zonasH="topic_poligono_zonaH";
    std::string topic_poligono_footprint="topic_poligono_footprint";




    //Publisher de la chaoa
    poly_chapa_pub = n.advertise<geometry_msgs::PolygonStamped>("topic_poligono_chapa", 1000);

    //Publisher de la zona de rotacion
    rot_zone_pub=n.advertise<geometry_msgs::PolygonStamped>("topic_rotation_zone",1000);

    footprint_pub=n.advertise<geometry_msgs::PolygonStamped>(topic_poligono_footprint,1000);

    footprintH_pub=n.advertise<geometry_msgs::PolygonStamped>("topic_poligono_Hfootprint",1000);

//    //Publishers de las zonas C

    for(int i=0; i<working_Czones_vector.size(); i++)
    {
        std::string i_string = std::to_string(i*90);
        vec_zonas_cam_pubs.push_back(n.advertise<geometry_msgs::PolygonStamped>(topic_poligono_zonasC+i_string, 1000));
    }
    ROS_INFO("Publishers de las zonas C actualizado!");

//    //Publishers de las zonas H

    for(int i=0; i<working_Hzones_vector.size(); i++)
    {
        std::string i_string = std::to_string(i*90);
        vec_zonas_herr_pubs.push_back(n.advertise<geometry_msgs::PolygonStamped>(topic_poligono_zonasH+i_string, 1000));
    }
    ROS_INFO("Publishers de las zonas H actualizado!");



    for(int i=0; i<poly_vector.size(); i++)
    {
        std::string i_string = std::to_string(i);
        vec_poligonos_pubs.push_back(n.advertise<geometry_msgs::PolygonStamped>(topic_poligono_defecto+i_string, 1000));

        vec_trapeciosarrays_pubs.push_back(n.advertise<jsk_recognition_msgs::PolygonArray>(topic_poligono_trapecios+i_string, 100));

        //Publishers de los trapecios
        for(int z=0; z<defectos_vec.at(i).defecto_divpor_zonas.size(); z++)
        {
            std::string z_string = std::to_string(z*90);

            for(int j=0; j<defectos_vec.at(i).defecto_divpor_zonas.at(z).trap_vec.size(); j++)
             {
                std::string j_string = std::to_string(j);
                vec_trapecios_pubs.push_back(n.advertise<geometry_msgs::PolygonStamped>(topic_poligono_trapecio+i_string+topic_poligono_trapecio2+j_string+"zona"+z_string, 1000));
             }
        }

    }
    ROS_INFO("Publishers de los defectos listo!");


    //Paths working zones
    int i_string_zone_topic=0;
    for(auto & elem: vec_paths_zonasherr_vizmsg)
    {
        vec_path_zonas_herr_pubs.push_back(n.advertise<visualization_msgs::Marker>("topic_pathherr_zone"+std::to_string(i_string_zone_topic*90), 1000));
        i_string_zone_topic++;
    }

//    i_string_zone_topic=0;
//    for(auto & elem: vec_path_zonascam_vizmsg)
//    {
//        vec_path_zonas_cam_pubs.push_back(n.advertise<visualization_msgs::Marker>("topic_pathcam_zone"+std::to_string(i_string_zone_topic*90), 1000));
//        i_string_zone_topic++;
//    }

    //Paths defectos

//    int i_string_defectpath_topic=0;
//    for(auto & elem: vec_path_defects_vizmsg)
//    {
//        vec_path_defects_pubs.push_back(n.advertise<visualization_msgs::Marker>("topic_path_defect"+std::to_string(i_string_defectpath_topic), 1000));
//        i_string_defectpath_topic++;
//    }

    for(int d=0; d<defectos_vec.size(); d++)
    {
        for(int z=0; z<defectos_vec.at(d).defecto_divpor_zonas.size(); z++)
        {
            for(int t=0; t<defectos_vec.at(d).defecto_divpor_zonas.at(z).trap_vec.size();t++)
            {
                vec_path_defects_pubs.push_back(n.advertise<visualization_msgs::Marker>("topic_path_defect"+std::to_string(d)+"zona"+std::to_string(z*90)+"trap"+std::to_string(t), 1000));
            }
        }
    }

    ordered_msgpath_pub=n.advertise<geometry_msgs::PoseArray> ("topic_msg_ordered_path", 1000);
    ordered_path_pub=n.advertise<visualization_msgs::Marker>("topic_ordered_path", 1000);
    ordered_toolpath_pub=n.advertise<visualization_msgs::Marker>("topic_ordered_toolpath", 1000);

}

visualization_msgs::Marker IROBOT_ir_Storage_Service_Class::PoseVector2VizMarker(geometry_msgs::PoseArray path)
{
    visualization_msgs::Marker vizmarker;

    vizmarker.header.frame_id=reference_frame_string;
    vizmarker.action=visualization_msgs::Marker::ADD;



    vizmarker.id=0;
    vizmarker.type=visualization_msgs::Marker::LINE_STRIP;

    vizmarker.scale.x=0.01;
    vizmarker.color.g=1.0f;
    vizmarker.color.a=1.0;



    vizmarker.pose.position.x = 0;
    vizmarker.pose.position.y = 0;
    vizmarker.pose.position.z = 0;
    vizmarker.pose.orientation.x = 0.0;
    vizmarker.pose.orientation.y = 0.0;
    vizmarker.pose.orientation.z = 0.0;
    vizmarker.pose.orientation.w = 1.0;


       for(auto & elem: path.poses)
        {
                geometry_msgs::Point p_aux;
                p_aux.z=elem.position.z;
                p_aux.y=elem.position.y;
                p_aux.x=elem.position.x;
                vizmarker.points.push_back(p_aux);
         }

       return vizmarker;


}

