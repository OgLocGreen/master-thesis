#include "ros/ros.h"
#include <actionlib/server/simple_action_server.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include "dirent.h"

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
#include <opencv2/ximgproc.hpp>


#include <irobot_dimensions_pckg/obtainDimensionAction.h>


using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;



class obtainDimensionAction
{
protected:

  ros::NodeHandle nh_;
  actionlib::SimpleActionServer<irobot_dimensions_pckg::obtainDimensionAction> as_; // NodeHandle instance must be created before this line. Otherwise strange error occurs.
  std::string action_name_;

  // create messages that are used to published feedback/result
  irobot_dimensions_pckg::obtainDimensionFeedback feedback_;
  irobot_dimensions_pckg::obtainDimensionResult result_;

void detectSheet(Mat src, Mat &dst, bool recort = true)
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

  if (recort == true)
    dst = src(boundRect_max);

  else
  {
    dst = src;

  //  Mat element = getStructuringElement( MORPH_ELLIPSE, Size(50, 50));
  //  morphologyEx( src, src, MORPH_CLOSE, element );

    for (int h=0; h<src.rows; h++)
    {
     for (int w=0; w<src.cols; w++)
     {
        //si w y h están fuera del rect, lo coloreo
       if ((w > boundRect_max.tl().x && w < boundRect_max.br().x) &&
           (h > boundRect_max.tl().y && h < boundRect_max.br().y) /*&&
           (frame_threshold.at<uchar>(h,w) == 255)*/)
           //dst.at<Vec3b>(h,w) = Vec3b(255,255,255);

           continue;

       else
         dst.at<Vec3b>(h,w) = Vec3b(0,0,0);

     }
    }
  }
}





public:

  obtainDimensionAction(std::string name) :
    as_(nh_, name, boost::bind(&obtainDimensionAction::executeCB, this, _1), false),
    action_name_(name)
  {
    as_.start();
  }

  ~obtainDimensionAction(void)
  {
  }

  void executeCB(const irobot_dimensions_pckg::obtainDimensionGoalConstPtr &goal)
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

          stringstream path_fold;
          int n_imgs;
          // string path_fold=goal->folder_path.data.c_str();
          string path_fold1 = goal->folder_path1.data.c_str();;
          int n_imgs1 = goal->n_imgs1;

          string path_fold2 = goal->folder_path2.data.c_str();;
          int n_imgs2 = goal->n_imgs2;

		  float rel_m_pixls = 0.004445;

		  vector<Mat> imgs;
		  int n_img_read = 0;

          double dimension1, dimension2;


          for (int veces = 0; veces < 2; veces++)
          {
              if (veces == 0)
              {
                  n_imgs = n_imgs1;
                  path_fold.str("");
                  path_fold << path_fold1;
              }
              else if (veces == 1)
              {
                  n_imgs = n_imgs2;
                  path_fold.str("");
                  path_fold << path_fold2;
              }

              n_img_read = 0;
              imgs.clear();

              for(int i=0; i<n_imgs; i=i+2)
              {
                Mat aux;
                stringstream name;
                name << path_fold.str() << i << ".tiff";
                aux = imread(name.str(), CV_LOAD_IMAGE_COLOR);
                imgs.push_back(aux);

                n_img_read++;
                if (n_img_read%5 == 0)
                  ROS_INFO("%d images readed", n_img_read);

                waitKey(1);
              }

             Point2f br(775,725),bl(549,725), tr(775,10), tl(549,10);
             Rect rect (tl.x,tl.y,tr.x-tl.x, bl.y-tl.y);

             Mat panorama(6000,8000,CV_8UC3, Scalar(0));
             float offset_x=4500, offset_y=3500;
             bool first = true;
             int offset_x_aux_ant=0, offset_y_aux_ant=0;


             ROS_INFO("Obtaining dimensions...");
             for(int im=0; im<imgs.size()-1;im++)
             {

              Point2f br_templ, tl_templ;
              Mat templ;

              templ = imgs[im+1](rect);
              br_templ = br;
              tl_templ = tl;

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

              /// Show me what you got
              rectangle( img_display, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar(0,255,0), 2, 8, 0 );
              rectangle( img_display, tl_templ, br_templ, Scalar(255,0,0), 2, 8, 0 );


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
            if ( offset_x_aux > 40 || offset_y_aux > 40)
            {
              offset_x_aux = offset_x_aux_ant;
              offset_y_aux = offset_y_aux_ant;
              good_measure = false;
            }

            //else if (offset_y_aux>0)
            //{
            //  offset_y_aux=0;
            //}

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

      //        namedWindow( "panorama", CV_WINDOW_NORMAL );// Create a window for display.
      //        imshow("panorama", panorama);

      //        namedWindow( "display", CV_WINDOW_NORMAL );// Create a window for display.
      //        imshow( "display", img_display );


      //         waitKey(1);

            }

            namedWindow( "panorama", CV_WINDOW_NORMAL );// Create a window for display.
            imshow("panorama", panorama);
            waitKey (1);

            // Calculate sheet dimensions
            detectSheet(panorama,panorama);
            double dimension_m = panorama.cols * rel_m_pixls;

            cout << "La chapa mide " << dimension_m << " metros en esta dirección" << endl;

            if (veces == 0)
                dimension1 = dimension_m;
            if (veces == 1)
                dimension2 = dimension_m;
          }
		  


        cout << "La chapa mide " << max(dimension1, dimension2) << "x"  << min(dimension1, dimension2) << "metros" << endl;
        feedback_.large = max(dimension1, dimension2);
        feedback_.width = min(dimension1, dimension2);

        result_.large = feedback_.large;
        result_.width = feedback_.width;


		if(success)
		  {
		      ROS_INFO("%s: Succeeded", action_name_.c_str());
		      // set the action state to succeeded
		      as_.setSucceeded(result_);

        }
    }
  }
};




int main(int argc, char **argv)
{
    ros::init(argc, argv, "obtaindimension");
    ros::NodeHandle nh;

    obtainDimensionAction obtainDimension("obtaindimension");
    ROS_INFO("obtainDimensions action server is ready!");

    ros::spin();

}
