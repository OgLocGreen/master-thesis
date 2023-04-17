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
#include <irobot_inspection_pckg/getPartialPanoramaAction.h>




using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;



class getPartialPanoramaAction
{
protected:

  ros::NodeHandle nh_;
  actionlib::SimpleActionServer<irobot_inspection_pckg::getPartialPanoramaAction> as_; // NodeHandle instance must be created before this line. Otherwise strange error occurs.
  std::string action_name_;

  // create messages that are used to published feedback/result
  irobot_inspection_pckg::getPartialPanoramaResult feedback_;
  irobot_inspection_pckg::getPartialPanoramaResult result_;


  bool getMask(Mat img, Mat &img_mask, Point2f &tl, Point2f &br )
  {
    bool isSuccess = false;
    Mat img_gray, img_thres;

    cvtColor(img, img_gray, CV_BGR2GRAY);
    threshold(img_gray,img_thres,150,255,THRESH_BINARY); // Optimizar los parámeteros //127

    /// Find contours
    Mat dist_8u;
    img_thres.convertTo(dist_8u, CV_8U);
    vector<vector<Point> > contours;
    findContours(dist_8u, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

    /// Find bounding box for each contour
    vector<vector<Point> > contours_poly( contours.size() );
    vector<Rect> boundRect( contours.size() );
    vector<vector<Point> >hull( contours.size() );

    for( int i = 0; i < contours.size(); i++ )
       {
          approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
          boundRect[i] = boundingRect( Mat(contours_poly[i]));
          convexHull( Mat(contours[i]), hull[i], false );
       }

      /// Get the moments
      vector<Moments> mu(contours.size() );
      for( int i = 0; i < contours.size(); i++ )
         { mu[i] = moments( contours[i], false ); }

      ///  Get the mass centers:
      vector<Point2f> mc( contours.size() );
      for( int i = 0; i < contours.size(); i++ )
         { mc[i] = Point2f( mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00 ); }

      vector<bool> isFilled;
      for (int i=0; i<mc.size();i++)
      {
        int largo = boundRect[i].br().y-boundRect[i].tl().y;
        int ancho = boundRect[i].br().x-boundRect[i].tl().x;

        if (mc[i].x != mc[i].x || mc[i].y != mc[i].y)
          isFilled.push_back(true);

        else if (img_thres.at<uchar>(mc[i].y, mc[i].x) == 255)
          isFilled.push_back(true);

        else if (abs (largo-ancho) > 350) //Según tamaño imagen!!
          isFilled.push_back(true);

        else if (boundRect[i].area() < 150)
          isFilled.push_back(true);

        else
          isFilled.push_back(false);
      }

      Rect boundRect_max = Rect();
      for (size_t i = 0; i < contours.size(); i++)
      {
         if (isFilled[i]==true)
           continue;

         if (boundRect[i].area() > boundRect_max.area()/*abs (boundRect[i].tl().y - boundRect[i].br().y) > abs (boundRect_max.tl().y - boundRect_max.br().y)*/)
         {
           boundRect_max = boundRect[i];
           br = boundRect[i].br();
           tl = boundRect[i].tl();
           isSuccess = true;
         }
      }
      img_mask = img(boundRect_max);


      return isSuccess;

  }


public:

  getPartialPanoramaAction(std::string name) :
    as_(nh_, name, boost::bind(&getPartialPanoramaAction::executeCB, this, _1), false),
    action_name_(name)
  {
    as_.start();
  }

  ~getPartialPanoramaAction(void)
  {
  }

  void executeCB(const irobot_inspection_pckg::getPartialPanoramaGoalConstPtr &goal)
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
          string path_fold=goal->folder_path.data.c_str();
          string path_fold_pano=goal->folder_pano_path.data.c_str();
          string direction=goal->direction.data.c_str();

          int n_imgs /* = goal->n_imgs*/;
       //   float rel_m_pixls = 0.004445;


          ROS_INFO("Reading images...");

          vector<cv::String> fn;
          stringstream aux;
          aux << path_fold << "*.tiff";
          glob(aux.str(), fn, false);
          n_imgs = fn.size();

          vector<Mat> imgs;
          int n_img_read=0;
          for(int i=1; i<n_imgs; i++)
          {
            Mat aux;
            stringstream name;
            name << path_fold << i << ".tiff";
            aux = imread(name.str(), CV_LOAD_IMAGE_COLOR);
            resize(aux,aux,Size(1500,1000));
            //---------------------------
            Rect aux_(430,303, 470, 303);
            aux = aux(aux_);
            //---------------------------
            imgs.push_back(aux);
            n_img_read++;
            if (n_img_read % 5 == 0)
                ROS_INFO("%d images readed", n_img_read);
          }

          ROS_INFO("Creating panorama...", n_img_read);

          //Hacer 1 vez
        //  Point2f br(772,650),bl(551,650), tr(772,100), tl(551,100);
          Point2f br(383/4*3,303/4*3),bl(383/4,3*303/4), tr(383/4*3,303/4), tl(383/4,303/4);
          Rect rect (tl.x,tl.y,tr.x-tl.x, bl.y-tl.y);

        Mat panorama(8000,8000,CV_8UC3, Scalar(0));

        float offset_x=3500, offset_y=3500;
        bool first =true;
        int offset_x_aux_ant=0, offset_y_aux_ant=0;

        for(int im=0; im<imgs.size()-1;im++)
        {

          Point2f br_templ, tl_templ, tl_, br_;
          Mat img_template = imgs[im+1];
          Mat templ;
          Mat img_mask;
        /*  if (getMask(img_template, img_mask, tl_, br_))
          {
            templ = img_mask;
            br_templ = br_;
            tl_templ = tl_;

            if (tl_.y < tl.y || br_.y > br.y || tl_.x < tl.x)
            {
              if (tl_.y < tl.y)
                tl_templ = Point2f(tl_.x, tl_.y+(br_.y-tl_.y)/3);
              if (br_.y > br.y)
                br_templ = Point2f(br_.x, br_.y-(br_.y-tl_.y)/3);
             // if (tl_.x < tl.x)
             //   tl_templ = Point2f(tl_.x+tl_.x/3, tl_.y);

              Rect rect_aux (tl_templ.x, tl_templ.y, br_templ.x-tl_templ.x, br_templ.y-tl_templ.y);
              templ = imgs[im+1](rect_aux);

            }

          }

          else
          {*/
            templ = imgs[im+1](rect);
            br_templ = br;
            tl_templ = tl;
          //}
         // namedWindow( "Threshold", CV_WINDOW_NORMAL );// Create a window for display.
         // imshow("Threshold", templ);

          Mat result;
          Mat img = imgs[im];

          /// Source image to display
          Mat img_display;
          img_display = img.clone();
        /// Create the result matrix
          int result_cols =  img.cols - templ.cols + 1;
          int result_rows = img.rows - templ.rows + 1;

          result.create( result_rows, result_cols, CV_32FC1 );

          /// Do the Matching and Normalize
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

          Mat junto(img.rows*2, img.cols*2, CV_8UC3, Scalar(0));
          for (int r=img.rows-1; r>0; r--)
          {
            for(int c=img.cols-1; c>0;c--)
            {
              junto.at<Vec3b>(r,c) = img.at<Vec3b>(r,c);

            }
          }

          //top left = matchLoc. bottom right = Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows )
          /// Show me what you got
          rectangle( img_display, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar(0,255,0), 2, 8, 0 );
          rectangle( img_display, tl_templ, br_templ, Scalar(255,0,0), 2, 8, 0 );


          // rectangle( result, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar::all(0), 2, 8, 0 )


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

        //REFINAR TODO LO DE LOS OFFSET A PARTIR DEL TAMAÑO DE LA IMAGEN!!!
        bool good_measure = true;
        if (/*(offset_x_aux<10 && offset_y_aux<10) ||*/ offset_x_aux > 40 || offset_y_aux > 40)
        {
          offset_x_aux = offset_x_aux_ant;
          offset_y_aux = offset_y_aux_ant;
          good_measure = false;

        }

        else if (offset_x_aux<10)
        {
          offset_x_aux=0;
        }
        else if (offset_y_aux<10)
        {
          offset_y_aux=0;
        }

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

          offset_y = offset_y + offset_y_aux;
          offset_x = offset_x + offset_x_aux;

          for (int r=0; r<img.rows; r++)
          {
            for(int c=0; c<img.cols; c++)
            {
              if (imgs[im+1].at<Vec3b>(r,c) != Vec3b(0,0,0) && panorama.at<Vec3b>(r+offset_y,c+offset_x) == Vec3b(0,0,0) )
                panorama.at<Vec3b>(r+offset_y,c+offset_x) = imgs[im+1].at<Vec3b>(r,c);
            }
          }

//          namedWindow( "panorama", CV_WINDOW_NORMAL );// Create a window for display.
//          imshow("panorama", panorama);

//          namedWindow( "display", CV_WINDOW_NORMAL );// Create a window for display.
//          imshow( "display", img_display );

        //  namedWindow( "result", CV_WINDOW_NORMAL );// Create a window for display.
        //  imshow( "result", result );


          //waitKey(1);
        }


        stringstream path;
        path<< path_fold_pano << "/" << direction << ".png"; //Cambiar el nombre de la imagen según el nombre que le pase
        imwrite(path.str(), panorama);




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
    ros::init(argc, argv, "getpartialpanorama");
    ros::NodeHandle nh;

    getPartialPanoramaAction getpano_server("getpartialpanorama");
    ROS_INFO("getPartialPanorama action server is ready!");

    ros::spin();

}
