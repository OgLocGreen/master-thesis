#include <ros/ros.h>

#include "ros/ros.h"
#include <actionlib/server/simple_action_server.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>

///includes de merge.h

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

#include <geometry_msgs/Polygon.h>
#include <irobot_inspection_pckg/polygonArray.h>
#include <irobot_inspection_pckg/getCompletePanoramaAction.h>




using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;



class getCompletePanoramaAction
{
protected:

  ros::NodeHandle nh_;
  actionlib::SimpleActionServer<irobot_inspection_pckg::getCompletePanoramaAction> as_; // NodeHandle instance must be created before this line. Otherwise strange error occurs.
  std::string action_name_;

  // create messages that are used to published feedback/result
  //action_server_package::BaseRotationFeedback feedback_;
  irobot_inspection_pckg::getCompletePanoramaResult result_;


  void deleteBlackArea(Mat src, Mat &dst)
  {
    // Get only the interest region (Bordes chapa por color)
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
    dst = src(boundRect_max);
  }


public:

  getCompletePanoramaAction(std::string name) :
    as_(nh_, name, boost::bind(&getCompletePanoramaAction::executeCB, this, _1), false),
    action_name_(name)
  {
    as_.start();
  }

  ~getCompletePanoramaAction(void)
  {
  }

  void executeCB(const irobot_inspection_pckg::getCompletePanoramaGoalConstPtr &goal)
  {
      // helper variables
      ros::Rate r(1);
      bool success = true;

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
          string path_fold=goal->folder_pano_path.data.c_str();
          string name_0=goal->name_0.data.c_str();
          string name_180=goal->name_180.data.c_str();

          int n_imgs = 2;
          vector<Mat> imgs;

            // Read partial panoramas

          stringstream name_img_0, name_img_180;
          name_img_0 << path_fold << "/" << name_0 << ".png";
          Mat im_0 = imread(name_img_0.str(), CV_LOAD_IMAGE_COLOR);
          deleteBlackArea(im_0,im_0);
          resize(im_0,im_0,Size(200,500));

          name_img_180 << path_fold << "/" << name_180 << ".png";
          Mat im_180 = imread(name_img_180.str(), CV_LOAD_IMAGE_COLOR);
          deleteBlackArea(im_180,im_180);
          resize(im_180,im_180,Size(200,500));

          Point2f src_center(im_180.cols/2.0F, im_180.rows/2.0F);
          Mat rot_mat = getRotationMatrix2D(src_center, 180, 1.0);
          warpAffine(im_180, im_180, rot_mat, im_180.size());

          imgs.push_back(im_0);
          imgs.push_back(im_180);

          imshow("0", im_0);
          imshow("180", im_180);


          /*
            for (int i=1; i<n_imgs+1; i++)
            {
              Mat aux;
              stringstream name;
              name << path_fold << i << ".png";
              aux = imread(name.str(), CV_LOAD_IMAGE_COLOR);
              deleteBlackArea(aux,aux);
              resize(aux,aux,Size(200,500));

              if (i==2)
              {
                Point2f src_center(aux.cols/2.0F, aux.rows/2.0F);
                Mat rot_mat = getRotationMatrix2D(src_center, 180, 1.0);
                warpAffine(aux, aux, rot_mat, aux.size());
              }
              imgs.push_back(aux);
            }
*/
            bool first = true;
            float offset_x=100, offset_y=100;
            int offset_x_aux_ant=0, offset_y_aux_ant=0;
            Mat panorama(1000,500,CV_8UC3, Scalar(0));

            //Point2f br(150,400),bl(50,400), tr(150,100), tl(50,100);
            Point2f br(150,350),bl(50,350), tr(150,150), tl(50,150);

            Rect rect (tl.x,tl.y,tr.x-tl.x, bl.y-tl.y);

            // Create complete panorama
            for(int im=0; im<imgs.size()-1;im++)
            {
              Mat templ = imgs[im+1](rect);
              Mat img = imgs[im];
              Mat result;
              Point2f br_templ = br;//Point2f(templ.cols, templ.rows);
              Point2f tl_templ = tl;//Point2f(0,0);

              Mat img_display;
              img_display = img.clone();

              // Do the Matching and Normalize
              int match_method = CV_TM_CCOEFF_NORMED ; //Mirar el tipo //CV_TM_SQDIFF_NORMED
              try
              {
               // ximgproc::colorMatchTemplate(img, templ, result);
                matchTemplate( img, templ, result, match_method );
              }

              catch(Exception& e)
              {
                ROS_INFO("ERROR");
                continue;
              }
              normalize( result, result, 0, 1, NORM_MINMAX, -1, Mat() );

              /// Localizing the best match with minMaxLoc
              double minVal; double maxVal; Point minLoc; Point maxLoc;
              Point matchLoc;
              minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );

              /// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
              if( match_method  == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED )
                { matchLoc = minLoc; }
              else
                { matchLoc = maxLoc; }

              rectangle( img_display, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar(0,255,0), 2, 8, 0 );
              rectangle( img_display, tl_templ, br_templ, Scalar(255,0,0), 2, 8, 0 );

              imshow("display", img_display);

              if (first)
              {
                for (int r=0; r<img.rows; r++)
                {
                  for(int c=0; c<img.cols; c++)
                  {
                    panorama.at<Vec3b>(r+offset_y,c+offset_x) = img.at<Vec3b>(r,c);
                  }
                }

                first = false;
              }

              int offset_x_aux, offset_y_aux;
              offset_x_aux =(int) abs(tl_templ.x - matchLoc.x);
              offset_y_aux =(int) abs(tl_templ.y - matchLoc.y);

              bool good_measure = true;
              if (good_measure)
              {
                if (matchLoc.x > tl_templ.x && matchLoc.y <= tl_templ.y)
                {
                  offset_x_aux = offset_x_aux;
                  offset_y_aux = -offset_y_aux;
                }
                else if (matchLoc.x > tl_templ.x && matchLoc.y > tl_templ.y)
                {
                  offset_x_aux = offset_x_aux;
                  offset_y_aux = offset_y_aux;
                }
                else if (matchLoc.x <= tl_templ.x && matchLoc.y > tl_templ.y)
                {
                  offset_x_aux = -offset_x_aux;
                  offset_y_aux = offset_y_aux;
                }
                else if (matchLoc.x <= tl_templ.x && matchLoc.y <= tl_templ.y)
                {
                  offset_x_aux = -offset_x_aux;
                  offset_y_aux = -offset_y_aux;
                }

                offset_x_aux_ant = offset_x_aux;
                offset_y_aux_ant = offset_y_aux;
              }

                offset_x_aux=0;

                offset_y = offset_y + offset_y_aux;
                offset_x = offset_x + offset_x_aux;


                for (int r=0; r<img.rows; r++) //img o imgs[im+1]
                {
                  for(int c=0; c<img.cols; c++)
                  {
                    if (imgs[im+1].at<Vec3b>(r,c) != Vec3b(0,0,0) && panorama.at<Vec3b>(r+offset_y,c+offset_x) == Vec3b(0,0,0) )
                      panorama.at<Vec3b>(r+offset_y,c+offset_x) = imgs[im+1].at<Vec3b>(r,c);
                  }
                }
            }

            deleteBlackArea(panorama, panorama);

            stringstream path;
            path<<path_fold << "/panoramaCompleto.png";
            imwrite(path.str(), panorama);

            imshow("PANO", panorama);
            waitKey(0);


            ROS_INFO("Panorama generated correctly");









          // this sleep is not necessary, the sequence is computed at 1 Hz for demonstration purposes
          r.sleep();


          if(success)
          {
              //result_.poly_array=msg;

              ROS_INFO("%s: Succeeded", action_name_.c_str());
              // set the action state to succeeded
              as_.setSucceeded(result_);
          }
   }
  }
};






int main(int argc, char **argv)
{
    ros::init(argc, argv, "getCompletePanoramaAction_actionserver");
    ros::NodeHandle nh;

    getCompletePanoramaAction getpano_server("getCompletePanorama");
    ROS_INFO("getCompletePanorama action server is ready!");

    ros::spin();

}
