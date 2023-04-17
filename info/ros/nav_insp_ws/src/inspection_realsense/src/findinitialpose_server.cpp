#include <ros/ros.h>
#include <inspection_realsense/findInitialPoseAction.h>

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

#include <tf2_ros/transform_broadcaster.h>

#include <tf2/transform_datatypes.h>
#include <tf2/transform_storage.h>
#include <tf2/LinearMath/Transform.h>

#include <geometry_msgs/PolygonStamped.h>


using namespace std;
using namespace cv;


class findInitialPoseAction
{
protected:
    ros::NodeHandle nh_;
    ros::NodeHandle nh;
    actionlib::SimpleActionServer<inspection_realsense::findInitialPoseAction> as_; // NodeHandle instance must be created before this line. Otherwise strange error occurs.
    std::string action_name_;

    // create messages that are used to published feedback/result
    inspection_realsense::findInitialPoseFeedback feedback_;
    inspection_realsense::findInitialPoseResult result_;

    //Variables

    tf2_ros::TransformBroadcaster br;
    geometry_msgs::TransformStamped T_sheet_world;
    tf2::Transform T_sheet_world_aux; //T_robot_world*T_sheet_robot
    tf::StampedTransform T_robot_world;
    tf2::Transform T_sheet_robot;
    geometry_msgs::PolygonStamped polygon_sheet;
    ros::Publisher polygon_pub = nh.advertise<geometry_msgs::PolygonStamped>("sheet_footprint", 1000);


    geometry_msgs::Twist vel_msg;
    float vel_goal_=100;
    float width_sheet_;
    float long_sheet_;
    float step_;
    float width_robot = 0;
    float long_robot = 0;

    bool findHorizontalLine_rear = false;
    bool isEnd = false;

    int n_frames_sin_linea_rear=0;
    int n_frames_con_linea_rear=0;
    int n_frames_con_linea_front=0;

    Point pt1_b_ant_rear;
    Point pt2_b_ant_rear;

    bool findLongPos = false, findWidthPos = false, isfindingWidthPos=false, isOriented=false, findLineForOrientation = false;

    ros::Publisher *pub, *pub_vel;
    message_filters::Subscriber<sensor_msgs::PointCloud2> sub_front;
    message_filters::Subscriber<sensor_msgs::PointCloud2> sub_rear;


    inline void convertTransformTFinTF2(tf::Transform m_tf, tf2::Transform &m_tf2)
    {
        tf::Matrix3x3 R_aux = m_tf.getBasis();
        tf::Vector3 t_aux = m_tf.getOrigin();
        double mat_data[12] = {R_aux[0][0], R_aux[0][1], R_aux[0][2], t_aux[0],
                               R_aux[1][0], R_aux[1][1], R_aux[1][2], t_aux[1],
                               R_aux[2][0], R_aux[2][1], R_aux[2][2], t_aux[2]};
        Mat src = Mat (3, 4, CV_64FC1, mat_data);

        tf2::Matrix3x3 R_aux2( src.at<double>(0,0), src.at<double>(0,1), src.at<double>(0,2),
                          src.at<double>(1,0), src.at<double>(1,1), src.at<double>(1,2),
                          src.at<double>(2,0), src.at<double>(2,1), src.at<double>(2,2));

        tf2::Vector3 t_aux2 (src.at<double>(0,3), src.at<double>(1,3), src.at<double>(2,3));

        m_tf2 = tf2::Transform(R_aux2, t_aux2);

    }

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

    //---quizá comentar esto
        // Create the filtering object
        pcl::ExtractIndices<pcl::PointXYZRGB> extract;
        extract.setInputCloud (cloud_msg);
        extract.setIndices (inliers_ground); // --> Utilizar esto para quedarme con la parte de la imagen que quiero ¿?
        extract.setNegative(false);
        extract.filter (*cloud_ground);//get the ground plane
    //-----

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
        //inRange(frame_HSV, Scalar(100, 40, 40), Scalar(110, 255, 255), frame_threshold); //AHORA MISMO DETECTA EL SUELO
        inRange(frame_HSV, Scalar(0, 67, 0), Scalar(143, 255, 161), frame_threshold);

     //   inRange(frame_HSV, Scalar(0, 0, 124), Scalar(31, 111, 255), frame_threshold);
    }


    void detectSheet_or(Mat src, Mat &dst, Mat &frame_threshold, bool recort = true)
    {
        // Get only the interest region (Sheet borders by colour)
        Mat frame_HSV/*, frame_threshold*/;
        // Convert from BGR to HSV colorspace
        cvtColor(src, frame_HSV, COLOR_BGR2HSV);
        /// Detect the object based on HSV Range Values
        //inRange(frame_HSV, Scalar(100, 40, 40), Scalar(110, 255, 255), frame_threshold); //AHORA MISMO DETECTA EL SUELO
        //inRange(frame_HSV, Scalar(0, 67, 0), Scalar(143, 255, 161), frame_threshold);

        inRange(frame_HSV, Scalar(0, 0, 124), Scalar(31, 111, 255), frame_threshold);
    }


    void mySigintHandler(int sig)
    {
      // Do some custom action.
      // For example, publish a stop message to some other nodes.

      // All the default sigint handler does is call shutdown()
      ros::shutdown();
    }

    void callback(const sensor_msgs::PointCloud2::ConstPtr &msg_points, int mode)
    {
        //---------------------------------------------------------------
        if (isEnd)
        {
            //Publicar tf sheet_inspection_frame a partir de la localización del robot.
            T_sheet_world.header.stamp = ros::Time::now();
            T_sheet_world.header.frame_id = "world";
            T_sheet_world.child_frame_id = "sheet_inspection_frame";
            T_sheet_world.transform.translation.x = T_sheet_world_aux.getOrigin().x();
            T_sheet_world.transform.translation.y = T_sheet_world_aux.getOrigin().y();
            T_sheet_world.transform.translation.z = T_sheet_world_aux.getOrigin().z(); //Estas zetas filtrarlas ¿?

            T_sheet_world.transform.rotation.x = T_sheet_world_aux.getRotation().normalized().x();
            T_sheet_world.transform.rotation.y = T_sheet_world_aux.getRotation().normalized().y();
            T_sheet_world.transform.rotation.z = T_sheet_world_aux.getRotation().normalized().z();
            T_sheet_world.transform.rotation.w = T_sheet_world_aux.getRotation().normalized().w();
            br.sendTransform(T_sheet_world);

            polygon_sheet.header.stamp = ros::Time::now();
            polygon_sheet.header.frame_id = "sheet_inspection_frame";

            polygon_pub.publish(polygon_sheet);
            return;
        }
        //---------------------------------------------------------------

        double vel_angular=0.15;
        double vel_linear_x=vel_goal_;
        double vel_linear_y=vel_goal_;

        if(vel_goal_==100)
            return;

        if (findLongPos && findWidthPos)
        {

            //vel_msg.linear.x = 0;
            //vel_msg.linear.y = 0;
            //pub_vel->publish(vel_msg);
            result_.finished=true;
            //Calcular el número de pasadas para inspeccionar
            int n_pasadas_totales = round((width_sheet_ - width_robot)/step_);
            result_.n_pasadas_totales = n_pasadas_totales;

            if (!isEnd)
            {
                ROS_INFO("Posicion inicial encontrada");

                as_.setSucceeded(result_);
            }
            isEnd=true;
            //ros::shutdown();

            //Aquí localizar robot--------------------------------------------
            // Transformación frame summit_xl_odom_estimated-world
            tf::TransformListener listener;
            try{
                  listener.waitForTransform("world","summit_xl_base_link",
                                           ros::Time(0), ros::Duration(5));
                  listener.lookupTransform("world","summit_xl_base_link",
                                           ros::Time(0),T_robot_world);
                }
            catch (tf::TransformException ex){
              ROS_ERROR("%s",ex.what());
              ros::Duration(1.0).sleep();
            }

            T_sheet_robot.setOrigin(tf2::Vector3(-long_robot/2,-width_robot/2,0));
            T_sheet_robot.setRotation(tf2::Quaternion(0,0,0,1));

           // tf2::Transform T_sheet_world_aux; //T_robot_world*T_sheet_robot

            tf2::Transform T_robot_world_aux;
            tf::Transform T_robot_world_aux2(T_robot_world.getBasis(), T_robot_world.getOrigin());
            convertTransformTFinTF2(T_robot_world_aux2, T_robot_world_aux);


            T_sheet_world_aux.mult(T_robot_world_aux,T_sheet_robot);


            //De aqui para abajo ponerlo en un sitio que solo lo haga una vez
            geometry_msgs::Point32 p1, p2, p3, p4;

            p1.x = 0;
            p1.y = 0;
            p1.z = 0;
            p2.x = long_sheet_;
            p2.y = 0;
            p2.z = 0;
            p3.x = long_sheet_;
            p3.y = width_sheet_;
            p3.z = 0;
            p4.x = 0;
            p4.y = width_sheet_;
            p4.z = 0;


            polygon_sheet.polygon.points.push_back(p1);
            polygon_sheet.polygon.points.push_back(p2);
            polygon_sheet.polygon.points.push_back(p3);
            polygon_sheet.polygon.points.push_back(p4);

            //---------------------------------------------------------------


            return;
        }

        string mode_str;
        bool findHorizontalLine = false;
        bool findVerticalLine = false;
        Point pt1_b_ant(0,0), pt2_b_ant(0,0);
        int n_frames_sin_linea=0;
        int n_frames_con_linea_oriented=0;

        int n_frames_con_linea=0;

        float data[9];

        if (mode == 0) //Front
        {
            mode_str = "Front";
            n_frames_con_linea = n_frames_con_linea_front;

            float data_[9]={6.016344012082745, 30.14062607399775, -1696.231661764519,
                           0.08856350362927527, 43.77080730172647, -5128.439446737068,
                           3.620748308637643e-05, 0.01095165953183649, 1};

            for (int j=0; j<9;j++)
                data[j]=data_[j];
        }


        else if (mode == 1) //Rear
        {
            vel_linear_x = -vel_linear_x;
            mode_str = "Rear";
            findHorizontalLine = findHorizontalLine_rear;
            pt1_b_ant = pt1_b_ant_rear;
            pt2_b_ant = pt2_b_ant_rear;
            n_frames_sin_linea = n_frames_sin_linea_rear;
            n_frames_con_linea_oriented = n_frames_con_linea_rear;

            float data_[9]={-5.98830655184492, -28.30136522174995, 6753.662812369213,
                           -0.9378879328787281, -42.07796162429873, 12085.59585714814,
                           -0.0002045815827764214, -0.01033300362604397, 1};
            for (int j=0; j<9;j++)
                data[j]=data_[j];

        }
        else //Error
        {
            ROS_ERROR("Error");
            return;
        }


        if (mode == 0 && (findHorizontalLine_rear && !isfindingWidthPos))
        {
            return;
        }
        if (mode == 0 && !isOriented)
        {
            return;
        }

        if (mode == 1 && isfindingWidthPos)
        {
            return;
        }

       // PCL_ERROR(mode_str.);
        //---------------------------------------------------------------------------------
          // Convert to pcl point cloud
          pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_msg (new pcl::PointCloud<pcl::PointXYZRGB>);
          pcl::fromROSMsg(*msg_points,*cloud_msg);

          pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_ground (new pcl::PointCloud<pcl::PointXYZRGB>);

          Mat img_ground, img_sheet, img_th;
          bool getPlane = findSheetPlane(cloud_msg, cloud_ground, img_ground);
          //---------------------------------------------------------------------------------
          if(!getPlane)
          {
              return;
          }

          //------------------------------------------
          //--------Probar imagen con homografía------


          Mat H(3,3,CV_32FC1,data);
          Mat img_homography,img_groung_aux;
          resize(img_ground,img_groung_aux,Size(1500,1000));
          warpPerspective(img_groung_aux,img_homography,H,Size(6000, 4000));
          resize(img_homography, img_homography, Size(1500,1000));
          namedWindow("homography", CV_WINDOW_NORMAL );// Create a window for display.
          imshow("homography",img_homography);

          //------------------------------------------
          //------------------------------------------


          stringstream name_ground;
          name_ground << "ground" << mode_str;
      //    namedWindow(name_ground.str(), CV_WINDOW_NORMAL );// Create a window for display.
      //    imshow(name_ground.str(), img_ground);

          detectSheet(img_ground,img_sheet,img_th,false);

          //-------------------
/*
          Mat img_gray2, img_bw2, img_sheet2,img_th2;
          detectSheet(img_homography,img_sheet2,img_th2,false);

          cv::cvtColor(img_homography, img_gray2,CV_RGB2GRAY);
          cv::threshold(img_gray2, img_bw2, 10.0, 255.0, THRESH_BINARY); //Ajustar el threshold

          img_bw2 = img_bw2 - img_th2;

          // Apertura: Erosion+Dilatacion. Eliminar puntos externos a la chapa

          int opening_size2 = 18;
          Mat opening_elem2 = cv::getStructuringElement(cv::MORPH_RECT,
                                                cv::Size(2 * opening_size2 + 1, 2 * opening_size2 + 1),
                                                cv::Point(opening_size2, opening_size2) );

          erode(img_bw2, img_bw2, opening_elem2);
          dilate(img_bw2, img_bw2, opening_elem2);


          // Cierre: Dilatacion+Erosión. Cerrar puntos abiertos en la chapa
          int closing_size2 = 6;
          Mat closing_elem2 = cv::getStructuringElement(cv::MORPH_RECT,
                                                cv::Size(2 * closing_size2 + 1, 2 * closing_size2 + 1),
                                                cv::Point(closing_size2, closing_size2) );

          dilate(img_bw2, img_bw2, closing_elem2);
          erode(img_bw2, img_bw2, closing_elem2);

          //Buscar líneas -- Movimiento de avance o retroceso
          Mat cdst2;
          Canny(img_bw2, img_bw2, 50, 200, 3);
          cvtColor(img_bw2, cdst2, COLOR_GRAY2BGR);
          std::vector<Vec2f> lines2; // will hold the results of the detection
          HoughLines(img_bw2, lines2, 5, 5*CV_PI/180, 120, 0, 0 ); //Ajustar el threshold

          for( size_t i = 0; i < lines2.size(); i++ )
          {
               float rho = lines2[i][0], theta = lines2[i][1];
               Point pt1, pt2;
               double a = cos(theta), b = sin(theta);
               double x0 = a*rho, y0 = b*rho;
               pt1.x = cvRound(x0 + 1000*(-b));
               pt1.y = cvRound(y0 + 1000*(a));
               pt2.x = cvRound(x0 - 1000*(-b));
               pt2.y = cvRound(y0 - 1000*(a));

               double angle_ = atan2(pt2.y - pt1.y, pt2.x - pt1.x) * 180.0 / CV_PI;

               if (angle_ > -3 && angle_ < 3)
                    line( cdst2, pt1, pt2, Scalar(0,0,255), 3, LINE_AA);

          }

          namedWindow("HOLA", CV_WINDOW_NORMAL );// Create a window for display.
          imshow("HOLA", cdst2);
*/

          //-------------------

          Mat img_gray, img_bw;
          cv::cvtColor(img_ground, img_gray,CV_RGB2GRAY);
          cv::threshold(img_gray, img_bw, 10.0, 255.0, THRESH_BINARY); //Ajustar el threshold

          namedWindow("ground", CV_WINDOW_NORMAL );// Create a window for display
          imshow("ground", img_ground);

          img_bw = img_bw - img_th;


          // Apertura: Erosion+Dilatacion. Eliminar puntos externos a la chapa

          int opening_size = 10;
          Mat opening_elem = cv::getStructuringElement(cv::MORPH_RECT,
                                                cv::Size(2 * opening_size + 1, 2 * opening_size + 1),
                                                cv::Point(opening_size, opening_size) );

          erode(img_bw, img_bw, opening_elem);
          dilate(img_bw, img_bw, opening_elem);


          // Cierre: Dilatacion+Erosión. Cerrar puntos abiertos en la chapa
          int closing_size = 6;
          Mat closing_elem = cv::getStructuringElement(cv::MORPH_RECT,
                                                cv::Size(2 * closing_size + 1, 2 * closing_size + 1),
                                                cv::Point(closing_size, closing_size) );

          dilate(img_bw, img_bw, closing_elem);
          erode(img_bw, img_bw, closing_elem);

          namedWindow("yey", CV_WINDOW_NORMAL );// Create a window for display
          imshow("yey", img_bw);

          //Buscar líneas -- Movimiento de avance o retroceso
          Mat cdst, cdstP;
          Canny(img_bw, img_bw, 50, 200, 3);
          cvtColor(img_bw, cdst, COLOR_GRAY2BGR);
          cdstP = cdst.clone();
          std::vector<Vec2f> lines; // will hold the results of the detection
          HoughLines(img_bw, lines, 5, 5*CV_PI/180, 120, 0, 0 ); //Ajustar el threshold

          //-----------------------------------------------------------------------------------------------
          // ORIENTAR ROBOT

          if (!isOriented)
          {

/*
              Mat img_sheet_h, img_th_h;
              detectSheet(img_homography,img_sheet_h,img_th_h,false); //

              Mat img_gray_h, img_bw_h;
              cv::cvtColor(img_homography, img_gray_h,CV_RGB2GRAY);
              cv::threshold(img_gray_h, img_bw_h, 10.0, 255.0, THRESH_BINARY); //Ajustar el threshold

              img_bw_h = img_bw_h - img_th_h;


              // Apertura: Erosion+Dilatacion. Eliminar puntos externos a la chapa

              int opening_size_h = 18;
              Mat opening_elem_h = cv::getStructuringElement(cv::MORPH_RECT,
                                                   cv::Size(2 * opening_size_h + 1, 2 * opening_size_h + 1),
                                                   cv::Point(opening_size_h, opening_size_h) );

              erode(img_bw_h, img_bw_h, opening_elem_h);
              dilate(img_bw_h, img_bw_h, opening_elem_h);

              // Cierre: Dilatacion+Erosión. Cerrar puntos abiertos en la chapa
              int closing_size_h = 6;
              Mat closing_elem_h = cv::getStructuringElement(cv::MORPH_RECT,
                                                   cv::Size(2 * closing_size_h + 1, 2 * closing_size_h + 1),
                                                   cv::Point(closing_size_h, closing_size_h) );

              dilate(img_bw_h, img_bw_h, closing_size_h);
              erode(img_bw_h, img_bw_h, closing_size_h);

              //Buscar línea horizontal
              Mat cdst_h, cdstP_h;
              Canny(img_bw_h, img_bw_h, 50, 200, 3);
              cvtColor(img_bw_h, cdst_h, COLOR_GRAY2BGR);
              vector<Vec4i> linesP; // will hold the results of the detection
              HoughLinesP(img_bw_h, linesP, 1, CV_PI/180, 50, 50, 30 ); // runs the actual detection
              // Draw the lines
              std::vector<double> angles;
              Vec4i max_l;
              double angle_max_line = 1000;
              double max_dist = -1.0;
              for( size_t i = 0; i < linesP.size(); i++ )
              {
                  Vec4i l = linesP[i];
                  float rho = linesP[i][0], theta = linesP[i][1];
                  Point pt1 =  Point(l[0], l[1]);
                  Point pt2 =  Point(l[2], l[3]);

                  double angle = atan2(pt2.y - pt1.y, pt2.x - pt1.x) * 180.0 / CV_PI;
                  //angles.push_back(angle);

                  double theta1,theta2, hyp, result;

                  theta1 = (l[3]-l[1]);
                  theta2 = (l[2]-l[0]);
                  hyp = hypot(theta1,theta2);

                  if (max_dist < hyp) {
                      max_l = l;
                      max_dist = hyp;
                      angle_max_line = angle;
                      findLineForOrientation = true;
                  }

              }

              if (findLineForOrientation)
              {
                  line( cdst_h, Point(max_l[0], max_l[1]), Point(max_l[2], max_l[3]), Scalar(255,0,0), 3, CV_AA);
                  if (angle_max_line > 1 && angle_max_line < 45)
                      vel_msg.angular.z = -vel_angular;

                  else if (angle_max_line < -1 && angle_max_line > -45)
                      vel_msg.angular.z = vel_angular;

                  else if (angle_max_line < 1 && angle_max_line > -1)
                  {
                      vel_msg.angular.z = 0;
                      isOriented = true;
                  }

              }

              namedWindow( "linees", CV_WINDOW_NORMAL );// Create a window for display.
              imshow("linees", cdst_h);
*/


              vector<Vec4i> linesP; // will hold the results of the detection
              HoughLinesP(img_bw, linesP, 1, CV_PI/180, 50, 50, 30 ); // runs the actual detection
              // Draw the lines
              std::vector<double> angles;
              Vec4i max_l;
              double angle_max_line = 1000;
              double max_dist = -1.0;
              for( size_t i = 0; i < linesP.size(); i++ )
              {
                  Vec4i l = linesP[i];
                  float rho = linesP[i][0], theta = linesP[i][1];
                  Point pt1 =  Point(l[0], l[1]);
                  Point pt2 =  Point(l[2], l[3]);

                  double angle = atan2(pt2.y - pt1.y, pt2.x - pt1.x) * 180.0 / CV_PI;
                  //angles.push_back(angle);

                  double theta1,theta2, hyp, result;

                  theta1 = (l[3]-l[1]);
                  theta2 = (l[2]-l[0]);
                  hyp = hypot(theta1,theta2);

                  if (max_dist < hyp) {
                      max_l = l;
                      max_dist = hyp;
                      angle_max_line = angle;
                      findLineForOrientation = true;
                  }

                  //line( cdst, pt1, pt2, Scalar(0,0,255), 3, LINE_AA);

                  //  for (int i=0;i<angles.size();i++)
                  //  {}
              }

              vel_msg.linear.x = 0;
              vel_msg.linear.y = 0;

              if (findLineForOrientation)
              {


                  line( cdst, Point(max_l[0], max_l[1]), Point(max_l[2], max_l[3]), Scalar(255,0,0), 3, CV_AA);
                  if (angle_max_line > 1 && angle_max_line < 45)
                      vel_msg.angular.z = -vel_angular;

                  else if (angle_max_line < -3 && angle_max_line > -45) //-1
                      vel_msg.angular.z = vel_angular;

                  else if (angle_max_line < 0.5 && angle_max_line > -3) //-0.5
                  {
                      vel_msg.angular.z = 0;
                      isOriented = true;
                  }

              }




              //De momento línea más larga. No se si depurar en otra ocasión
              // Una vez orientado
              //isOriented == true;

              stringstream name_lines;
              name_lines << "lineaORIENTAR" << mode_str;
              namedWindow( name_lines.str(), CV_WINDOW_NORMAL );// Create a window for display.
              imshow(name_lines.str(), cdst);

          }

          //-----------------------------------------------------------------------------------------------
          // BUSCAR FRONTAL CHAPA SI ROBOT ORIENTADO (SUPONEMOS QUE SIEMPRE VE CHAPA CON LA REALSENSE TRASERA¿?)

          if (!findLongPos && isOriented)
          {
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

                  if(pt1.y>y_max && angle_< 3 && angle_ > -3 )
                  {
                      findHorizontalLine = true;
                      y_max=pt1.y;
                      pt1_b = pt1;
                      pt2_b = pt2;
                  }

             }
             double Angle = atan2(pt2_b.y - pt1_b.y, pt2_b.x - pt1_b.x) * 180.0 / CV_PI;

             if (pt1_b.y > pt1_b_ant.y-10 && Angle < 3 && Angle > -3 && !findLongPos)
             {
                line( cdst, pt1_b, pt2_b, Scalar(0,255,255), 3, LINE_AA);
                n_frames_sin_linea=0;
                pt1_b_ant = pt1_b;
                pt2_b_ant = pt2_b;


                n_frames_con_linea_oriented++;
                if (n_frames_con_linea_oriented > 5)
                {
                    isOriented = false;
                    n_frames_con_linea_oriented = 0;
                }


              }


             else /*if (findHorizontalLine)*/{
                  pt1_b = Point(0,0);
                  pt2_b = Point(0,0);

                  n_frames_sin_linea++;
                  //n_frames_con_linea_oriented = 0;

                  if(n_frames_sin_linea > 5/* && pt1_b.y>(cdst.rows-40)*/) //15
                  {
                      findLongPos = true;
                      n_frames_sin_linea=0;
                  }



              }

              vel_msg.linear.x = vel_linear_x;

              stringstream name_lines;
              name_lines << "linea" << mode_str;
              namedWindow( name_lines.str(), CV_WINDOW_NORMAL );// Create a window for display.
              imshow(name_lines.str(), cdst);

          }



          //-----------------------------------------------------------------------------------------------
          // BUSCAR LATERAL CHAPA
          if (findLongPos && !isfindingWidthPos)
          {
              vel_msg.linear.x = 0;
              pub_vel->publish(vel_msg);
              sleep(1);

              isfindingWidthPos = true;
          }

          if (isfindingWidthPos)
          {

              vel_msg.linear.y = -0.1;

              //-------------------

              Mat img_gray2, img_bw2, img_sheet2,img_th2;
              detectSheet(img_homography,img_sheet2,img_th2,false);

              cv::cvtColor(img_homography, img_gray2,CV_RGB2GRAY);
              cv::threshold(img_gray2, img_bw2, 10.0, 255.0, THRESH_BINARY); //Ajustar el threshold

              img_bw2 = img_bw2 - img_th2;

              // Apertura: Erosion+Dilatacion. Eliminar puntos externos a la chapa

              int opening_size2 = 18;
              Mat opening_elem2 = cv::getStructuringElement(cv::MORPH_RECT,
                                                    cv::Size(2 * opening_size2 + 1, 2 * opening_size2 + 1),
                                                    cv::Point(opening_size2, opening_size2) );

              erode(img_bw2, img_bw2, opening_elem2);
              dilate(img_bw2, img_bw2, opening_elem2);


              // Cierre: Dilatacion+Erosión. Cerrar puntos abiertos en la chapa
              int closing_size2 = 6;
              Mat closing_elem2 = cv::getStructuringElement(cv::MORPH_RECT,
                                                    cv::Size(2 * closing_size2 + 1, 2 * closing_size2 + 1),
                                                    cv::Point(closing_size2, closing_size2) );

              dilate(img_bw2, img_bw2, closing_elem2);
              erode(img_bw2, img_bw2, closing_elem2);

              //Buscar líneas -- Movimiento de avance o retroceso
              Mat cdst2;
              Canny(img_bw2, img_bw2, 50, 200, 3);
              cvtColor(img_bw2, cdst2, COLOR_GRAY2BGR);
              std::vector<Vec2f> lines2; // will hold the results of the detection
              HoughLines(img_bw2, lines2, 5, 5*CV_PI/180, 120, 0, 0 ); //Ajustar el threshold
              Point pt1_b2, pt2_b2;

              for( size_t i = 0; i < lines2.size(); i++ )
              {
                   float rho = lines2[i][0], theta = lines2[i][1];
                   Point pt1, pt2;
                   double a = cos(theta), b = sin(theta);
                   double x0 = a*rho, y0 = b*rho;
                   pt1.x = cvRound(x0 + 1000*(-b));
                   pt1.y = cvRound(y0 + 1000*(a));
                   pt2.x = cvRound(x0 - 1000*(-b));
                   pt2.y = cvRound(y0 - 1000*(a));

                   double angle_ = atan2(pt2.y - pt1.y, pt2.x - pt1.x) * 180.0 / CV_PI;

                   if (fabs(angle_) > 85 && fabs(angle_) < 95)
                   {
                        line( cdst2, pt1, pt2, Scalar(0,0,255), 3, LINE_AA);
                        findVerticalLine = true;
                        pt1_b2 = pt1;
                        pt2_b2 = pt2;
                    }
              }

              double Angle = atan2(pt2_b2.y - pt1_b2.y, pt2_b2.x - pt1_b2.x) * 180.0 / CV_PI;

              vel_msg.angular.z = 0;

              if (fabs(Angle) > 80 && fabs(Angle) <100)
              {

                 line( cdst2, pt1_b2, pt2_b2, Scalar(255,0,255), 3, LINE_AA);
                 pt1_b_ant = pt1_b2;
                 pt2_b_ant = pt2_b2;

                 n_frames_con_linea++;

                 //Reorientar
                 if(fabs(Angle) < 88 || fabs(Angle) > 92)
                 {
                     if (Angle > 0)
                         vel_msg.angular.z = 0.1;

                     else if (Angle <0 )
                         vel_msg.angular.z = -0.1;

                     vel_msg.linear.y = 0;


                 }
                 else {
                     vel_msg.angular.z = 0;
                 }




                 if(fabs(Angle)>88 && fabs(Angle)<92 && (pt1_b2.x < 960 || pt2_b2.x < 960) && n_frames_con_linea > 1)
                 {

                     findWidthPos = true;
                     isfindingWidthPos = false;
                     n_frames_con_linea=0;
                     vel_msg.angular.z = 0;

                 }

               }

         //      else if (findVerticalLine){
         //           n_frames_con_linea=0;
         //      }

              namedWindow("HOLA", CV_WINDOW_NORMAL );// Create a window for display.
              imshow("HOLA", cdst2);


              //-------------------



/* esto es lo que teniaaaaaaaaaa

              //Buscar línea "vertical" y ajustar el pt1 según su altura
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

                   if((angle_> 25 && angle_ < 45) )
                   {
                       findVerticalLine = true;
                       pt1_b = pt1;
                       pt2_b = pt2;
                   }
              }

              double Angle = atan2(pt2_b.y - pt1_b.y, pt2_b.x - pt1_b.x) * 180.0 / CV_PI;

              if (Angle > 25 && Angle <45)
              {
                 line( cdst, pt1_b, pt2_b, Scalar(0,0,255), 3, LINE_AA);
                 pt1_b_ant = pt1_b;
                 pt2_b_ant = pt2_b;

                 n_frames_con_linea++;

                 if(n_frames_con_linea > 5)
                 {

                     findWidthPos = true;
                     isfindingWidthPos = false;
                     n_frames_con_linea=0;
                 }
               }

               else if (findVerticalLine){
                    n_frames_con_linea=0;
               }


               stringstream name_lines;
               name_lines << "linea" << mode_str;
               namedWindow( name_lines.str(), CV_WINDOW_NORMAL );// Create a window for display.
               imshow(name_lines.str(), cdst);
*/

/*
              //---------------------------BUSCAR LÍNEA VERTICAL----------------------------------------
              //--------------------------------------------------------------------------------------------------
              Mat img_sheet_h, img_th_h;
              detectSheet(img_homography,img_sheet_h,img_th_h,false); //

              Mat img_gray_h, img_bw_h;
              cv::cvtColor(img_homography, img_gray_h,CV_RGB2GRAY);
              cv::threshold(img_gray_h, img_bw_h, 10.0, 255.0, THRESH_BINARY); //Ajustar el threshold

              img_bw_h = img_bw_h - img_th_h;


              // Apertura: Erosion+Dilatacion. Eliminar puntos externos a la chapa

              int opening_size_h = 18;
              Mat opening_elem_h = cv::getStructuringElement(cv::MORPH_RECT,
                                                   cv::Size(2 * opening_size_h + 1, 2 * opening_size_h + 1),
                                                   cv::Point(opening_size_h, opening_size_h) );

              erode(img_bw_h, img_bw_h, opening_elem_h);
              dilate(img_bw_h, img_bw_h, opening_elem_h);

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
              HoughLines(img_bw_h, lines_h, 5, 2*CV_PI/180, 90, 0, 0 ); //Ajustar el threshold

              // Encontrar la línea correcta
              std::vector<Vec2f> vertical_lines;
              std::vector<double> angles;

              Point pt1_b, pt2_b;
              findVerticalLine = false;
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
                      findVerticalLine = true;
                      pt1_b = pt1;
                      pt2_b = pt2;
                  }

              }

              double Angle = atan2(pt2_b.y - pt1_b.y, pt2_b.x - pt1_b.x) * 180.0 / CV_PI;

              if (Angle > 80 && Angle <100)
              {
                 line( cdst_h, pt1_b, pt2_b, Scalar(0,0,255), 3, LINE_AA);
                 pt1_b_ant = pt1_b;
                 pt2_b_ant = pt2_b;

                 n_frames_con_linea++;

                 if(n_frames_con_linea > 2 && pt2_b.y<1050 && pt2_b.y>950)
                 {
                     findWidthPos = true;
                     isfindingWidthPos = false;
                     n_frames_con_linea=0;
                 }
               }

               else if (findVerticalLine){
                    n_frames_con_linea=0;
               }

              //----
              if (fabs(Angle) > 80 && fabs(Angle) < 100)
              {

                  if (Angle > 0)
                      vel_msg.angular.z = 0.1;

                  else if (Angle <0 )
                      vel_msg.angular.z = -0.1;
              }
              else
              {
                  vel_msg.angular.z = 0;
              }
             //-----

              stringstream name_lines;
              name_lines << "linea" << mode_str;
              namedWindow( name_lines.str(), CV_WINDOW_NORMAL );// Create a window for display.
              imshow(name_lines.str(), cdst_h);
*/
              //----------------------------------------------------------

              vel_msg.linear.x = 0;
             // vel_msg.linear.y = -0.1;
              pub_vel->publish(vel_msg);

          }


          pub_vel->publish(vel_msg);



          //-----------------------------------------------------------------------------------------------
          // Update data
          if (mode == 0) //Front
          {
              int a = 0;
              // findHorizontalLine = findHorizontalLine_front;
              n_frames_con_linea_front = n_frames_con_linea;

          }
          else if (mode == 1) //Rear
          {
              findHorizontalLine_rear = findHorizontalLine;
              pt1_b_ant_rear = pt1_b_ant;
              pt2_b_ant_rear = pt2_b_ant;
              n_frames_sin_linea_rear = n_frames_sin_linea;
              n_frames_con_linea_rear = n_frames_con_linea_oriented;

          }

          waitKey(1);
    }


    public:

    findInitialPoseAction(std::string name) :
        as_(nh_, name, /*boost::bind(&findInitialPoseAction::executeCB, this, _1),*/ false),
        action_name_(name)
      {
        as_.registerGoalCallback(boost::bind(&findInitialPoseAction::goalCB, this));
        as_.registerPreemptCallback(boost::bind(&findInitialPoseAction::preemptCB, this));

        pub_vel = new ros::Publisher(nh.advertise<geometry_msgs::Twist>("/summit_xl/cmd_vel", 30));

        int mode_front=0, mode_rear=1;

        sub_front.subscribe(nh, "/summit_xl/front_realsense/depth_registered/points" ,1);
        sub_front.registerCallback(boost::bind(&findInitialPoseAction::callback, this, _1, mode_front));

        sub_rear.subscribe(nh, "/summit_xl/rear_realsense/depth_registered/points" ,1);
        sub_rear.registerCallback(boost::bind(&findInitialPoseAction::callback, this, _1, mode_rear));

        as_.start();

      }

    ~findInitialPoseAction(void)
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
          vel_goal_ = goal_->vel;
          width_sheet_ = goal_->width_sheet;
          long_sheet_ = goal_->long_sheet;
          width_robot = goal_->width_robot;
          long_robot = goal_->long_robot;
          step_ = goal_->step;

      }

    void preemptCB()
    {
      ROS_INFO("%s: Preempted", action_name_.c_str());
      // set the action state to preempted
      as_.setPreempted();
    }

    void executeCB(const inspection_realsense::findInitialPoseGoalConstPtr &goal)
     {
         // make sure that the action hasn't been canceled
         if (!as_.isActive())
           return;

        ros::Rate r(30);

     }

};


int main(int argc, char **argv)
{
    ros::init(argc, argv, "FindInitialPose");
    ros::NodeHandle nh;

    findInitialPoseAction findInitialPose("FindInitialPose");
    ROS_INFO("Find initial pose action server is ready!");

    ros::spin();
}
