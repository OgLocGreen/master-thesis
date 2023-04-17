#include <ros/ros.h>
#include <inspection_realsense/moveForwardAction.h>
#include <inspection_realsense/Twist_inspection.h>

#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_ros/point_cloud.h>
#include <pcl_ros/transforms.h>

#include <cv_bridge/cv_bridge.h>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <pcl_ros/point_cloud.h>

#include <pcl/point_types.h>
#include <pcl/ModelCoefficients.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/filters/passthrough.h>
#include <pcl/filters/filter_indices.h>
#include <pcl/range_image/range_image_planar.h>
#include <pcl/common/transforms.h>
#include <pcl/search/kdtree.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_types_conversion.h>
#include <pcl/io/pcd_io.h>
#include <pcl/search/search.h>
#include <pcl/search/kdtree.h>
#include <pcl/features/normal_3d.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/filters/passthrough.h>
#include <pcl/segmentation/region_growing.h>
#include <pcl/segmentation/region_growing_rgb.h>

#include <actionlib/server/simple_action_server.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <signal.h>

#include <tf/transform_listener.h>

using namespace std;
using namespace cv;


class moveForwardAction
{
protected:
    int n_img = 0;
    bool new_goal = true;
    float long_sheet=3.76, width_sheet=2.51;
    float long_robot=0.71, width_robot=0.58;

    ros::NodeHandle nh_;
    ros::NodeHandle nh;
    actionlib::SimpleActionServer<inspection_realsense::moveForwardAction> as_; // NodeHandle instance must be created before this line. Otherwise strange error occurs.
    std::string action_name_;

    // create messages that are used to published feedback/result
    inspection_realsense::moveForwardFeedback feedback_;
    inspection_realsense::moveForwardResult result_;

    //Variables
    geometry_msgs::Twist vel_msg;
    float vel_goal_=100;
    int n_pasadas_ant=-1;
    int n_imgs_ant=-1;


    float pos_line=0;
    bool find_lineaIni=false, find_lineaFin=false, moveIzq=false, find_posIni = false, find_posFin = false, find_orientFin = false;
    int n_frames_sin_linea=0;
    Point pt1_b_ant, pt2_b_ant;
    Point pt1_vertical_ant, pt2_vertical_ant;


    ros::Publisher *pub, *pub_vel;
    message_filters::Subscriber<sensor_msgs::PointCloud2> sub_pc;

    bool isEnd=false;
    bool isLateralBorder = false;

    bool findSheetPlane(pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_msg, pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_ground, Mat &img_output)
    {
         // Segmentación
        pcl::ModelCoefficients::Ptr coefficients (new pcl::ModelCoefficients); //Coeficientes del plano: Ax + By + Cz + D = 0
        pcl::PointIndices::Ptr inliers_ground (new pcl::PointIndices);
        // Create the segmentation object

        pcl::SACSegmentation<pcl::PointXYZRGB> seg;
        // Optional
        seg.setOptimizeCoefficients (true);
        // Mandatory
        seg.setModelType (pcl::SACMODEL_PERPENDICULAR_PLANE);
        seg.setMethodType (pcl::SAC_RANSAC);
        seg.setDistanceThreshold (0.02);//0.01->1cm //Ajustar
        seg.setAxis(Eigen::Vector3f (0.0, 0.0, 1.0));
        seg.setEpsAngle (90.0*CV_PI/180.0);
        seg.setMaxIterations (500); //adaptar

        seg.setInputCloud (cloud_msg);
        seg.segment (*inliers_ground, *coefficients);

        if (inliers_ground->indices.size () == 0)
        {
          ROS_ERROR ("Could not estimate a planar model for the given dataset.");
          return false;
        }

        //Filtrar por coefficientes: Tiene que ser parecido a 0,-1,0,0.5

        if (round(coefficients->values[1]) != -1)
        {
            ROS_ERROR("Ground plane not found.");
            return false;
        }


        // Create the filtering object
        pcl::ExtractIndices<pcl::PointXYZRGB> extract;
        extract.setInputCloud (cloud_msg);
        extract.setIndices (inliers_ground); // --> Utilizar esto para quedarme con la parte de la imagen que quiero ¿?
        extract.setNegative(false);
        extract.filter (*cloud_ground);//get the ground plane


        img_output = Mat::zeros(cloud_msg->height, cloud_msg->width, CV_8UC3);
        for (int i=0; i<inliers_ground->indices.size();i++)
        {

            int fila =  inliers_ground->indices[i]/cloud_msg->width;
            int columna = inliers_ground->indices[i]%cloud_msg->width;

            pcl::PointXYZRGB point = cloud_msg->at(columna,fila);
            Eigen::Vector3i rgb = point.getRGBVector3i();

            img_output.at<cv::Vec3b>(fila, columna)[0] = rgb[2];
            img_output.at<cv::Vec3b>(fila, columna)[1] = rgb[1];
            img_output.at<cv::Vec3b>(fila, columna)[2] = rgb[0];

        }

      //  auto t_end = std::chrono::high_resolution_clock::now();
      //  PCL_ERROR("filtering: %f \n",(t_end-t_start).count()*1E-9);
        return true;
    }

    void detectSheet(Mat src, Mat &dst, Mat &frame_threshold, bool recort = true)
    {

      // Get only the interest region (Sheet borders by colour)
      Mat frame_HSV/*, frame_threshold*/;
      // Convert from BGR to HSV colorspace
      cvtColor(src, frame_HSV, COLOR_BGR2HSV);
      /// Detect the object based on HSV Range Values
      inRange(frame_HSV, Scalar(100, 40, 40), Scalar(110, 200, 200), frame_threshold);

   //   namedWindow( "th", CV_WINDOW_NORMAL );// Create a window for display.
   //   imshow("th", frame_threshold);

      // Find contours
      vector< vector<Point> > contours;
      findContours(frame_threshold, contours, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
      vector<vector<Point> > contours_poly( contours.size() );
      vector<Rect> boundRect( contours.size() );
      for( int i = 0; i < contours.size(); i++ )
      {
        approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
        boundRect[i] = boundingRect( Mat(contours_poly[i]));
      }
      Rect boundRect_max;
      float area_max = 0;
      for( int i = 0; i < boundRect.size(); i++)
      {
        if (boundRect[i].area() > area_max)
        {
          area_max = boundRect[i].area();
          boundRect_max = boundRect[i];
        }
      }

      if (recort == true)
        dst = src(boundRect_max).clone();

      else
      {
        dst = src.clone();

        for (int h=0; h<src.rows; h++)
        {
         for (int w=0; w<src.cols; w++)
         {
           if ((w > boundRect_max.tl().x && w < boundRect_max.br().x) &&
               (h > boundRect_max.tl().y && h < boundRect_max.br().y))
               continue;

           else
             dst.at<Vec3b>(h,w) = Vec3b(0,0,0);

         }
        }
      }

    }

    void detectSheet_mejorada(Mat src, Mat &dst, Mat &frame_threshold, bool recort = true)
    {

      // Get only the interest region (Sheet borders by colour)
      Mat frame_HSV/*, frame_threshold*/;
      // Convert from BGR to HSV colorspace
      cvtColor(src, frame_HSV, COLOR_BGR2HSV);
      /// Detect the object based on HSV Range Values
      inRange(frame_HSV, Scalar(0, 67, 0), Scalar(143, 255, 161), frame_threshold);

    //  namedWindow( "th", CV_WINDOW_NORMAL );// Create a window for display.
    //  imshow("th", frame_threshold);

      // Find contours
      vector< vector<Point> > contours;
      findContours(frame_threshold, contours, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
      vector<vector<Point> > contours_poly( contours.size() );
      vector<Rect> boundRect( contours.size() );
      for( int i = 0; i < contours.size(); i++ )
      {
        approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
        boundRect[i] = boundingRect( Mat(contours_poly[i]));
      }
      Rect boundRect_max;
      float area_max = 0;
      for( int i = 0; i < boundRect.size(); i++)
      {
        if (boundRect[i].area() > area_max)
        {
          area_max = boundRect[i].area();
          boundRect_max = boundRect[i];
        }
      }

      if (recort == true)
        dst = src(boundRect_max).clone();

      else
      {
        dst = src.clone();

        for (int h=0; h<src.rows; h++)
        {
         for (int w=0; w<src.cols; w++)
         {
           if ((w > boundRect_max.tl().x && w < boundRect_max.br().x) &&
               (h > boundRect_max.tl().y && h < boundRect_max.br().y))
               continue;

           else
             dst.at<Vec3b>(h,w) = Vec3b(0,0,0);

         }
        }
      }

    }

    void callback(const sensor_msgs::PointCloud2::ConstPtr &msg_points)
    {

        //geometry_msgs::Twist vel_msg;
        inspection_realsense::Twist_inspection vel_msg;
        vel_msg.distance_left = 100;

        float vel = vel_goal_;
        if(vel_goal_==100 || n_pasadas_ant == -1)
            return;


        //if (isLateralBorder) --> Seguirlo con bastante confianza --> reorientarse lentamente si no está bien
        //if (isLineaIni)-->Seguir con bastante confianza
        //if (nada)-->usar lozalización (summit_xl_odom)

        if (new_goal)
        {
            find_lineaIni=false;
            find_lineaFin=false;
            moveIzq=false;
            find_posIni = false;
            isEnd = false;
            n_frames_sin_linea=0;
            pt1_b_ant = Point(0,0);
            pt2_b_ant = Point(0,0);
            pt1_vertical_ant = Point(0,0);
            pt2_vertical_ant = Point(0,0);



            new_goal = false;
        }

        if (isEnd)
        {
            return;
        }


        if (find_orientFin)
        {

            //Comprobar según localización que estoy cerca del final y no en medio de la chapa, si es consistente perfecto
            //Utilizar la línea vertical para algo¿?

            vel_msg.linear.x = 0;
            vel_msg.linear.y = 0;
            vel_msg.angular.z = 0;

            pub_vel->publish(vel_msg);
            result_.finished=true;
            result_.n_pasadas_act = n_pasadas_ant+1;
            result_.n_imgs_act = n_img;

            if (!isEnd)
            {
                ROS_INFO("Posicion final encontrada");
                as_.setSucceeded(result_);
            }
            isEnd=true;

           // ros::shutdown();
            return;
        }


        // Comprobar que no me salga de la chapa también con la posición


        //---------------------------------------------------------------------------------
          // Convert to pcl point cloud
          pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_msg (new pcl::PointCloud<pcl::PointXYZRGB>);
          pcl::fromROSMsg(*msg_points,*cloud_msg);


          pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_ground (new pcl::PointCloud<pcl::PointXYZRGB>);

          Mat img_ground, img_sheet, img_th;
          bool getPlane = findSheetPlane(cloud_msg, cloud_ground, img_ground);
          //---------------------------------------------------------------------------------


          //------------------------------------------
          //--------Probar imagen con homografía------

          float data[9]={6.016344012082745, 30.14062607399775, -1696.231661764519,
                         0.08856350362927527, 43.77080730172647, -5128.439446737068,
                         3.620748308637643e-05, 0.01095165953183649, 1};

          Mat H(3,3,CV_32FC1,data);
          Mat img_homography, img_groung_aux;
          resize(img_ground,img_groung_aux,Size(1500,1000));
          warpPerspective(img_groung_aux,img_homography,H,Size(6000, 4000));
          resize(img_homography, img_homography, Size(1500,1000));
          stringstream name;
          n_img = n_imgs_ant;
          name << "/home/irobot/imgs_panorama/" << n_img <<".tiff";
        //  imwrite(name.str(), img_homography);
          n_img++;
//          namedWindow("homography__", CV_WINDOW_NORMAL );// Create a window for display.
//          imshow("homography__",img_homography); //<-- Utilizar para seguir línea vertical

          //------------------------------------------
          //------------------------------------------


          if(getPlane)
          {

              //---------------------------REORIENTARSE CON LÍNEA VERTICAL----------------------------------------
              //--------------------------------------------------------------------------------------------------
              Mat img_sheet_h, img_th_h;
              detectSheet_mejorada(img_homography,img_sheet_h,img_th_h,false); //

              Mat img_gray_h, img_bw_h;
              cv::cvtColor(img_homography, img_gray_h,CV_RGB2GRAY);
              cv::threshold(img_gray_h, img_bw_h, 10.0, 255.0, THRESH_BINARY); //Ajustar el threshold

              img_bw_h = img_bw_h - img_th_h;


              // Apertura: Erosion+Dilatacion. Eliminar puntos externos a la chapa

              int opening_size_h = 18;
              Mat opening_elem_h = cv::getStructuringElement(cv::MORPH_RECT,
                                                   cv::Size(2 * opening_size_h + 1, 2 * opening_size_h + 1),
                                                   cv::Point(opening_size_h, opening_size_h) );

             // erode(img_bw_h, img_bw_h, opening_elem_h);
             // dilate(img_bw_h, img_bw_h, opening_elem_h);

              // Cierre: Dilatacion+Erosión. Cerrar puntos abiertos en la chapa
              int closing_size_h = 6;
              Mat closing_elem_h = cv::getStructuringElement(cv::MORPH_RECT,
                                                   cv::Size(2 * closing_size_h + 1, 2 * closing_size_h + 1),
                                                   cv::Point(closing_size_h, closing_size_h) );

              dilate(img_bw_h, img_bw_h, closing_size_h);
              erode(img_bw_h, img_bw_h, closing_size_h);



              //Buscar línea vertical
              Mat cdst_h, cdstP_h;
              Canny(img_bw_h, img_bw_h, 50, 200, 3);
              cvtColor(img_bw_h, cdst_h, COLOR_GRAY2BGR);
              cdstP_h = cdst_h.clone();
              std::vector<Vec2f> lines_h; // will hold the results of the detection
              HoughLines(img_bw_h, lines_h, 3, 2*CV_PI/180, 150, 0, 0 ); //Ajustar el threshold

              // Encontrar la línea correcta
              std::vector<Vec2f> vertical_lines;
              std::vector<double> angles;

              isLateralBorder = false;
              for( size_t i = 0; i < lines_h.size(); i++ )
              {
                  float rho = lines_h[i][0], theta = lines_h[i][1];
                  Point pt1, pt2;
                  double a = cos(theta), b = sin(theta);
                  double x0 = a*rho, y0 = b*rho;
                  pt1.x = cvRound(x0 + 1000*(-b));
                  pt1.y = cvRound(y0 + 1000*(a));
                  pt2.x = cvRound(x0 - 1000*(-b));
                  pt2.y = cvRound(y0 - 1000*(a));

             //     line(cdst_h, pt1, pt2, Scalar(0,255,255), 3, LINE_AA);

                  double angle_ = atan2(pt2.y - pt1.y, pt2.x - pt1.x) * 180.0 / CV_PI;
                  if (fabs(angle_) <= 100 && fabs(angle_) >= 80)
                  {
                      isLateralBorder = true;
                      vertical_lines.push_back(lines_h[i]);
                      angles.push_back(angle_);
                      //line(cdst_h, pt1, pt2, Scalar(0,0,255), 3, LINE_AA);


                  }
                  else {
                      //isLateralBorder = false;
                  }
              }

              //Quedarme con la línea más vertical <--suponemos que es la mejor ¿?
              if(isLateralBorder)
              {
                  float min_dist=100;
                  int id_line=0;
                  for (int i=0; i<vertical_lines.size();i++)
                  {
                      if (abs(90-fabs(angles[i])) < min_dist)
                      {
                          min_dist = abs(90-fabs(angles[i]));
                          id_line=i;
                      }
                  }

                  float rho = vertical_lines[id_line][0], theta = vertical_lines[id_line][1];
                  Point pt1, pt2;
                  double a = cos(theta), b = sin(theta);
                  double x0 = a*rho, y0 = b*rho;
                  pt1.x = cvRound(x0 + 1000*(-b));
                  pt1.y = cvRound(y0 + 1000*(a));
                  pt2.x = cvRound(x0 - 1000*(-b));
                  pt2.y = cvRound(y0 - 1000*(a));
                 // line(cdst_h, pt1, pt2, Scalar(0,0,255), 3, LINE_AA);

                  //COMPROBAR QUE LA LÍNEA ES CONSISTENTE EN LA POSICIÓN X A LO LARGO DEL FRAME
                  bool isLateralBorder_correct = false;
                  if (pt1_vertical_ant.x != 0 && fabs(pt1.x-pt1_vertical_ant.x)<20) //CREO QUE DEBERÍA SER EN X
                      isLateralBorder_correct = true;


                  if (min_dist > 2 && min_dist != 100 && (isLateralBorder_correct || pt1_vertical_ant.x != 0) && !find_lineaIni)
                  {
                      line(cdst_h, pt1, pt2, Scalar(0,255,255), 3, LINE_AA);
                      //NECESITA REORIENTARSE
                      if (angles[id_line] > 0)
                          vel_msg.angular.z = 0.1;

                      else if (angles[id_line] <0 )
                          vel_msg.angular.z = -0.1;                                           

                  }
                  else
                  {
                      line(cdst_h, pt1, pt2, Scalar(0,0,255), 3, LINE_AA);
                      vel_msg.angular.z = 0;
                  }

                  pt1_vertical_ant = pt1;
                  pt2_vertical_ant = pt2;

              }

//             namedWindow( "HOMO_BW", CV_WINDOW_NORMAL );
//             imshow("HOMO_BW",cdst_h);

              //---------------------------------------------------------------------------------------------------------------
              //---------------------------------------------------------------------------------------------------------------

              detectSheet(img_ground,img_sheet,img_th,false);

           //   namedWindow( "ground", CV_WINDOW_NORMAL );// Create a window for display.
           //   imshow("ground", img_ground);

              Mat img_gray, img_bw;
              cv::cvtColor(img_ground, img_gray,CV_RGB2GRAY);
              cv::threshold(img_gray, img_bw, 10.0, 255.0, THRESH_BINARY); //Ajustar el threshold

              img_bw = img_bw - img_th;


              // Cierre: Dilatacion+Erosión. Cerrar puntos abiertos en la chapa
              int closing_size = 12;
              Mat closing_elem = cv::getStructuringElement(cv::MORPH_RECT,
                                                   cv::Size(2 * closing_size + 1, 2 * closing_size + 1),
                                                   cv::Point(closing_size, closing_size) );

              dilate(img_bw, img_bw, closing_elem);
              erode(img_bw, img_bw, closing_elem);

              // Apertura: Erosion+Dilatacion. Eliminar puntos externos a la chapa

              int opening_size = 6;
              Mat opening_elem = cv::getStructuringElement(cv::MORPH_RECT,
                                                   cv::Size(2 * opening_size + 1, 2 * opening_size + 1),
                                                   cv::Point(opening_size, opening_size) );

              erode(img_bw, img_bw, opening_elem);
              dilate(img_bw, img_bw, opening_elem);



              //Buscar líneas -- Movimiento de avance o retroceso
              Mat cdst, cdstP;
              Canny(img_bw, img_bw, 50, 200, 3);
              cvtColor(img_bw, cdst, COLOR_GRAY2BGR);
              cdstP = cdst.clone();
              std::vector<Vec2f> lines; // will hold the results of the detection
              HoughLines(img_bw, lines, 5, 5*CV_PI/180, 120, 0, 0 ); //Ajustar el threshold

              // Encontrar la línea correcta

              float y_max=0;
              Point pt1_b, pt2_b;

              for( size_t i = 0; i < lines.size(); i++ )
              {
                  float rho = lines[i][0], theta = lines[i][1];
                  Point pt1, pt2;
                  double a = cos(theta), b = sin(theta);
                  double x0 = a*rho, y0 = b*rho;
                  pt1.x = cvRound(x0 + 1000*(-b));
                  pt1.y = cvRound(y0 + 1000*(a));
                  pt2.x = cvRound(x0 - 1000*(-b));
                  pt2.y = cvRound(y0 - 1000*(a));

                  double angle_ = atan2(pt2.y - pt1.y, pt2.x - pt1.x) * 180.0 / CV_PI;

                  if(pt1.y>img_bw.rows/4 && pt1.y>y_max && angle_< 4 && angle_ > -4 )
                  {
                      find_lineaIni = true;
                      y_max=pt1.y;
                      pt1_b = pt1;
                      pt2_b = pt2;
                  }

              }
              double Angle = atan2(pt2_b.y - pt1_b.y, pt2_b.x - pt1_b.x) * 180.0 / CV_PI;

              if (pt1_b.y > pt1_b_ant.y-10 && Angle < 4 && Angle > -4 && !find_lineaFin)
              {
                line( cdst, pt1_b, pt2_b, Scalar(0,0,255), 3, LINE_AA);
                n_frames_sin_linea=0;
                pt1_b_ant = pt1_b;
                pt2_b_ant = pt2_b;
              }
              else if (find_lineaIni){
                  pt1_b = Point(0,0);
                  pt2_b = Point(0,0);

                  n_frames_sin_linea++;

                  if(n_frames_sin_linea > 5)
                  {
                      find_lineaFin = true;
                      n_frames_sin_linea=0;
                  }

              }

//              namedWindow( "lines", CV_WINDOW_NORMAL );// Create a window for display.
//              imshow("lines", cdst);

            //  namedWindow( "sheet", CV_WINDOW_NORMAL );// Create a window for display.
            //  imshow("sheet", img_bw);

          }

          else if (find_lineaIni){
              find_lineaFin = true;
              n_frames_sin_linea++;

              if(n_frames_sin_linea > 5)
              {
                  find_lineaFin = true;
                  n_frames_sin_linea=0;
              }
          }


          vel_msg.linear.x = vel;
          /*
          if (find_lineaFin)
          {
             // vel_msg.linear.x = 0;
             // vel_msg.linear.y = 0;
             // vel_msg.angular.z = 0;

              pub_vel->publish(vel_msg);

              sleep(1);
              //Reorientar, ¿Pero cómo, con localizacion?
          }
*/

  //-------

         // pub_vel->publish(vel_msg);

          //Comprobar en todo momento que no me salgo de la chapa

          bool prueba = false;
          tf::StampedTransform T_robot_world;
          tf::TransformListener listener;
          try{
                listener.waitForTransform("sheet_inspection_frame","summit_xl_base_link",
                                         ros::Time(0), ros::Duration(5));
                listener.lookupTransform("sheet_inspection_frame","summit_xl_base_link",
                                         ros::Time(0),T_robot_world);
              }
          catch (tf::TransformException ex){
            ROS_ERROR("%s",ex.what());
            ros::Duration(1.0).sleep();
            prueba = true;

          }


          if (!prueba)
              vel_msg.distance_left = long_sheet-3*long_robot/4-T_robot_world.getOrigin().x();


          if( !prueba &&
              ((T_robot_world.getOrigin().x() > long_sheet-3*long_robot/4 && vel_msg.linear.x > 0) ||
               (T_robot_world.getOrigin().x() < 3*long_robot/4 && vel_msg.linear.x < 0) ||
               (T_robot_world.getOrigin().y() > width_sheet-3*width_robot/4 && vel_msg.linear.y > 0) ||
               (T_robot_world.getOrigin().y() < 3*width_robot/4 && vel_msg.linear.y < 0) ||
               (find_posFin && !find_orientFin))  )
          {
              vel_msg.linear.x = 0;
              vel_msg.linear.y = 0;
              vel_msg.angular.z = 0;
              ROS_INFO("EL ROBOT SE VA A SALIR DE LA CHAPA");
              find_lineaFin = true;
              find_posFin = true;

              //REORIENTAR SEGÚN INSPECTION FRAME
              //T_robot_inspection_frame --> YAW = 0!!!
              double yaw = tf::getYaw(T_robot_world.getRotation());
              //Move angle yaw --> 0

              if (fabs(yaw) < 0.08)
              {
                  find_orientFin = true;
                  vel_msg.angular.z = 0;

              }
              else {

                  if (yaw < 0)
                      vel_msg.angular.z = 0.2;
                  else
                      vel_msg.angular.z = -0.2;

              }

              //return;
          }

          if (find_lineaFin && !find_posFin)
          {

              vel_msg.linear.x = vel;
              pub_vel->publish(vel_msg);
          }



          pub_vel->publish(vel_msg);

          waitKey(1);


    }


    public:

    moveForwardAction(std::string name) :
        as_(nh_, name, /*boost::bind(&moveForwardAction::executeCB, this, _1),*/ false),
        action_name_(name)
      {
        as_.registerGoalCallback(boost::bind(&moveForwardAction::goalCB, this));
        as_.registerPreemptCallback(boost::bind(&moveForwardAction::preemptCB, this));

        pub_vel = new ros::Publisher(nh.advertise<inspection_realsense::Twist_inspection>("/cmd_vel_robot", 1));


        sub_pc.subscribe(nh, "/summit_xl/front_realsense/depth_registered/points" ,1);
        sub_pc.registerCallback(boost::bind(&moveForwardAction::callback, this, _1));


        as_.start();

      }

    ~moveForwardAction(void)
    {
    }

    void goalCB()
      {
        // reset helper variables //LA VELOCIDADDDD
          // helper variables
          nh = nh;
          vel_msg.linear.x = vel_msg.linear.y = vel_msg.angular.z = 0;
          // accept the new goal
          auto goal_ = as_.acceptNewGoal();
          if (goal_ != NULL)
          {
              vel_goal_ = goal_->vel;
              n_pasadas_ant = goal_->n_pasadas_ant;
              n_imgs_ant = goal_->n_imgs_ant;

              find_lineaIni=false;
              find_lineaFin=false;
              find_posFin=false;
              find_orientFin=false;
              moveIzq=false;
              find_posIni = false;

              new_goal = true;
          }


      }

    void preemptCB()
    {
      ROS_INFO("%s: Preempted", action_name_.c_str());
      // set the action state to preempted
      as_.setPreempted();
    }

    void executeCB(const inspection_realsense::moveForwardGoalConstPtr &goal)
     {
         // make sure that the action hasn't been canceled
         if (!as_.isActive())
         {
           new_goal = true;
           return;
         }
        ros::Rate r(30);

     }

};


int main(int argc, char **argv)
{
    ros::init(argc, argv, "moveForward");
    ros::NodeHandle nh;

    moveForwardAction moveForward("moveForward");
    ROS_INFO("Move forward action server is ready!");

    ros::spin();
}
