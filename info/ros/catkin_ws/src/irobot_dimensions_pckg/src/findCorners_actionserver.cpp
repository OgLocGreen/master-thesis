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
  ros::Publisher *vel_pub_;

  typedef message_filters::sync_policies::ApproximateTime <sensor_msgs::Image,
                                                           sensor_msgs::Image,
                                                           sensor_msgs::PointCloud2> MySyncPolicy;

  typedef message_filters::Synchronizer<MySyncPolicy> Sync;
  boost::shared_ptr<Sync> sync;



// Solo si uso PCL
/*
void findSheetPlane(pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_msg, Mat &img_cloud)
{
  img_cloud = Mat(cloud_msg->height, cloud_msg->width, CV_8UC3);

  for (int h=0; h<img_cloud.rows; h++)
  {
   for (int w=0; w<img_cloud.cols; w++)
   {
     pcl::PointXYZRGB point = cloud_msg->at(w, h);
     Eigen::Vector3i rgb = point.getRGBVector3i();
     if (point.y > 0.25 && point.y <0.30)
     {
       img_cloud.at<cv::Vec3b>(h,w)[0] = rgb[0];
       img_cloud.at<cv::Vec3b>(h,w)[1] = rgb[1];
       img_cloud.at<cv::Vec3b>(h,w)[2] = rgb[2];
     }
     else
     {
       img_cloud.at<cv::Vec3b>(h,w)[0] = 0;
       img_cloud.at<cv::Vec3b>(h,w)[1] = 0;
       img_cloud.at<cv::Vec3b>(h,w)[2] = 0;
     }
   }
  }
}
*/
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

int detectVerticalLine(Mat &img, int &pos_x)
{
  cv::addWeighted(img, 3, img, -0.5, 0, img);

  Mat img_gray, img_canny;
  cvtColor(img, img_gray, CV_BGR2GRAY);
  Canny(img_gray,img_canny, 100, 550);

  vector<Vec2f> lines;
  HoughLines(img_canny, lines, 1, 2*CV_PI/180, 100, 0, 0 );

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

void detectSheet(Mat src, Mat &dst, bool recort = true)
{

  // Get only the interest region (Sheet borders by colour)
  Mat frame_HSV, frame_threshold;
  /// Convert from BGR to HSV colorspace
  cvtColor(src, frame_HSV, COLOR_BGR2HSV);
  /// Detect the object based on HSV Range Values
  inRange(frame_HSV, Scalar(0, 70, 50), Scalar(10, 255, 255), frame_threshold);
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

void turnRobot(double ang_rad, double vel_ang)
{
  cmd_vel.linear.x = 0.0;
  cmd_vel.linear.y = 0.0;
  cmd_vel.angular.z = vel_ang;
  vel_pub_->publish(cmd_vel);

  ros::Duration(2*ang_rad/vel_ang).sleep();

  cmd_vel.angular.z = 0.0;
  vel_pub_->publish(cmd_vel);
}

  bool finished = false;
  void callback(const sensor_msgs::Image::ConstPtr &msg_rgb,
                            const sensor_msgs::Image::ConstPtr &msg_depth,
                            const sensor_msgs::PointCloud2::ConstPtr &msg_points)
{

      // make sure that the action hasn't been canceled
      if (!as_.isActive())
        return;

 // Convert ROS image to OpenCV image
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

  namedWindow( "todo", CV_WINDOW_NORMAL );// Create a window for display.
  imshow("todo", img_rgb);


  // Apply homography
  Mat img_homography;

  float data[9] ={-0.6301265052034912, -7.41300208446086, 3083.726098496922,
                   0.06351945027887879, -9.905867862139496, 4179.452812722296,
                   2.393600668406576e-05, -0.002808027645680259, 1};
  H = Mat(3,3,CV_32FC1, data);

  warpPerspective(img_rgb,img_homography,H,Size(6000, 4000));
  resize(img_homography, img_homography, Size(1500,1000));

  /*
  // Convert to pcl point cloud
  pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_msg (new pcl::PointCloud<pcl::PointXYZRGB>);
  pcl::fromROSMsg(*msg_points,*cloud_msg);

  Mat img_sheet;
  findSheetPlane(cloud_msg, img_sheet);

  Mat img_homography_sheet
  warpPerspective(img_sheet,img_homography_sheet,H,Size(6000, 4000)); //Ajustar el tamaño
  resize(img_homography_sheet, img_homography_sheet, Size(1500,1000));

  //namedWindow( "suelo", CV_WINDOW_NORMAL );// Create a window for display.
  //imshow("suelo", img_homography_sheet);
*/


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
    cmd_vel.linear.y = -0.3;
    vel_pub_->publish(cmd_vel);
    ros::Duration(6).sleep();
    cmd_vel.linear.y = 0;
    vel_pub_->publish(cmd_vel);

    turnRobot(CV_PI/2, 0.2);
    isImagesCaptures = false;
    isEdgeDetected = false;
    isLookingCorner = false;
    isEdgeDetected = false;
  }

  // Detect sheet
  Mat img_prueba;
  detectSheet(img_homography,img_prueba, false);

  // Detect edge and turn the robot to the horizontal edge
  if (!isLookingCorner && !isEdgeDetected && !isPanoraming)
  {
    double angle;
    int pos_y_h;
    int a_ = detectBorder(img_prueba, angle, pos_y_h);
    //int a_ = detectBorder(img_homography_sheet, angle, pos_y_h);

    if (a_ == 1)
    {
      if (angle > 0.5 && angle < 50)
        cmd_vel.angular.z = -0.1;

      else if (angle < -0.5 && angle > -50)
        cmd_vel.angular.z = 0.1;

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
        vel_pub_->publish(cmd_vel);
        vel_pub_->publish(cmd_vel);
        sleep(1);

        cout << "BORDE ENCONTRADO, COLOCAR EN POSICIÓN ADECUADA" << endl;

        // Colocar línea horizontal superior en posición adecuada
        if (pos_y_h > img_prueba.rows/2)
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
          cout << "BORDE ENCONTRADO, BUSCAR ESQUINA" << endl;

        }
        vel_pub_->publish(cmd_vel);


      }
    }

    else if (first_first)
    {
      cmd_vel.angular.z = -0.1;
      first_first = false;
    }
  }
  vel_pub_->publish(cmd_vel);


  namedWindow( "prueba", CV_WINDOW_NORMAL );// Create a window for display.
  imshow("prueba", img_prueba);


   // Look for corner to start panoraming
  if (isLookingCorner && !isEdgeDetected && !isPanoraming)
  {
    int pos_x_v;
    cmd_vel.linear.y = -0.2;
    int corner_yn = detectVerticalLine(img_prueba, pos_x_v);

    if (corner_yn == 1)
    {
      if (pos_x_v < img_prueba.cols/2 + 50 && pos_x_v > img_prueba.cols/2 - 50)
      {
        cmd_vel.linear.y = 0;
        vel_pub_->publish(cmd_vel);
        isEdgeDetected = true;
        cout << "ESQUINA ENCONTRADA. PASAR A HACER EL PANORAMA" << endl;
        isPanoraming = true;
        isLookingCorner = false;
      }
    }
  }

  // Start panoraming
  if (isPanoraming)
  {
    cmd_vel.linear.y = 0.2;
    vel_pub_->publish(cmd_vel);

    int pos_x_v;
    int corner_yn = detectVerticalLine(img_prueba, pos_x_v);

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
        cout << "ESQUINA ENCONTRADA.PANORAMA FINALIZADO" << endl;
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



      // ---------- Topic suscription -------------------------------------------
      sub_rgb.subscribe(nh, "/summit_xl_a/realsense/image_raw" ,1);
      sub_depth.subscribe(nh, "/summit_xl_a/realsense/depth/image_raw" ,1);
      sub_points.subscribe(nh, "/summit_xl_a/realsense/points" ,1);

      sync.reset(new Sync(MySyncPolicy(10), sub_rgb, sub_depth, sub_points));
      sync->registerCallback(boost::bind(&findCornersAction::callback, this, _1, _2, _3));

      // ---------- Topic publication -------------------------------------------
      vel_pub_ = new ros::Publisher(nh.advertise<geometry_msgs::Twist>("/summit_xl_a/cmd_vel", 1));

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


      ros::Rate r(1);

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
