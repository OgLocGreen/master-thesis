#include "fcppstorage_service_class.h"


FCPPStorage_Service_Class::FCPPStorage_Service_Class(double xm, double xM, double ym, double yM,
                                                     double hlat, double hproa, double hpopa, double robot_radius)
{
    xmin=xm; xmax=xM; ymin=ym; ymax=yM;

    herr_lat=hlat; herr_popa=hpopa; herr_proa=hproa;

    rot_radius=robot_radius;

    computeWorkingZones2();
    computeRotationZone();
}

FCPPStorage_Service_Class::FCPPStorage_Service_Class(double long_robotX, double long_robotY,
                                                     double long_chapaX, double long_chapaY,
                                                     double tras_herrx, double tras_herry,
                                                     double robot_radius)
{
    xmin=0.0; xmax=long_chapaX; ymin=0.0; ymax=long_chapaY;

    longx_r=long_robotX; longy_r=long_robotY;
    h_x=tras_herrx; h_y=tras_herry;

    rot_radius=robot_radius;

    computeWorkingZones2();
    computeRotationZone();
}



void FCPPStorage_Service_Class::addPolydefect(geometry_msgs::Polygon poly)
{
    poly_vector.push_back(poly);
}

geometry_msgs::Polygon FCPPStorage_Service_Class::getPolyDefectAt(int i)
{
    return poly_vector.at(i);
}

void FCPPStorage_Service_Class::loop()
{
    service = n.advertiseService("fcpp_data_service", &FCPPStorage_Service_Class::service_function, this);
    ROS_INFO("Servicio de almacenamiento de los datos de entrada para el FCPP---> LISTO");
    while (ros::ok()) { ros::spinOnce(); }
}

bool FCPPStorage_Service_Class::service_function(irobot_fcpp_simul::FCPP_in::Request &req,
                                                 irobot_fcpp_simul::FCPP_in::Response &res)
{



    res.n_defects=this->getNumberOfDefects();

    res.xmax_chapa=xmax; res.xmin_chapa=xmin;
    res.ymax_chapa=ymax; res.ymin_chapa=ymin;

    res.herr_lat=herr_lat; res.herr_popa=herr_popa; res.herr_proa=herr_proa;

    //Nuevas respuestas
    res.long_robotx=this->longx_r; res.long_roboty=this->longy_r;
    res.tras_herrx=this->h_x; res.tras_herry=this->h_y;

    if(req.id_input>res.n_defects || req.id_input<0)
        return true;

    res.poly_i=this->getPolyDefectAt(req.id_input);

    if(req.get_working_zones==true)
    {
        res.zone0=working_zones_vector.at(0);
        res.zone90=working_zones_vector.at(1);
        res.zone180=working_zones_vector.at(2);
        res.zone270=working_zones_vector.at(3);
//        res.zone4=working_zones_vector.at(4);
//        res.zone5=working_zones_vector.at(5);
//        res.zone6=working_zones_vector.at(6);
//        res.zone7=working_zones_vector.at(7);
//        res.zone8=working_zones_vector.at(8);
//        res.zone9=working_zones_vector.at(9);
    }

    if(req.get_rot_zone==true)
    {
        res.zone_rot=rotation_zone;
    }

    return true;

}

void FCPPStorage_Service_Class::computeWorkingZones()
{
        double complete_longx=xmax-xmin;
        double complete_longy=ymax-ymin;

        double min_herrp=std::min(herr_proa, herr_popa);
        double max_herrp=std::max(herr_proa, herr_popa);

        rectangle_limits zone1, zone2,
                         zone3_top, zone4_top,
                         zone5_bot, zone6_bot,
                         zone7_out, zone8_out, zone9_out, zone10_out;

        //Zonas numeradas del 1-10 en la funcion

        //Zona 1
        zone1.xmin= herr_lat;
        zone1.ymin=herr_popa;
        zone1.xmax=complete_longx;
        zone1.ymax=complete_longy-herr_proa;

        //Zona 2
        zone2.xmin=0.0;
        zone2.ymin=herr_proa;
        zone2.xmax=zone1.xmin;
        zone2.ymax=complete_longy-herr_popa;

        //Zona 7
        zone7_out.xmin=0.0;
        zone7_out.ymin=0.0;
        zone7_out.xmax=herr_popa;
        zone7_out.ymax=herr_proa;

        //Zona 8
        zone8_out.xmin=0.0;
        zone8_out.ymin=complete_longy-herr_popa;
        zone8_out.xmax=herr_proa;
        zone8_out.ymax=complete_longy;

        //Zona 9
        zone9_out.xmin=complete_longx-herr_popa;
        zone9_out.ymin=complete_longy-herr_proa;
        zone9_out.xmax=complete_longx;
        zone9_out.ymax=complete_longy;

        //Zona 10
        zone10_out.xmin=complete_longx-herr_proa;
        zone10_out.ymin=0.0;
        zone10_out.xmax=complete_longx;
        zone10_out.ymax=herr_popa;


        //Zona 3
        zone3_top.xmin=zone1.xmin;
        zone3_top.ymin=complete_longy-herr_proa;//zone2.ymax;
        zone3_top.xmax=zone9_out.xmin;////hdywqbyhe
        zone3_top.ymax=complete_longy;


        //Zona 4
        zone4_top.xmin=zone8_out.xmax;
        zone4_top.ymin=zone2.ymax;
        zone4_top.xmax=zone2.xmax;
        zone4_top.ymax=complete_longy;

        //Zona 5
        zone5_bot.xmin=zone1.xmin;
        zone5_bot.ymin=0;//min_herrp;
        zone5_bot.xmax=zone10_out.xmin;
        zone5_bot.ymax=herr_popa;//max_herrp;

        //Zona 6
        zone6_bot.xmin=herr_popa;
        zone6_bot.ymin=0.0;
        zone6_bot.xmax=zone2.xmax;//complete_longx-herr_proa;
        zone6_bot.ymax=zone2.ymin;//min_herrp;


        working_zones_vector.push_back(rectlimits2rosPolygon(zone1));     working_zones_vector.push_back(rectlimits2rosPolygon(zone2));
        working_zones_vector.push_back(rectlimits2rosPolygon(zone3_top)); working_zones_vector.push_back(rectlimits2rosPolygon(zone4_top));
        working_zones_vector.push_back(rectlimits2rosPolygon(zone5_bot)); working_zones_vector.push_back(rectlimits2rosPolygon(zone6_bot));
        working_zones_vector.push_back(rectlimits2rosPolygon(zone7_out)); working_zones_vector.push_back(rectlimits2rosPolygon(zone8_out));
        working_zones_vector.push_back(rectlimits2rosPolygon(zone9_out)); working_zones_vector.push_back(rectlimits2rosPolygon(zone10_out));
}

void FCPPStorage_Service_Class::computeWorkingZones2()
{
        ///Parametros chapa
        double hc=(xmax-xmin)*100*0.5; //*100 en esta funcion se trabaja en cm
        double lc=(ymax-ymin)*100*0.5;

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
        double offset_xd=h_x;//Leer del servicio
        double offset_yd=h_y;

        double l_sherpaxl=44*0.5; double h_sherpaxl=58*0.5;

        double lmax= (lc - offset_xd)*0.5;
        double hmax= (hc - offset_yd)*0.5;

        double lr=l_sherpaxl;
        double hr=h_sherpaxl;

        //Máscara robot
        cv::Mat img_r=Mat::ones(2*hr+1, 2*lr+1, CV_8UC1);


        ///Parametros herramienta
         double xd=lr+offset_xd;
         double yd=hr+offset_yd;

         //Máscara de la herr
         cv::Mat img_h=Mat::zeros(2*abs(yd)+1, 2*abs(xd)+1, CV_8UC1);
                 //img_h.at<uchar>(abs(yd)+1-yd, abs(xd)+1+xd)=1; //?
                 img_h.at<uchar>(1,1)=1;


// Zona navegable con ejes paralelos
         cv::Mat zona0 = computePossibleWorkingArea(img_int, img_r, img_h, rot0);
         cv::Mat mat_disp=img;

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
//                    if(f>xmax_aux) xmax_aux=f;
//                    if(f<xmin_aux) xmin_aux=f;
//                    if(c<ymin_aux) ymin_aux=c;
//                    if(c>ymax_aux) ymax_aux=c;
                 }
             }
         }
//         rectangle_limits z0_rl;
//         z0_rl.xmin=(xmin_aux-tras_origen)*.01; z0_rl.xmax=(xmax_aux-tras_origen)*.01;
//         z0_rl.ymin=(ymin_aux-tras_origen)*.01; z0_rl.ymax=(ymax_aux-tras_origen)*.01;

//         imshow("disp0", mat_disp);
//         cv::waitKey();

         // Zona navegable con giro 270
          xmax_aux=ymax_aux=0;
          xmin_aux=ymin_aux=10000000;
         cv::Mat zona270 = computePossibleWorkingArea(img_int, img_r, img_h, rot270);
         for(int f=0; f<mat_disp.rows; f++)
         {
             for(int c=0; c<mat_disp.cols; c++)
             {
                 if(zona270.at<uchar>(f,c)==1 && zona0.at<uchar>(f,c)==0 /*&& zona90.at<uchar>(f,c)==0 && zona180.at<uchar>(f,c)==0*/)
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


         // Zona navegable con giro 90
         cv::Mat zona90 = computePossibleWorkingArea(img_int, img_r, img_h, rot90);
         xmax_aux=ymax_aux=0;
         xmin_aux=ymin_aux=10000000;
         for(int f=0; f<mat_disp.rows; f++)
         {
             for(int c=0; c<mat_disp.cols; c++)
             {
                 if(zona90.at<uchar>(f,c)==1 && zona0.at<uchar>(f,c)==0 && zona270.at<uchar>(f,c)==0)
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

//         imshow("disp90", mat_disp);
//         cv::waitKey();

         // Zona navegable con giro 180
         xmax_aux=ymax_aux=0;
         xmin_aux=ymin_aux=10000000;
         cv::Mat zona180 = computePossibleWorkingArea(img_int, img_r, img_h, rot180);
         for(int f=0; f<mat_disp.rows; f++)
         {
             for(int c=0; c<mat_disp.cols; c++)
             {
                 if(zona180.at<uchar>(f,c)==1 && zona0.at<uchar>(f,c)==0 && zona90.at<uchar>(f,c)==0 && zona270.at<uchar>(f,c)==0)
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

//         imshow("disp180", mat_disp);
//          cv::waitKey();

//Se vuelve a calcular la zona 0
         xmax_aux=ymax_aux=0;
         xmin_aux=ymin_aux=10000000;

         for(int f=0; f<zona0.rows; f++)
         {
             for(int c=0; c<zona0.cols; c++)
             {
                 if(zona0.at<uchar>(f,c)==1 && !isInsideRectLimits((f-tras_origen)*.01,(c-tras_origen)*.01, z90_rl)
                                            && !isInsideRectLimits((f-tras_origen)*.01,(c-tras_origen)*.01, z180_rl)
                                            && !isInsideRectLimits((f-tras_origen)*.01,(c-tras_origen)*.01, z270_rl))
                 {
                     //mat_disp.at<Vec3b>(f,c)=c_zona0;
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

        //Zonas numeradas del 1-10 en la funcion

//    cv::imshow("imagen",mat_disp);
//    cv::waitKey();


    adjustRectlimits2maxmin(z0_rl,   this->xmin, this->xmax, this->ymin, this->ymax);
    adjustRectlimits2maxmin(z90_rl,  this->xmin, this->xmax, this->ymin, this->ymax);
    adjustRectlimits2maxmin(z180_rl, this->xmin, this->xmax, this->ymin, this->ymax);
    adjustRectlimits2maxmin(z270_rl, this->xmin, this->xmax, this->ymin, this->ymax);

    working_zones_vector.push_back(rectlimits2rosPolygon(z0_rl));     working_zones_vector.push_back(rectlimits2rosPolygon(z90_rl));
    working_zones_vector.push_back(rectlimits2rosPolygon(z180_rl));   working_zones_vector.push_back(rectlimits2rosPolygon(z270_rl));

}

cv::Mat FCPPStorage_Service_Class::computePossibleWorkingArea(cv::Mat img_areatotal, cv::Mat img_robot, cv::Mat img_herr, GradosRotacion rotation)
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

cv::Mat FCPPStorage_Service_Class::rotatek90Mat(cv::Mat img, GradosRotacion rotation)
{
    cv::Mat mat_return;
    switch (rotation)
    {
    case rot0:
        mat_return=img;
        break;
    case rot90:
        cv::rotate(img, mat_return, ROTATE_90_CLOCKWISE);
//        transpose(img, mat_return);
//        flip(mat_return, mat_return, +1);
        break;
    case rot180:
        cv::rotate(img, mat_return, ROTATE_180);
//        flip(img, mat_return, -1);
        break;
    case rot270:
        cv::rotate(img, mat_return, ROTATE_90_COUNTERCLOCKWISE);
//        transpose(img, mat_return);
//        flip(mat_return, mat_return, 0);
        break;
    }

    return mat_return;
}

void FCPPStorage_Service_Class::computeRotationZone()
{
    rectangle_limits zone;

    //Zonas numeradas del 1-10 en la funcion

    //Zona 1
    zone.xmin=xmin+rot_radius;
    zone.ymin=ymin+rot_radius;
    zone.xmax=xmax-rot_radius;
    zone.ymax=ymax-rot_radius;

    rotation_zone=rectlimits2rosPolygon(zone);
}

geometry_msgs::Polygon FCPPStorage_Service_Class::rectlimits2rosPolygon(rectangle_limits limits)
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

void FCPPStorage_Service_Class::adjustRectlimits2maxmin(rectangle_limits &rl, double xmin, double xmax, double ymin, double ymax)
{
    if (rl.xmin<xmin)rl.xmin=xmin;
    if (rl.xmax>xmax)rl.xmax=xmax;
    if (rl.ymax>ymax)rl.ymax=ymax;
    if (rl.ymin<ymin)rl.ymin=ymin;
}

bool FCPPStorage_Service_Class::isInsideRectLimits(double x, double y, rectangle_limits rl)
{
    if(x>=rl.xmin && y>=rl.ymin && y<=rl.ymax && x<=rl.xmax)
      return true;

    return false;
}

