#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/PointCloud2.h>
#include <cv_bridge/cv_bridge.h>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/stitching.hpp>
#include "opencv2/xfeatures2d.hpp"
#include <opencv2/aruco.hpp>

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
#include <pcl/search/kdtree.h>
#include <pcl/filters/passthrough.h>
#include <pcl/common/transforms.h>
//#include <fiducial_msgs/FiducialAll.h>
#include <pcl/filters/project_inliers.h>
#include <pcl/surface/convex_hull.h>

#include <tf2_ros/transform_listener.h>
#include <tf2_ros/transform_broadcaster.h>
#include <tf/transform_datatypes.h>
#include <tf2/transform_storage.h>
#include <tf2/transform_datatypes.h>
#include <tf2_eigen/tf2_eigen.h>
#include <tf2/LinearMath/Matrix3x3.h>
#include <tf2/LinearMath/Transform.h>
#include <tf2/LinearMath/Scalar.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <gazebo_msgs/ModelStates.h>


using namespace std;
using namespace cv;

void mySigintHandler(int sig)
{
   ros::shutdown();
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

void detectSheet(Mat src, Mat &dst, Mat &frame_threshold, bool recort = true)
{

  // Get only the interest region (Sheet borders by colour)
  Mat frame_HSV/*, frame_threshold*/;
  /// Convert from BGR to HSV colorspace
  cvtColor(src, frame_HSV, COLOR_BGR2HSV);
  /// Detect the object based on HSV Range Values
  inRange(frame_HSV, Scalar(0, 50, 50), Scalar(50, 255, 255), frame_threshold);
  /// Find contours
  ///
  namedWindow( "THRESHOLD", WINDOW_NORMAL );// Create a window for display.
  imshow("THRESHOLD", frame_threshold);
  waitKey(0);

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

int detectBorder(Mat img, double &Angle_, int &pos_y)
{
  sharpen2D(img,img);

  Mat img_gray, img_canny;
  img_gray = img.clone();
 // cvtColor(img, img_gray, CV_BGR2GRAY);
  /// Reduce noise with a kernel 3x3
 // blur( img_gray, img_gray, Size(3,3) );
  Canny(img_gray,img_canny, 50, 150, 3);

  namedWindow( "THRESHOLD", WINDOW_NORMAL );// Create a window for display.
  imshow("THRESHOLD", img_gray);
  waitKey(0);

  vector<Vec2f> lines;
  HoughLinesP(img_canny, lines, 1, 2*CV_PI/180, 50, 50, 10 );

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
    if ((Angle > 4 && Angle < 50) || (Angle < -4 && Angle > -50))
    {
      line( img, pt1, pt2, Scalar(0,0,255), 3, 2);
      Angle_ = Angle;
      return 1;
    }

    else if (Angle < 4 && Angle > -4)
    {
      if (pt1.y < pos_y)
          pos_y = pt1.y;
      line( img, pt1, pt2, Scalar(255,0,255), 3, 2);
    }
  }
}



void readData(string file_name, Mat &H, double &rel)
{
  FileStorage fs(file_name, FileStorage::READ);

  if (!fs.isOpened())
  {
     ROS_ERROR("Information File not found");
     return;
  }
  else
  {
    fs["Homography"] >> H;
    fs["rel_m_pxls"] >> rel;
    fs.release();
  }
}

bool first = true;
FileStorage fs_;
int id_marker_calib = 0;
string file_name = "/home/irobot/data.yml";

void callback()
{


    if (first)
  {
    fs_.open(file_name, FileStorage::WRITE);
    if (!fs_.isOpened())
    {
      ROS_ERROR("Error creating file");
      return;
    }
    first = false;
  }

  Mat img = imread("/home/irobot/imgs/aruco2_.png");
 // int id_marker_calib = 0;
  Mat H;
  bool isTransformKnown = false;

  // Convertir imagen a Mat
  // Convert ROS image to OpenCV image

  resize(img,img,Size(1500,1000));

  // Buscar aruco

  std::vector<int> ids;
  std::vector<std::vector<cv::Point2f> > corners;
  cv::aruco::detectMarkers(img, aruco::getPredefinedDictionary(aruco::DICT_ARUCO_ORIGINAL), corners, ids);

  aruco::drawDetectedMarkers(img, corners, ids);
  namedWindow( "ARUCO", WINDOW_NORMAL );// Create a window for display.
  imshow("ARUCO", img);


  // ¿Colocar donde corresponda?

  // Calcular homografia

  // Calcular relación metros - píxeles

  //waitKey(0);
  vector<Point2f> detectedCorners;
  bool is_marker = false;
  for (int i=0; i<corners.size(); i++)
  {
    if (ids[i] == id_marker_calib)
    {
      detectedCorners = corners[i];
      is_marker = true;
    }
  }

  double rel_m_pixls;

  if (!is_marker)
  {
    ROS_INFO("Marker not detected");
/*
    float data[9] ={-0.6301265052034912, -7.41300208446086, 3083.726098496922,
                     0.06351945027887879, -9.905867862139496, 4179.452812722296,
                     2.393600668406576e-05, -0.002808027645680259, 1};
    H = Mat(3,3,CV_32FC1, data);

    Mat img_homography;
   // warpPerspective(img,img_homography,H,Size(6000, 4000)); //Ajustar el tamaño
    resize(img, img, Size(1500,1000));

   // namedWindow( "ARUCO_H", WINDOW_NORMAL );// Create a window for display.
   // imshow("ARUCO_H", img_homography);

    double angle;
    int pos_y_h;
    Mat dst;
    detectSheet(img,dst, false);
     namedWindow( "ARUCO_H", WINDOW_NORMAL );// Create a window for display.
     imshow("ARUCO_H", dst);
     waitKey(0);
     warpPerspective(dst,img_homography,H,Size(6000, 4000)); //Ajustar el tamaño
    detectBorder(img_homography, angle, pos_y_h);

    namedWindow( "threshold", WINDOW_NORMAL );// Create a window for display.
    imshow("threshold", img_homography);

    waitKey(0);
    */
  }

  else
  {
    vector<Point2f> inputQuad;
    float o_x = detectedCorners[0].x+2000 , o_y = detectedCorners[0].y+2000;
    float offset = abs (detectedCorners[1].x - detectedCorners[0].x);
   // float offset = 50;
    inputQuad.push_back(Point2f(o_x, o_y));
    inputQuad.push_back(Point2f(o_x+offset, o_y));
    inputQuad.push_back(Point2f(o_x+offset, o_y+offset));
    inputQuad.push_back(Point2f(o_x, o_y+offset));

    H = findHomography( detectedCorners, inputQuad, CV_RANSAC );
   /*
    cout << H << endl;

    float data[9] ={-0.6301265052034912, -7.41300208446086, 3083.726098496922,
                     0.06351945027887879, -9.905867862139496, 4179.452812722296,
                     2.393600668406576e-05, -0.002808027645680259, 1};
    H = Mat(3,3,CV_32FC1, data);
*/
    Mat img_homography;
    warpPerspective(img,img_homography,H,Size(6000, 4000)); //Ajustar el tamaño
    resize(img_homography, img_homography, Size(1500,1000));

    namedWindow( "ARUCO_H", WINDOW_NORMAL );// Create a window for display.
    imshow("ARUCO_H", img_homography);

    Mat img_prueba;
    double angle;
    int pos_y_h;
    //detectSheet(img_homography,img_prueba, false);
    detectBorder(img_prueba, angle, pos_y_h);

    namedWindow( "SHEET", WINDOW_NORMAL );// Create a window for display.
    imshow("SHEET", img_prueba);

    waitKey(0);

    int ancho_pixls = abs (detectedCorners[0].y - detectedCorners[3].y);
    rel_m_pixls = 0.1778 / ancho_pixls;
    cout << rel_m_pixls << endl;

    isTransformKnown = true;
  }

/*
  if (isTransformKnown)
  {
    // Guardar datos en archivo
    fs_ << "Homography" << H;
    fs_ << "rel_m_pxls" << rel_m_pixls;
    fs_.release();

    cout << "Datos guardados correctamente en..." << endl;
    mySigintHandler(1);
  }
*/

/*
    Mat src = imread("/home/irobot/imgs/suelo_recto.png");
    Mat frame_HSV, frame_threshold, dst;
    /// Convert from BGR to HSV colorspace
    cvtColor(src, frame_HSV, COLOR_BGR2HSV);
    /// Detect the object based on HSV Range Values
    inRange(frame_HSV, Scalar(0, 50, 50), Scalar(50, 255, 255), frame_threshold);

    namedWindow( "ARUCO_H", WINDOW_NORMAL );// Create a window for display.
    imshow("ARUCO_H", frame_threshold);
*/
  waitKey(0);
}

void callback2(const geometry_msgs::Twist::ConstPtr& msg)
{
    ROS_INFO("ENTRÉ");
}

int main(int argc, char **argv)
{

    // callback();

/*
    ros::init(argc, argv, "talker");
    ros::NodeHandle nh;

    geometry_msgs::Twist cmd_vel;
    ros::Publisher vel_pub_ = nh.advertise<geometry_msgs::Twist>("/summit_xl_a/cmd_vel", 100);


    ros::Rate loop_rate(10);

    while (ros::Duration(5).sleep())
    {
    cmd_vel.linear.x = 0.0;
    cmd_vel.linear.y = 0.0;
    cmd_vel.angular.z = 160;
    vel_pub_.publish(cmd_vel);



    ros::spinOnce();
    }
*/

  /*
    ros::init(argc, argv, "listener");
    ros::NodeHandle nh;


    ros::Subscriber sub = nh.subscribe("/summit_xl_a/cmd_vel", 1000, callback2);
    ros::spin();
*/


    Mat img = imread("/home/irobot/imgs/vertical.png");
    resize(img,img,Size(1500,1000));

    Mat H;
    float data[9] = { -7.2577313964835966e-01, -5.2185841833731255e+00,
                      3.2822862140546463e+03, -1.6073931379399456e-01,
                      -7.3070127756300502e+00, 4.5676101041902402e+03,
                      -4.0807808887220393e-05, -1.8667106962967325e-03, 1 };
    H = Mat(3,3,CV_32FC1, data);

    Mat img_homography;
    warpPerspective(img,img_homography,H,Size(6000, 4000)); //Ajustar el tamaño
    resize(img_homography, img_homography, Size(1500,1000));

    namedWindow( "ARUCO_H", WINDOW_NORMAL );// Create a window for display.
    imshow("ARUCO_H", img_homography);

    Mat img_prueba, img_thres, img_canny;
    double angle;
    int pos_y_h;
    detectSheet(img_homography,img_prueba, img_thres, false);

    Canny(img_thres,img_canny, 50, 150, 3);

    vector<Vec2f> lines;
    HoughLines(img_canny, lines,1, 2*CV_PI/180, 50, 0, 10 );
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
      line( img_prueba, pt1, pt2, Scalar(0,0,255), 3, CV_AA);
    }

    //detectBorder(img_thres, angle, pos_y_h);

    namedWindow( "SHEET", WINDOW_NORMAL );// Create a window for display.
    imshow("SHEET", img_prueba);

    waitKey(0);

    return 0;
}





































/*************************************
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *




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

#include "std_msgs/String.h"

using namespace cv;
using namespace std;

/*
void chatterCallback(const sensor_msgs::Image::ConstPtr &msg_rgb,
                     const sensor_msgs::Image::ConstPtr &msg_depth)
{
  cv_bridge::CvImagePtr cv_ptr_rgb, cv_ptr_depth;
  try
  {
    cv_ptr_rgb = cv_bridge::toCvCopy(msg_rgb, sensor_msgs::image_encodings::BGR8);
    cv_ptr_depth = cv_bridge::toCvCopy(msg_depth, sensor_msgs::image_encodings::TYPE_32FC1);

  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("cv_bridge exception: %s", e.what());
    return;
  }
  Mat img_rgb, img_depth;
  img_rgb = cv_ptr_rgb->image;
  img_depth = cv_ptr_depth->image;


  imshow("hola", img_rgb);
  imshow("h", img_depth);

  waitKey(1);
}
*/

/*
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

void detectSheet(Mat src, Mat &dst, bool recort = true)
{

  // Get only the interest region (Sheet borders by colour)
  Mat frame_HSV, frame_threshold;
  /// Convert from BGR to HSV colorspace
  cvtColor(src, frame_HSV, COLOR_BGR2HSV);
  /// Detect the object based on HSV Range Values
  inRange(frame_HSV, Scalar(0, 50, 50), Scalar(50, 255, 255), frame_threshold);
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

int detectBorder(Mat img, double &Angle_, int &pos_y)
{
  sharpen2D(img,img);

  Mat img_gray, img_canny;
  cvtColor(img, img_gray, CV_BGR2GRAY);
  /// Reduce noise with a kernel 3x3
  blur( img_gray, img_gray, Size(3,3) );
  Canny(img_gray,img_canny, 50, 150, 3);

  vector<Vec2f> lines;
  HoughLines(img_canny, lines, 1, 2*CV_PI/180, 100, 0, 0 );

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
    if ((Angle > 4 && Angle < 50) || (Angle < -4 && Angle > -50))
    {
      line( img, pt1, pt2, Scalar(0,0,255), 3, 2);
      Angle_ = Angle;
      return 1;
    }

    else if (Angle < 4 && Angle > -4)
    {
      if (pt1.y < pos_y)
          pos_y = pt1.y;
      line( img, pt1, pt2, Scalar(255,0,255), 3, 2);
    }
  }
}

*/

/*
int main(int argc, char* argv[])
{

    Mat src = imread("/home/irobot/imgs/imag5.png");
    Mat frame_HSV, frame_threshold, dst;
    /// Convert from BGR to HSV colorspace
   // cvtColor(src, frame_HSV, COLOR_BGR2HSV);
    /// Detect the object based on HSV Range Values
   // inRange(frame_HSV, Scalar(0, 50, 50), Scalar(50, 255, 255), frame_threshold);

    double angle;
    int pos_y_h;
    detectSheet(src,dst);
    detectBorder(dst, angle, pos_y_h);
    imshow("src", src);
    imshow("threshold", dst);
    waitKey(0);

/*
      ros::init(argc, argv, "listener");
      ros::NodeHandle n;

      message_filters::Subscriber<sensor_msgs::Image> sub_rgb;
      message_filters::Subscriber<sensor_msgs::Image> sub_depth;

      sub_rgb.subscribe(n, "/camera/color/image_raw" ,1);
      sub_depth.subscribe(n, "/camera/depth/image_rect_raw" ,1);

      typedef message_filters::sync_policies::ApproximateTime <sensor_msgs::Image,
                                                               sensor_msgs::Image> MySyncPolicy;

      typedef message_filters::Synchronizer<MySyncPolicy> Sync;
      boost::shared_ptr<Sync> sync;

      sync.reset(new Sync(MySyncPolicy(10), sub_rgb, sub_depth));
      sync->registerCallback(boost::bind(&chatterCallback, _1, _2));
      ros::spin();
      return 0;
  */
      /*
}
*/
