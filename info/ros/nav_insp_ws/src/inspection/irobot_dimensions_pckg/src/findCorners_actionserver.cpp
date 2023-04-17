#include <ros/ros.h>
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/PointCloud2.h>
#include <cv_bridge/cv_bridge.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Transform.h>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <signal.h>

#include <actionlib/server/simple_action_server.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <irobot_dimensions_pckg/findCornersAction.h>

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



using namespace std;
using namespace cv;


class findCornersAction
{
protected:

  ros::NodeHandle nh_;
  actionlib::SimpleActionServer<irobot_dimensions_pckg::findCornersAction> as_; // NodeHandle instance must be created before this line. Otherwise strange error occurs.
  std::string action_name_;

  // create messages that are used to published feedback/result
  irobot_dimensions_pckg::findCornersFeedback feedback_;
  irobot_dimensions_pckg::findCornersResult result_;

  //Variables
  Mat H; // Homography matrix

  int index, index_0, index_1;
  int n_hlines_consecutive = 0;
  int n_edgeNotDetected = 0;
  int n_panoramas = 0;

  bool first_first = true;
  bool first = true;
  bool isEdgeDetected = false;
  bool isLookingCorner = false;
  bool isPanoraming = false;
  bool isImagesCaptures = false;

  string path_fold_goal_;

  double vel, yaw_rate;

  ros::NodeHandle nh;
  message_filters::Subscriber<sensor_msgs::Image> sub_rgb;
  message_filters::Subscriber<sensor_msgs::Image> sub_depth;
  message_filters::Subscriber<sensor_msgs::PointCloud2> sub_points;

  geometry_msgs::Twist cmd_vel;
  sensor_msgs::Image img_result;
  ros::Publisher *vel_pub_;
  ros::Publisher *img_result_pub_;

  typedef message_filters::sync_policies::ApproximateTime <sensor_msgs::Image,
                                                           /*sensor_msgs::Image*/
                                                            sensor_msgs::PointCloud2> MySyncPolicy;

  typedef message_filters::Synchronizer<MySyncPolicy> Sync;
  boost::shared_ptr<Sync> sync;

ros::Publisher * pub;

  pcl::PointCloud<pcl::PointXYZRGB>::Ptr passThroughFilter1D(const pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud, const std::string field, const double low, const double high, const bool remove_inside)
  {
      if (low > high)
      {
          std::cout << "Warning! Min is greater than max!\n";
      }

      pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_filtered(new pcl::PointCloud<pcl::PointXYZRGB>);
      pcl::PassThrough<pcl::PointXYZRGB> pass(new pcl::PassThrough<pcl::PointXYZRGB>);

      pass.setInputCloud(cloud);
      pass.setFilterFieldName(field);
      pass.setFilterLimits(low, high);
      pass.setFilterLimitsNegative(remove_inside);
      pass.filter(*cloud_filtered);
      return cloud_filtered;
  }

  cv::Mat makeImageFromPointCloud(pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud, std::string dimensionToRemove, float stepSize1, float stepSize2)
  {
      pcl::PointXYZRGB cloudMin, cloudMax;
      pcl::getMinMax3D(*cloud, cloudMin, cloudMax);

      std::string dimen1, dimen2;
      float dimen1Max, dimen1Min, dimen2Min, dimen2Max;
      if (dimensionToRemove == "x")
      {
          dimen1 = "y";
          dimen2 = "z";
          dimen1Min = cloudMin.y;
          dimen1Max = cloudMax.y;
          dimen2Min = cloudMin.z;
          dimen2Max = cloudMax.z;
      }
      else if (dimensionToRemove == "y")
      {
          dimen1 = "x";
          dimen2 = "z";
          dimen1Min = cloudMin.x;
          dimen1Max = cloudMax.x;
          dimen2Min = cloudMin.z;
          dimen2Max = cloudMax.z;
      }
      else if (dimensionToRemove == "z")
      {
          dimen1 = "x";
          dimen2 = "y";
          dimen1Min = cloudMin.x;
          dimen1Max = cloudMax.x;
          dimen2Min = cloudMin.y;
          dimen2Max = cloudMax.y;
      }

      std::vector<std::vector<int>> pointCountGrid;
      int maxPoints = 0;

      std::vector<pcl::PointCloud<pcl::PointXYZRGB>::Ptr> grid;

      for (float i = dimen1Min; i < dimen1Max; i += stepSize1)
      {
          pcl::PointCloud<pcl::PointXYZRGB>::Ptr slice = passThroughFilter1D(cloud, dimen1, i, i + stepSize1, true);
          grid.push_back(slice);

          std::vector<int> slicePointCount;

          for (float j = dimen2Min; j < dimen2Max; j += stepSize2)
          {
              pcl::PointCloud<pcl::PointXYZRGB>::Ptr grid_cell = passThroughFilter1D(slice, dimen2, j, j + stepSize2, true);

              int gridSize = grid_cell->size();
              slicePointCount.push_back(gridSize);

              if (gridSize > maxPoints)
              {
                  maxPoints = gridSize;
              }
          }
          pointCountGrid.push_back(slicePointCount);
      }

      cv::Mat mat(static_cast<int>(pointCountGrid.size()), static_cast<int>(pointCountGrid.at(0).size()), CV_8UC1);
      mat = cv::Scalar(0);

      for (int i = 0; i < mat.rows; ++i)
      {
          for (int j = 0; j < mat.cols; ++j)
          {
              int pointCount = pointCountGrid.at(i).at(j);
              float percentOfMax = (pointCount + 0.0) / (maxPoints + 0.0);
              int intensity = percentOfMax * 255;

              mat.at<uchar>(i, j) = intensity;
          }
      }

      return mat;
  }

void findSheetPlane(pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_msg, Mat &img_cloud, Mat &img_cloud_bw)
{
  img_cloud = Mat(cloud_msg->height, cloud_msg->width, CV_8UC3);
  img_cloud_bw = Mat(cloud_msg->height, cloud_msg->width, CV_8UC1);

  for (int h=0; h<img_cloud.rows; h++)
  {
   for (int w=0; w<img_cloud.cols; w++)
   {
     pcl::PointXYZRGB point = cloud_msg->at(w, h);
     Eigen::Vector3i rgb = point.getRGBVector3i();


     //if (point.y > 0.45 && point.y <0.58)
     //if (point.y > 0.45 && point.y < 0.65) //REALSENSE TRIPODE
     if (point.y > 0.5/* && point.y < 0.65*/)
     {
       img_cloud.at<cv::Vec3b>(h,w)[0] = rgb[2];
       img_cloud.at<cv::Vec3b>(h,w)[1] = rgb[1];
       img_cloud.at<cv::Vec3b>(h,w)[2] = rgb[0];

       img_cloud_bw.at<uchar>(h,w) = 255;
     }
     else
     {
       img_cloud.at<cv::Vec3b>(h,w)[0] = 0;
       img_cloud.at<cv::Vec3b>(h,w)[1] = 0;
       img_cloud.at<cv::Vec3b>(h,w)[2] = 0;

       img_cloud_bw.at<uchar>(h,w) = 0;
     }
   }
  }

/*
    Mat element = getStructuringElement(MORPH_RECT, Size(20,20));
    morphologyEx( img_cloud_bw, img_cloud_bw, MORPH_OPEN, element );
    morphologyEx( img_cloud_bw, img_cloud_bw, MORPH_CLOSE, element );

    namedWindow( "CIERRE", CV_WINDOW_NORMAL );// Create a window for display.
    imshow("CIERRE", img_cloud_bw);
*/
    pcl::ModelCoefficients::Ptr coefficients (new pcl::ModelCoefficients); //Coeficientes del plano: Ax + By + Cz + D = 0
    pcl::PointIndices::Ptr inliers_groud (new pcl::PointIndices);
    // Create the segmentation object

    pcl::SACSegmentation<pcl::PointXYZRGB> seg;
    // Optional
    seg.setOptimizeCoefficients (true);
    // Mandatory
    seg.setModelType (pcl::SACMODEL_PARALLEL_PLANE);
    seg.setMethodType (pcl::SAC_RANSAC);
    seg.setDistanceThreshold (0.01);//0.01->1cm
    seg.setAxis(Eigen::Vector3f (0.0, 0.0, 1.0));
    //seg.setEpsAngle (10*CV_PI/180);
    seg.setMaxIterations (1000);

    seg.setInputCloud (cloud_msg);
      seg.segment (*inliers_groud, *coefficients);

      if (inliers_groud->indices.size () == 0)
      {
          PCL_ERROR ("Could not estimate a planar model for the given dataset.");
          return;
      }

      // Create the filtering object
        pcl::ExtractIndices<pcl::PointXYZRGB> extract;
        extract.setInputCloud (cloud_msg);
        extract.setIndices (inliers_groud); // --> Utilizar esto para quedarme con la parte de la imagen que quiero ¿?
        extract.setNegative(false);

        pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_groud (new pcl::PointCloud<pcl::PointXYZRGB>);

        extract.filter (*cloud_groud);//get the ground plane

        // Convertir a imagen

        Mat img_ground = makeImageFromPointCloud(cloud_groud, "z", 1,1);
        namedWindow( "GROUND", CV_WINDOW_NORMAL );// Create a window for display.
        imshow("GROUND", img_cloud);

        // Convert to sensor_msgs::PointCloud 2 and publish
        sensor_msgs::PointCloud2 object_msg;
        pcl::toROSMsg(*cloud_groud,object_msg );

        pub->publish(object_msg);

        /*
          Mat img_ground(cloud_msg->height, cloud_msg->width, CV_8UC3, CV_8UC3);
          int h=cloud_msg->height-1,w=cloud_msg->width-1;
          for (int i=cloud_groud->points.size()-1; i>-1; i--)
          {
            if (h<0 || w<0)
              break;

            pcl::PointXYZRGB point = cloud_groud->points[i];
            Eigen::Vector3i rgb = point.getRGBVector3i();

            img_ground.at<cv::Vec3b>(h,w)[0] = rgb[2];
            img_ground.at<cv::Vec3b>(h,w)[1] = rgb[1];
            img_ground.at<cv::Vec3b>(h,w)[2] = rgb[0];

             w--;
             if (w<0)
             {
               w=cloud_msg->width-1;
               h--;
             }

          }
          */
          //namedWindow( "GROUND", CV_WINDOW_NORMAL );// Create a window for display.
          //imshow("GROUND", img_ground);

}

void sharpen2D(const cv::Mat &image, cv::Mat &result) {

  // Construct kernel (all entries initialized to 0)
  cv::Mat kernel(3,3,CV_32F,cv::Scalar(0));
  // assigns kernel values
  kernel.at<float>(1,1)= 5.0;
  kernel.at<float>(0,1)= -1.0;
  kernel.at<float>(2,1)= -1.0;
  kernel.at<float>(1,0)= -1.0;
  kernel.at<float>(1,2)= -1.0;

  //filter the image
  cv::filter2D(image,result,image.depth(),kernel);

}

void mySigintHandler(int sig)
{
   ros::shutdown();
}


int detectBorder(Mat img, Mat frame_threshold, double &Angle_, int &pos_y)
{
  sharpen2D(img,img);

  pos_y = img.rows;
  Mat img_gray, img_canny;
  cvtColor(img, img_gray, CV_BGR2GRAY);
  /// Reduce noise with a kernel 3x3
 // blur( img, img, Size(2,3) );
  Canny(img,img_canny, 100, 200, 3);
  Sobel(img_canny,img_canny,-1,0,1);

  /*
  Mat labelImage, stats, centroids;
  int nLabels = connectedComponentsWithStats(img_canny,labelImage, stats, centroids, 4, CV_32S);

  int temp_label_num=0, vector_size=0;
  vector<int> test;
  for (int i=0; i<stats.rows; i++)
  {
      int area=stats.at<int>(Point(4,i));
      double cent_x = centroids.at<double>(i,0);
      double cent_y = centroids.at<double>(i,1);

      temp_label_num = labelImage.at<int>(cent_x,cent_y);

      if (area>2) //your desired minimun area
      {
          if(temp_label_num>0)
          {
              test.push_back(temp_label_num);
              vector_size++;
          }
          continue;
      }

  }

  Mat temp(img_canny.size(), CV_8UC3, Vec3b(0,0,0));
  for (int i=0; i<labelImage.rows; i++)
  {
      for (int j=0; j<labelImage.cols;j++)
      {
          for (int k=0; k<vector_size; k++)
          {
              if (labelImage.at<int>(i,j) == test[k])
              {
                  //int label = labelImage.at<int>(i,j);
                  Vec3b &pixel = temp.at<Vec3b>(i,j);
                  pixel = Vec3b(255,255,255);
              }
          }
      }
  }
  //cvtColor(temp,temp,COLOR_BGR2GRAY);
  //cv::threshold(temp,temp,128.0,255.0, THRESH_BINARY);
*/

  //Canny(frame_threshold,img_canny, 50, 150, 3);

  //namedWindow( "gray", CV_WINDOW_NORMAL );// Create a window for display.
  //imshow("gray", img_gray);

  /*
  int dil_size = 1;
  Mat element = getStructuringElement( MORPH_ELLIPSE,
                       Size( 2*dil_size+1,2*dil_size+1 ),
                       Point( dil_size,dil_size) );
  dilate( img_canny, img_canny, element );
*/
  vector<Vec2f> lines;
 // HoughLines(img_canny, lines, 1, 2*CV_PI/180, 100, 0, 0 );
  HoughLines(img_canny, lines, 1, CV_PI/180, 60, 0, 0 );

 // namedWindow( "temp", CV_WINDOW_NORMAL );// Create a window for display.
 // imshow("temp", temp);

  namedWindow( "canny", CV_WINDOW_NORMAL );// Create a window for display.
  imshow("canny", img_canny);

  ROS_INFO("Numero lineas: %d",lines.size());
  for (size_t i = 0; i < lines.size(); i++)
  {
    float rho = lines[i][0], theta = lines[i][1];
    Point pt1, pt2;
    double a = cos(theta), b = sin(theta);
    double x0 = a*rho, y0 = b*rho;

    pt1.x = cvRound(x0 + 1000*(-b));
    pt1.y = cvRound(y0 + 1000*(a));
    pt2.x = cvRound(x0 - 1000*(-b));
    pt2.y = cvRound(y0 - 1000*(a));

    double Angle = atan2(pt2.y - pt1.y, pt2.x - pt1.x) * 180.0 / CV_PI;
    if ((Angle > 4 && Angle < 40) || (Angle < -4 && Angle > -40))
    {
      line( img, pt1, pt2, Scalar(0,0,255), 3, 2);
      Angle_ = Angle;
      line( img, pt1, pt2, Scalar(255,0,255), 3, 2);

      return 1;
    }

    else if (Angle < 4 && Angle > -4)
    {
      if (pt1.y < pos_y)
          pos_y = pt1.y;
      line( img, pt1, pt2, Scalar(255,0,255), 3, 2);
    }

  }

  namedWindow( "detectBorder", CV_WINDOW_NORMAL );// Create a window for display.
  imshow("detectBorder", img);
 // waitKey();

  return -1;

}

int detectVerticalLine(Mat &img, Mat frame_threshold, int &pos_x)
{
  cv::addWeighted(img, 3, img, -0.5, 0, img);

  Mat img_gray, img_canny;
  cvtColor(img, img_gray, CV_BGR2GRAY);
  Canny(frame_threshold,img_canny, 100, 550);

  vector<Vec2f> lines;
  HoughLines(img_canny, lines, 1, 2*CV_PI/180, 50, 0, 10 );


  namedWindow( "CANNY_", CV_WINDOW_NORMAL );// Create a window for display.
  imshow("CANNY_", img_canny);
  waitKey(1);


  Point pt1_v, pt2_v;

  bool isVertical = false, isLeft = false, isRight = false;

  for (size_t i = 0; i < lines.size(); i++)
  {
    float rho = lines[i][0], theta = lines[i][1];
    Point pt1, pt2;
    double a = cos(theta), b = sin(theta);
    double x0 = a*rho, y0 = b*rho;

    pt1.x = cvRound(x0 + 1000*(-b));
    pt1.y = cvRound(y0 + 1000*(a));
    pt2.x = cvRound(x0 - 1000*(-b));
    pt2.y = cvRound(y0 - 1000*(a));

    double Angle = round(atan2(pt2.y - pt1.y, pt2.x - pt1.x) * 180.0 / CV_PI);


    //Left line
    if ((Angle > 53 && Angle < 58) && (pt1.x < img.cols || pt2.x < img.cols))
    {
      isLeft = true;
    }

    //Right line
    if ((Angle < -53 && Angle > -58) && (pt1.x > img.cols || pt2.x > img.cols))
    {
      isRight = true;
    }

    if (abs(Angle) > 85 && abs(Angle) < 95 )
    {
      pos_x = pt1.x;
      isVertical = true;
      pt1_v=pt1;
      pt2_v=pt2;

      line( img, pt1, pt2, Scalar(255,255,0), 3, 2);


    }
    else
      line( img, pt1, pt2, Scalar(0,255,0), 3, 2);
  }

  if (isVertical)
  {
    if (isLeft && pos_x <= img.cols/2)
    {}
    else if (isRight && pos_x >= img.cols/2)
    {}
    else
    {
      line( img, pt1_v, pt2_v, Scalar(255,0,0), 3, 2);
      return 1;
    }
  }
}

void detectSheet(Mat src, Mat &dst, Mat &frame_threshold, bool recort = true)
{

  // Get only the interest region (Sheet borders by colour)
  Mat frame_HSV/*, frame_threshold*/;
  /// Convert from BGR to HSV colorspace
  cvtColor(src, frame_HSV, COLOR_BGR2HSV);
  /// Detect the object based on HSV Range Values
  inRange(frame_HSV, Scalar(0, 60, 180), Scalar(45, 140, 255), frame_threshold);
  /// Find contours
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

void turnRobot(double ang_rad, double vel_rpm)
{
  cmd_vel.linear.x = 0.0;
  cmd_vel.linear.y = 0.0;
  cmd_vel.angular.z = vel_rpm;
  vel_pub_->publish(cmd_vel);

  double vel_ang = vel_rpm*2*CV_PI/60;

  ros::Duration(2*ang_rad/vel_ang).sleep();

  cmd_vel.angular.z = 0.0;
  vel_pub_->publish(cmd_vel);
}

  bool finished = false;
  void callback(const sensor_msgs::Image::ConstPtr &msg_rgb,
                            /*const sensor_msgs::Image::ConstPtr &msg_depth*/
                            const sensor_msgs::PointCloud2::ConstPtr &msg_points)
{

    ROS_INFO("Find Corners");
      // make sure that the action hasn't been canceled
      if (!as_.isActive())
        return;

 // Convert ROS image to OpenCV image
  cv_bridge::CvImagePtr cv_ptr_rgb, cv_ptr_depth;
  try
  {
    cv_ptr_rgb = cv_bridge::toCvCopy(msg_rgb, sensor_msgs::image_encodings::BGR8);
   // cv_ptr_depth = cv_bridge::toCvCopy(msg_depth, sensor_msgs::image_encodings::TYPE_32FC1);

  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("cv_bridge exception: %s", e.what());
    return;
  }
  Mat img_rgb, img_depth;
  img_rgb = cv_ptr_rgb->image;
 // img_depth = cv_ptr_depth->image;

  namedWindow( "todo", CV_WINDOW_NORMAL );// Create a window for display.
  imshow("todo", img_rgb);

  resize(img_rgb,img_rgb,Size(1500,1000));

  // Apply homography
  Mat img_homography;

  /*
  float data[9] ={-0.6301265052034912, -7.41300208446086, 3083.726098496922,
                   0.06351945027887879, -9.905867862139496, 4179.452812722296,
                   2.393600668406576e-05, -0.002808027645680259, 1};
*/
  /*
 float data[9] = { -7.2577313964835966e-01, -5.2185841833731255e+00,
                   3.2822862140546463e+03, -1.6073931379399456e-01,
                   -7.3070127756300502e+00, 4.5676101041902402e+03,
                   -4.0807808887220393e-05, -1.8667106962967325e-03, 1 };
*/
  float data[9] = {-1.2910847131586896e+00, -5.9386599143107244e+00,
                   3.3187124342207335e+03, -3.0794042239498781e-01,
                   -9.8263300640239972e+00, 5.8018791588819804e+03,
                   -1.0786004287039858e-04, -2.2345666455110208e-03, 1.};

H = Mat(3,3,CV_32FC1, data);

  warpPerspective(img_rgb,img_homography,H,Size(6000, 4000));
  resize(img_homography, img_homography, Size(1500,1000));
 // namedWindow( "HOMOGRAFIA", CV_WINDOW_NORMAL );// Create a window for display.
 // imshow("HOMOGRAFIA", img_homography);


  // Convert to pcl point cloud
  pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_msg (new pcl::PointCloud<pcl::PointXYZRGB>);
  pcl::fromROSMsg(*msg_points,*cloud_msg);

  Mat img_sheet, img_sheet_bw;// = img_rgb;
 // findSheetPlane(cloud_msg, img_sheet, img_sheet_bw); -------------------------------

 // namedWindow( "suelo__", CV_WINDOW_NORMAL );// Create a window for display.
 // imshow("suelo__", img_sheet);

/*---------------
  Mat img_homography_sheet;
  resize(img_sheet, img_sheet, Size(1500,1000));
  warpPerspective(img_sheet,img_homography_sheet,H,Size(6000, 4000)); //Ajustar el tamaño
  resize(img_homography_sheet, img_homography_sheet, Size(1500,1000));
----------------------*/
//  namedWindow( "suelo", CV_WINDOW_NORMAL );// Create a window for display.
//  imshow("suelo", img_homography_sheet);



  // If panoramas are made, finish program
  if (n_panoramas == 2)
  {
    cmd_vel.linear.x = 0;
    cmd_vel.linear.y = 0;
    cmd_vel.angular.z = 0;
    vel_pub_->publish(cmd_vel);

    cout << "PROGRAMA TERMINADO. FINALIZANDO..." << endl;

    feedback_.n_imgs1 = index_0;
    feedback_.n_imgs2 = index_1;

    result_.n_imgs1 = index_0;
    result_.n_imgs2 = index_1;

    as_.setSucceeded(result_);

    finished = true;

//    mySigintHandler(1);
  }


  if (isImagesCaptures == true && n_panoramas == 1)
  {
    cmd_vel.linear.y = -0.2;
    vel_pub_->publish(cmd_vel);
    ros::Duration(6).sleep();
    cmd_vel.linear.y = 0;
    vel_pub_->publish(cmd_vel);

    turnRobot(CV_PI/2, 90);
    isImagesCaptures = false;
    isEdgeDetected = false;
    isLookingCorner = false;
    isEdgeDetected = false;
  }

  // Detect sheet

  findSheetPlane(cloud_msg, img_sheet, img_sheet_bw);
  Mat img_homography_sheet;
  resize(img_sheet, img_sheet, Size(1500,1000));
  warpPerspective(img_sheet,img_homography_sheet,H,Size(6000, 4000)); //Ajustar el tamaño
  resize(img_homography_sheet, img_homography_sheet, Size(1500,1000));

  Mat img_prueba,/* = img_homography_sheet,*/ frame_thres;
  detectSheet(img_homography_sheet,img_prueba, frame_thres, false); //////////////////////////////////////

 // namedWindow( "prueba", CV_WINDOW_NORMAL );// Create a window for display.
 // imshow("prueba", img_prueba);

  //Cambiar detectsheet por color a plano con info de profundidad

  // Detect edge and turn the robot to the horizontal edge
  if (!isLookingCorner && !isEdgeDetected && !isPanoraming)
  {


    double angle;
    int pos_y_h;
    int a_ = detectBorder(img_prueba, frame_thres, angle, pos_y_h);

    namedWindow( "prueba", CV_WINDOW_NORMAL );// Create a window for display.
    imshow("prueba", img_prueba);
    //img_result = cv_bridge::CvImage(std_msgs::Header(), "bgr8", img_prueba).toImageMsg();
   // img_result_pub_->publish(cv_bridge::CvImage(std_msgs::Header(), "bgr8", img_prueba).toImageMsg());

    //int a_ = detectBorder(img_homography_sheet, angle, pos_y_h);


  //  if(a_ == -1)
  //  {
  //      ROS_INFO("NO BORDER DETECTED")
  //}

    if (a_ == 1)
    {
      if (angle > 0.5 && angle < 50)
        cmd_vel.angular.z = 0.2;

      else if (angle < -0.5 && angle > -50)
        cmd_vel.angular.z = -0.2;

      first = false;
      first_first = false;
      n_hlines_consecutive = 0;
    }
    else if (first == false)
    {
      n_hlines_consecutive++;

      if (n_hlines_consecutive == 4)
      {
        cmd_vel.angular.z = 0.0;
  cmd_vel.angular.z = - cmd_vel.angular.z; //QUITAR ESTOOOOOOOOOOS
        vel_pub_->publish(cmd_vel);
        vel_pub_->publish(cmd_vel);
        sleep(1);

        ROS_INFO("BORDE ENCONTRADO, COLOCAR EN POSICIÓN ADECUADA");


        // Colocar línea horizontal superior en posición adecuada
        if (pos_y_h > img_prueba.rows/2 +200)
        {
          cmd_vel.linear.x = -0.2;
        }

        else if (pos_y_h < img_prueba.rows/2 -200)
        {
          cmd_vel.linear.x = +0.2;
        }

        else
        {
          cmd_vel.linear.x = 0;
          isLookingCorner = true;
          ROS_INFO("BORDE ENCONTRADO, BUSCAR ESQUINA");

        }
  cmd_vel.linear.x = - cmd_vel.linear.x; //QUITAR ESTOOOOOOOOOOS

        vel_pub_->publish(cmd_vel);
        n_hlines_consecutive = 0;

      }
    }

    else if (first_first)
    {
      cmd_vel.angular.z = -0.2;
      first_first = false;
    }
  }

  cmd_vel.angular.z = - cmd_vel.angular.z; //QUITAR ESTOOOOOOOOOOS
  cmd_vel.linear.x = - cmd_vel.linear.x; //QUITAR ESTOOOOOOOOOOS

  vel_pub_->publish(cmd_vel);


 // namedWindow( "prueba", CV_WINDOW_NORMAL );// Create a window for display.
 // imshow("prueba", img_prueba);


   // Look for corner to start panoraming
  if (isLookingCorner && !isEdgeDetected && !isPanoraming)
  {
      ROS_INFO("LOOK FOR CORNER");

    int pos_x_v;
    cmd_vel.linear.y = -0.2;

    int corner_yn = detectVerticalLine(img_prueba, frame_thres, pos_x_v);

    ROS_INFO("DETECT VERTICAL LINE");

    if (corner_yn == 1)
    {
      if (pos_x_v < img_prueba.cols/2 + 50 && pos_x_v > img_prueba.cols/2 - 250)
      {
        cmd_vel.linear.y = 0;
        vel_pub_->publish(cmd_vel);
        isEdgeDetected = true;
        ROS_INFO("ESQUINA ENCONTRADA. PASAR A HACER EL PANORAMA");

        isPanoraming = true;
        isLookingCorner = false;
      }
    }
  }

  // Start panoraming
  if (isPanoraming)
  {
      ROS_INFO("IS PANORAMING");

    cmd_vel.linear.y = 0.2;
    vel_pub_->publish(cmd_vel);

    int pos_x_v;
    int corner_yn = detectVerticalLine(img_prueba, frame_thres, pos_x_v);

    if (corner_yn != 1)
    {
      n_edgeNotDetected ++;
      if (n_edgeNotDetected == 5)
        isEdgeDetected = false;
    }

    if (corner_yn == 1 && !isEdgeDetected)
    {
      if (pos_x_v < img_prueba.cols/2 + 150 && pos_x_v > img_prueba.cols/2 - 200)
      {
        cmd_vel.linear.y = 0;
        vel_pub_->publish(cmd_vel);
        isEdgeDetected = true;
        ROS_INFO("ESQUINA ENCONTRADA.PANORAMA FINALIZADO");

        isPanoraming = false;
        isImagesCaptures = true;
        n_panoramas ++;
        n_edgeNotDetected = 0;
	
	if (n_panoramas == 1)
		index_0 = index;
	if (n_panoramas == 2)
		index_1 = index;

        index = 0;
      }
    }

  }

  vel_pub_->publish(cmd_vel);


// Save images
  stringstream name;
  name << "/home/sara/imagenesDimensions" << n_panoramas << "/" << index << ".tiff";
  resize(img_homography,img_homography,Size(1500,1000));

  if (isPanoraming)
  {
     imwrite(name.str(), img_homography);
     index++;
  }

  waitKey(1);
}




public:

  findCornersAction(std::string name) :
    as_(nh_, name, /*boost::bind(&findCornersAction::executeCB, this, _1),*/ false),
    action_name_(name)
  {
      //register the goal and feeback callbacks
      as_.registerGoalCallback(boost::bind(&findCornersAction::goalCB, this));
      as_.registerPreemptCallback(boost::bind(&findCornersAction::preemptCB, this));



        pub = new ros::Publisher(nh.advertise<sensor_msgs::PointCloud2>("/aux", 1));

      // ---------- Topic suscription -------------------------------------------
     // sub_rgb.subscribe(nh, "/summit_xl_a/realsense/image_raw" ,1);
 /*
      sub_rgb.subscribe(nh, "/camera/color/image_raw" ,1);
      sub_depth.subscribe(nh, "/camera/depth/image_rect_raw" ,1);
*/
      //sub_depth.subscribe(nh, "/summit_xl_a/realsense/depth/image_raw" ,1);
      //sub_points.subscribe(nh, "/summit_xl_a/realsense/points" ,1);

    //  sub_rgb.subscribe(nh, "/summit_xl/front_rgbd_camera/rgb/image_raw" ,1);
    //  sub_depth.subscribe(nh, "/summit_xl/front_rgbd_camera/depth/image_raw" ,1);
    //  sub_points.subscribe(nh, "/summit_xl/front_rgbd_camera/depth/points" ,1); //depth_registered -->color

        sub_rgb.subscribe(nh, "/summit_xl/front_realsense/color/image_raw" ,1);
        sub_depth.subscribe(nh, "/summit_xl/front_realsense/depth/image_rect_raw" ,1);
        sub_points.subscribe(nh, "/summit_xl/front_realsense/depth_registered/points" ,1);

      sync.reset(new Sync(MySyncPolicy(10), sub_rgb, sub_points));
      sync->registerCallback(boost::bind(&findCornersAction::callback, this, _1, _2));

      // ---------- Topic publication -------------------------------------------
      vel_pub_ = new ros::Publisher(nh.advertise<geometry_msgs::Twist>("/summit_xl/cmd_vel", 1));
      img_result_pub_ = new ros::Publisher(nh.advertise<sensor_msgs::Image>("/get_dimensions/image_result", 1));

      as_.start();
  }

  ~findCornersAction(void)
  {
  }

  void goalCB()
  {
    // reset helper variables
      // helper variables
      nh = nh;
      first = true;
      index=0;
      cmd_vel.linear.x = cmd_vel.linear.y = cmd_vel.angular.z = 0;
      //string path_fold=goal->folder_path.data.c_str();
      // accept the new goal
      path_fold_goal_ = as_.acceptNewGoal()->folder_path.data.c_str();
  }

  void preemptCB()
    {
      ROS_INFO("%s: Preempted", action_name_.c_str());
      // set the action state to preempted
      as_.setPreempted();
    }

  void executeCB(const irobot_dimensions_pckg::findCornersGoalConstPtr &goal)
  {
      // helper variables
    /*  nh = nh;
      first = true;
      index=0;
      cmd_vel.linear.x = cmd_vel.linear.y = cmd_vel.angular.z = 0;
      string path_fold=goal->folder_path.data.c_str();
*/

      // make sure that the action hasn't been canceled
      if (!as_.isActive())
        return;


      ros::Rate r(30);

      //bool success = true;

      //feedback

      // start executing the action
        // check that preempt has not been requested by the client
   /*     if (as_.isPreemptRequested() || !ros::ok())
        {

          ROS_INFO("%s: Preempted", action_name_.c_str());
          // set the action state to preempted
          as_.setPreempted();
          success = false;

        }

        else
        {



          r.sleep();

          if(success )
          {
              ROS_INFO("%s: Succeeded", action_name_.c_str());
              // set the action state to succeeded
              as_.setSucceeded(result_);
          }

      }

  */
  }
};


int main(int argc, char **argv)
{
    ros::init(argc, argv, "findcorners");
    ros::NodeHandle nh;

    findCornersAction findCorners("findcorners");
    ROS_INFO("findCorners action server is ready!");

    ros::spin();
}
