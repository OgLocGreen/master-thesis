#include <ros/ros.h>
#include <inspection_realsense/checkNewScanBackwardAction.h>
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

using namespace std;
using namespace cv;


class checkNewScanBackwardAction
{
protected:

    float long_sheet=3.76, width_sheet=2.51;
    float long_robot=0.71, width_robot=0.58;

    ros::NodeHandle nh_;
    ros::NodeHandle nh;
    actionlib::SimpleActionServer<inspection_realsense::checkNewScanBackwardAction> as_; // NodeHandle instance must be created before this line. Otherwise strange error occurs.
    std::string action_name_;

    // create messages that are used to published feedback/result
    inspection_realsense::checkNewScanBackwardFeedback feedback_;
    inspection_realsense::checkNewScanBackwardResult result_;

    //Variables
    inspection_realsense::Twist_inspection vel_msg;
    float vel_goal_=100;
    int mode_ = 100;

    Point pt1_vertical_ant, pt2_vertical_ant;
    bool isLateralBorder = false;
    bool isEnd=false;
    bool newScanIsNeeded = false;

    ros::Publisher *pub_vel;
    message_filters::Subscriber<sensor_msgs::PointCloud2> sub_pc;


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

        vel_msg.distance_left = 1000;

       //geometry_msgs::Twist vel_msg;
        float vel = vel_goal_;
        if(vel_goal_==100)
            return;

        if (isEnd)
        {
            vel_msg.linear.x = 0;
            vel_msg.linear.y = 0;
            vel_msg.angular.z  = 0;
            pub_vel->publish(vel_msg);
            result_.newScanIsNeeded = newScanIsNeeded;
            result_.finished=true;
            as_.setSucceeded(result_);

            ros::shutdown();
            return;
        }


        //---------------------------------------------------------------------------------
          // Convert to pcl point cloud
          pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_msg (new pcl::PointCloud<pcl::PointXYZRGB>);
          pcl::fromROSMsg(*msg_points,*cloud_msg);


          pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_ground (new pcl::PointCloud<pcl::PointXYZRGB>);

          Mat img_ground, img_sheet, img_th;
          bool getPlane = findSheetPlane(cloud_msg, cloud_ground, img_ground);


          //------------------------------------------
          //--------Probar imagen con homografía------

          float data[9];
          if (mode_ == 0)
          {

              float data_[9]={6.016344012082745, 30.14062607399775, -1696.231661764519,
                             0.08856350362927527, 43.77080730172647, -5128.439446737068,
                             3.620748308637643e-05, 0.01095165953183649, 1};

              for (int j=0; j<9;j++)
                  data[j]=data_[j];
          }
          else if (mode_ == 1)
          {
              float data_[9]={-5.98830655184492, -28.30136522174995, 6753.662812369213,
                             -0.9378879328787281, -42.07796162429873, 12085.59585714814,
                             -0.0002045815827764214, -0.01033300362604397, 1};
              for (int j=0; j<9;j++)
                  data[j]=data_[j];
          }

          Mat H(3,3,CV_32FC1,data);
          Mat img_homography, img_groung_aux;
          resize(img_ground,img_groung_aux,Size(1500,1000));
          warpPerspective(img_groung_aux,img_homography,H,Size(6000, 4000));
          resize(img_homography, img_homography, Size(1500,1000));
          namedWindow("homography", CV_WINDOW_NORMAL );// Create a window for display.
          imshow("homography",img_homography); //<-- Utilizar para seguir línea vertical

          //------------------------------------------
          //------------------------------------------


          if(getPlane)
          {
              //---------------------------BUSCAR LÍNEA VERTICAL----------------------------------------
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
                  line(cdst_h, pt1, pt2, Scalar(0,0,255), 3, LINE_AA);

                  if (min_dist > 2 && min_dist != 100)
                  {
                      //NECESITA REORIENTARSE
                      if (angles[id_line] > 0)
                          vel_msg.angular.z = 0.1;

                      else if (angles[id_line] <0 )
                          vel_msg.angular.z = -0.1;

                  }
                  else
                      vel_msg.angular.z = 0;

                  //Moverse hacia la izquierda hasta que pt1.x esté donde quiero

                 if ((fabs(pt1.x)>940 && fabs(pt1.x)<960 && mode_== 1) || (fabs(pt1.x)>350 && fabs(pt1.x)<400 && mode_== 0)) //AJUSTAR ESTO
                 {
                     isEnd = true;
                 }
                 else
                 {
                     vel_msg.linear.y = 0.1;
                   //  pub_vel->publish(vel_msg);
                     newScanIsNeeded = true;
                 }

                  pt1_vertical_ant = pt1;
                  pt2_vertical_ant = pt2;

              }

              else
              {
                  vel_msg.linear.y = 0.1;
                //  pub_vel->publish(vel_msg);
                 // newScanIsNeeded = true;
              }

             namedWindow( "lines", CV_WINDOW_NORMAL );// Create a window for display.
             imshow("lines",cdst_h);

          }




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

          if( !prueba &&
              ((T_robot_world.getOrigin().x() > long_sheet-3*long_robot/4 && vel_msg.linear.x > 0) ||
               (T_robot_world.getOrigin().x() < 3*long_robot/4 && vel_msg.linear.x < 0) ||
               (T_robot_world.getOrigin().y() > width_sheet-3*width_robot/4 && vel_msg.linear.y > 0) ||
               (T_robot_world.getOrigin().y() < 3*width_robot/4 && vel_msg.linear.y < 0)) )
          {
              vel_msg.linear.x = 0;
              vel_msg.linear.y = 0;
              vel_msg.angular.z = 0;
             // pub_vel->publish(vel_msg);
              ROS_INFO("EL ROBOT SE VA A SALIR DE LA CHAPA");
              isEnd = true;
              newScanIsNeeded = true;


              //return;
          }

          pub_vel->publish(vel_msg);

          waitKey(1);
    }


    public:

    checkNewScanBackwardAction(std::string name) :
        as_(nh_, name, /*boost::bind(&checkNewScanBackwardAction::executeCB, this, _1),*/ false),
        action_name_(name)
      {
        as_.registerGoalCallback(boost::bind(&checkNewScanBackwardAction::goalCB, this));
        as_.registerPreemptCallback(boost::bind(&checkNewScanBackwardAction::preemptCB, this));

        pub_vel = new ros::Publisher(nh.advertise<inspection_realsense::Twist_inspection>("/cmd_vel_robot", 30));



//        sub_pc.subscribe(nh, "/summit_xl/rear_realsense/depth_registered/points" ,1);
//        sub_pc.registerCallback(boost::bind(&checkNewScanBackwardAction::callback, this, _1));


        as_.start();

      }

    ~checkNewScanBackwardAction(void)
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
          vel_goal_ = - goal_->vel;
          mode_ = goal_->mode;

          string topic_name;
          if (mode_ == 0)
              topic_name =  "/summit_xl/front_realsense/depth_registered/points";

          else if (mode_ == 1)
               topic_name = "/summit_xl/rear_realsense/depth_registered/points";

          sub_pc.subscribe(nh, topic_name,1);
          sub_pc.registerCallback(boost::bind(&checkNewScanBackwardAction::callback, this, _1));


      }

    void preemptCB()
    {
      ROS_INFO("%s: Preempted", action_name_.c_str());
      // set the action state to preempted
      as_.setPreempted();
    }

    void executeCB(const inspection_realsense::checkNewScanBackwardGoalConstPtr &goal)
     {
         // make sure that the action hasn't been canceled
         if (!as_.isActive())
           return;

        ros::Rate r(30);

     }

};


int main(int argc, char **argv)
{
    ros::init(argc, argv, "checkNewScanBackward");
    ros::NodeHandle nh;

    checkNewScanBackwardAction checkNewScanBackward("checkNewScanBackward");
    ROS_INFO("Move backward action server is ready!");

    ros::spin();
}
