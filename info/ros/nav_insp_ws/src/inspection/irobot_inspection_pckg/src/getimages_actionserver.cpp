#include <ros/ros.h>

#include "ros/ros.h"
#include <actionlib/server/simple_action_server.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>

///includes de merge.h
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/PointCloud2.h>
#include <cv_bridge/cv_bridge.h>

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
//include <fiducial_msgs/FiducialAll.h>
#include <pcl/filters/project_inliers.h>
#include <pcl/surface/convex_hull.h>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/stitching.hpp>
#include "opencv2/xfeatures2d.hpp"
//#include <opencv2/imgproc.hpp>
#include <opencv2/ximgproc.hpp>
//#include <opencv2/ximgproc/color_match.hpp>
#include <opencv2/aruco.hpp>

#include <tf2_ros/transform_listener.h>
#include <tf2_ros/transform_broadcaster.h>
#include <tf/transform_datatypes.h>
#include <tf2/transform_storage.h>
#include <tf2/transform_datatypes.h>
#include <tf2/LinearMath/Matrix3x3.h>
#include <tf2/LinearMath/Transform.h>
#include <tf2/LinearMath/Scalar.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <gazebo_msgs/ModelStates.h>
#include <cv_bridge/cv_bridge.h>


#include <geometry_msgs/Polygon.h>
#include <irobot_inspection_pckg/polygonArray.h>
#include <irobot_inspection_pckg/getImagesAction.h>
#include <irobot_fcpp_simul/bool_aux.h>


using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;


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

class getImagesAction
{
protected:

  ros::NodeHandle nh_;
  actionlib::SimpleActionServer<irobot_inspection_pckg::getImagesAction> as_; // NodeHandle instance must be created before this line. Otherwise strange error occurs.
  std::string action_name_;

  // create messages that are used to published feedback/result
  irobot_inspection_pckg::getImagesResult feedback_;
  irobot_inspection_pckg::getImagesResult result_;

  //Variables de panorama.cpp
  Mat panorama = Mat(8000,8000, CV_8UC3, Scalar(0));
  bool hazlo = false;
  vector<Mat> imgs_panorama;
  Mat img_prev;
  Mat H;
  bool first;
  bool isTransformKnown;
  int id_marker_calib;
  geometry_msgs::Transform T_ground_camera;
  int index;
  bool first_gazebo = true;
  bool first_bool = true;
  float pos_x_ant=0;
  float pos_y_ant=0;
  string path_fold;
  string path_calib;

  ros::NodeHandle nh;
  message_filters::Subscriber<sensor_msgs::Image> sub_rgb;
  message_filters::Subscriber<sensor_msgs::Image> sub_depth;
  message_filters::Subscriber<sensor_msgs::PointCloud2> sub_points;

  message_filters::Subscriber<irobot_fcpp_simul::bool_aux> sub_bool;
 // message_filters::Subscriber<sensor_msgs::Image> sub_gazebo;

  gazebo_msgs::ModelStatesConstPtr gazeboModel_ptr;
  ros::Publisher *pub;

  typedef message_filters::sync_policies::ApproximateTime <sensor_msgs::Image,
                                                           sensor_msgs::Image,
                                                           sensor_msgs::PointCloud2> MySyncPolicy;
  typedef message_filters::Synchronizer<MySyncPolicy> Sync;
  boost::shared_ptr<Sync> sync;

/*
  void gazeboCallback(const gazebo_msgs::ModelStatesConstPtr &msg)
  {

    vector<string> names = msg->name;
    int id_robot;

    for (int j=0; j<names.size();j++)
    {
      if (names[j]=="summit_xl_a" )
        id_robot = j;
    }

    float pos_x = msg->pose[id_robot].position.x;
    float pos_y = msg->pose[id_robot].position.y;

    float despl_x = pos_x - pos_x_ant;
    float despl_y = pos_y - pos_y_ant;

    if (first_gazebo)
    {
      despl_x = 0;
      despl_y = 0;
    }

    //Data to a .csv
//    myfile << index << "," << pos_x << "," << pos_y << "," << despl_x << "," << despl_y << "\n";
//    myfile.flush();

    pos_x_ant = pos_x;
    pos_y_ant = pos_y;

    first_gazebo = false;
  }

  */
  void tf2Mat(tf2::Matrix3x3 m_tf, Mat &m_mat)
  {

      double mat_data[9] = {m_tf[0][0], m_tf[0][1], m_tf[0][2],
                            m_tf[1][0], m_tf[1][1], m_tf[1][2],
                            m_tf[2][0], m_tf[2][1], m_tf[2][2]};

      Mat aux = Mat (3, 3, CV_64FC1, mat_data);
      m_mat = aux.clone();

  }


  void callback(const sensor_msgs::Image::ConstPtr &msg_rgb,
                const sensor_msgs::Image::ConstPtr &msg_depth,
                const sensor_msgs::PointCloud2::ConstPtr &msg_points)
  {

      ROS_INFO("GET IMAGES");
      // make sure that the action hasn't been canceled
      if (!as_.isActive())
      {
    //    feedback_.n_imgs = index;
    //    result_.n_imgs = index;

   //     as_.setSucceeded(result_);

        first_bool = true;
        return;
      }


      if (first_bool)
      {
          // Eliminar todas las imagenes del directorio
          vector<cv::String> fn;
          stringstream aux;
          aux << "exec rm -r " << path_fold << "*.tiff";
          //glob(aux.str(), fn, false);

          cout << aux.str() << endl;
          system(aux.str().c_str());



          irobot_fcpp_simul::bool_aux::ConstPtr bool_msg = ros::topic::waitForMessage<irobot_fcpp_simul::bool_aux>("/getImagesBool");         
          first_bool = false;
      }


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


  // ---------------------------------------------------------------------------------------------------

  // ---------------------------------------------------------------------------------------------------

    // Find ground Plane

    // Convert to pcl point cloud
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_msg (new pcl::PointCloud<pcl::PointXYZRGB>);
    pcl::fromROSMsg(*msg_points,*cloud_msg);


    // Select ground plane and convert to Mat
    Mat img_cloud(cloud_msg->height, cloud_msg->width, CV_8UC3);
   // stringstream name_;
   // name_ << "/home/sara/imagenesHomografiaHorizontal/" << index << "_entera.png";
    //imwrite(name_.str(),img_rgb );

    for (int h=0; h<img_cloud.rows; h++)
    {
     for (int w=0; w<img_cloud.cols; w++)
     {
       pcl::PointXYZRGB point = cloud_msg->at(w, h);
       Eigen::Vector3i rgb = point.getRGBVector3i();
       if (point.y > 0.25 /*&& point.y <0.30*/) //0.15
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

  //  stringstream name2_;
  //  name2_ << "/home/sara/imagenesHomografiaHorizontal/" << index << "_suelo.png";
    //imwrite(name2_.str(),img_cloud );
   // namedWindow( "suelo", CV_WINDOW_NORMAL );// Create a window for display.
   // imshow("suelo", img_cloud);

  // Homography

    Mat img_homography;

  /*
    float data[9] ={-0.6301265052034912, -7.41300208446086, 3083.726098496922,
                     0.06351945027887879, -9.905867862139496, 4179.452812722296,
                     2.393600668406576e-05, -0.002808027645680259, 1};
    H = Mat(3,3,CV_32FC1, data);
  */

    warpPerspective(img_cloud,img_homography,H,Size(6000, 4000)); //Ajustar el tamaño



    //namedWindow( "prueba", CV_WINDOW_NORMAL );// Create a window for display.
    //imshow("prueba", img_homography);
    stringstream name;
    name << path_fold << index << ".tiff";
    resize(img_homography,img_homography,Size(1500,1000));
    imwrite(name.str(), img_homography);


    index++;
    waitKey(1);
  }



public:

  getImagesAction(std::string name) :
    as_(nh_, name, false),
    action_name_(name)
  {

      //register the goal and feeback callbacks
      as_.registerGoalCallback(boost::bind(&getImagesAction::goalCB, this));
      as_.registerPreemptCallback(boost::bind(&getImagesAction::preemptCB, this));


      // ---------- Topic suscription -------------------------------------------
  /*
      sub_rgb.subscribe(nh, "/summit_xl_a/realsense/image_raw" ,1);
      sub_depth.subscribe(nh, "/summit_xl_a/realsense/depth/image_raw" ,1);
      sub_points.subscribe(nh, "/summit_xl_a/realsense/points" ,1);
      */
      sub_rgb.subscribe(nh, "/summit_xl/front_realsense/color/image_raw" ,1);
      sub_depth.subscribe(nh, "/summit_xl/front_realsense/depth/image_rect_raw" ,1);
      sub_points.subscribe(nh, "/summit_xl/front_realsense/depth_registered/points" ,1);
     // sub_bool.subscribe(nh, "/getImagesBool",1);

      sync.reset(new Sync(MySyncPolicy(10), sub_rgb, sub_depth, sub_points));
      sync->registerCallback(boost::bind(&getImagesAction::callback, this, _1, _2, _3));

      as_.start();
  }

  ~getImagesAction(void)
  {
  }

  void goalCB()
  {

      nh = nh;
      first = true;
      isTransformKnown = false;
      index=0;

      auto goal = as_.acceptNewGoal();
      path_fold=goal->folder_path.data.c_str();
      path_calib=goal->calib_path.data.c_str();
      id_marker_calib=goal->id_marker;

      first_bool = true;

      double rel;
      readData(path_calib, H, rel);
  }

  void preemptCB()
    {
      ROS_INFO("%s: Preempted", action_name_.c_str());
      // set the action state to preempted
      as_.setPreempted();
    }
  void executeCB(const irobot_inspection_pckg::getImagesGoalConstPtr &goal)
  {


      // make sure that the action hasn't been canceled
      if (!as_.isActive())
        return;

      // helper variables
      ros::Rate r(1);

      /*
      //irobot_fcpp_simul::defecto d_msg;

      // start executing the action

        // check that preempt has not been requested by the client
        if (as_.isPreemptRequested() || !ros::ok())
        {

          ROS_INFO("%s: Preempted", action_name_.c_str());
          // set the action state to preempted
          as_.setPreempted();
          success = false;

        }

        else
        {
          string path_fold=goal->folder_path.data.c_str();
          nh = nh;
          first = true;
          isTransformKnown = false;
          id_marker_calib = 9;

          double rel;
          readData("/home/sara/data.yml", H, rel);

          // ---------- Topic suscription -------------------------------------------
          sub_rgb.subscribe(nh, "/summit_xl_a/realsense/image_raw" ,1);
          sub_depth.subscribe(nh, "/summit_xl_a/realsense/depth/image_raw" ,1);
          sub_points.subscribe(nh, "/summit_xl_a/realsense/points" ,1);

          sync.reset(new Sync(MySyncPolicy(10), sub_rgb, sub_depth, sub_points));
          sync->registerCallback(boost::bind(&GetImagesAction::callback, this, _1, _2, _3, path_fold));

//          pub = new ros::Publisher(nh.advertise<sensor_msgs::PointCloud2>("/aux", 1));

          index=0;

          // Create csv
//          myfile.open ("/home/sara/imagenesHomografiaHorizontal/datos.csv");
//          myfile << "n_imagen" << "," << "pos_x" << "," << "pos_y" << "," << "despl_x" << "," << "despl_y" << "\n";

          ROS_INFO("Panorama Node Ready");



        }
*/

  }
};




int main(int argc, char **argv)
{
    ros::init(argc, argv, "getimages");
    ros::NodeHandle nh;

    getImagesAction getpano_server("getimages");
    ROS_INFO("getImages action server is ready!");

    ros::spin();
}
