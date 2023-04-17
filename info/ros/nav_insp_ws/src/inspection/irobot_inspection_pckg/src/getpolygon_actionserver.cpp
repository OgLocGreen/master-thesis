#include <ros/ros.h>

#include "ros/ros.h"
#include <actionlib/server/simple_action_server.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>

#include <irobot_inspection_pckg/polygonArray.h>
#include <irobot_inspection_pckg/getPolygonsAction.h>

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
#include <irobot_inspection_pckg/getPolygonsAction.h>



using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;


enum Flags
{
    ONLY_LEFT = 0,
    ONLY_RIGHT = 1 << 0,
    ONLY_TOP = 1 << 1,
    ONLY_BOTTOM = 1 << 2,
    TOP_LEFT = 1 << 3,
    TOP_RIGHT = 1 << 4,
    BOTTOM_LEFT = 1 << 5,
    BOTTOM_RIGHT = 1 << 6,
};



class GetPolygonsAction
{
protected:

  ros::NodeHandle nh_;
  actionlib::SimpleActionServer<irobot_inspection_pckg::getPolygonsAction> as_; // NodeHandle instance must be created before this line. Otherwise strange error occurs.
  std::string action_name_;

  // create messages that are used to published feedback/result
  //action_server_package::BaseRotationFeedback feedback_;
  irobot_inspection_pckg::getPolygonsResult result_;

  bool closeOnlyOneSideTouching(vector<Point> vPoints, vector<int> vInd, vector<Point> &polygon, MatSize img_size, int flags )
  {
    int indMin, indMax;
    int min_=1000, max_=0, x_max=0;

    for (int ind=0; ind<vPoints.size(); ind++)
    {
      if (flags == ONLY_LEFT || flags == ONLY_RIGHT)
      {
        if (vPoints[ind].y<min_)
        {
          indMin = ind;
          min_ = vPoints[ind].y;
        }
        if (vPoints[ind].y>=max_ /*&& vPoints[ind].x>x_max*/)
        {
          indMax = ind;
          max_ = vPoints[ind].y;
        //  x_max = vPoints[ind].x;
        }

      }      

      else if (flags == ONLY_TOP || flags == ONLY_BOTTOM)
      {
        if (vPoints[ind].x<min_)
        {
          indMin = ind;
          min_ = vPoints[ind].x;
        }
        if (vPoints[ind].x>max_)
        {
          indMax = ind;
          max_ = vPoints[ind].x;
        }
      }

      else
      {
        cout << "Wrong flag" << endl;
        return false;
      }

    }


    int indMinGlobal = vInd[indMin];
    int indMaxGlobal = vInd[indMax];

 //   polygon[indMaxGlobal].x = img_size[0]-1;
 //   polygon[indMinGlobal].x = img_size[0]-1;

    // Delete elements between points
    if ((polygon[indMinGlobal+1].x >= 0 && polygon[indMinGlobal+1].x < 5) ||
        (polygon[indMinGlobal+1].y >= 0 && polygon[indMinGlobal+1].y < 5) ||
        (polygon[indMinGlobal+1].x > img_size[1] -5 && polygon[indMinGlobal+1].x <= img_size[1]) ||
        (polygon[indMinGlobal+1].y > img_size[0] -5 && polygon[indMinGlobal+1].y <= img_size[0]) )
    {
      polygon.erase(polygon.begin()+min(indMinGlobal, indMaxGlobal)+1, polygon.begin()+max(indMaxGlobal,indMinGlobal));
    }

    else if (vPoints.size()>2)
    {
      polygon.erase(polygon.begin(), polygon.begin()+min(indMinGlobal, indMaxGlobal));
      polygon.erase(polygon.begin()+max(indMaxGlobal,indMinGlobal)+1, polygon.end());
    }

    polygon.insert(polygon.begin()+max(indMaxGlobal,indMinGlobal)+1,Point(img_size[0]-1,polygon[max(indMaxGlobal,indMinGlobal)].y));

    return true;

  }

  bool closeTwoSideTouching(vector<Point> vPointsLateral, vector<int> vIndLateral,
                            vector<Point> vPointsFront, vector<int> vIndFront,
                            vector<Point> &polygon, MatSize img_size, int flags)
  {
    int indX, indY;
    int x_value=0, y_value=0;

    int indXGlobal;
    int indYGlobal;

    // hola que tal,
    if (flags == TOP_LEFT) // x_min, y_min
    {
      x_value = 1000;
      y_value = 1000;
      for (int ind=0; ind<vPointsFront.size(); ind++)
      {
        if (vPointsFront[ind].x<x_value)
        {
          indX = ind;
          x_value = vPointsFront[ind].x;
        }
      }
      for (int ind=0; ind<vPointsLateral.size(); ind++)
      {
        if (vPointsLateral[ind].y<y_value)
          {
            indY = ind;
            y_value = vPointsLateral[ind].y;
          }
      }

      indXGlobal = vIndFront[indX];
      indYGlobal = vIndLateral[indY];

      polygon[indXGlobal] =  Point(0,0);
      polygon[indYGlobal] =  Point(0,0);
    }


    else if (flags == TOP_RIGHT) //  x_max, y_min
    {
      x_value = 0;
      y_value = 1000;
      for (int ind=0; ind<vPointsFront.size(); ind++)
      {
        if (vPointsFront[ind].x>x_value)
        {
          indX = ind;
          x_value = vPointsFront[ind].x;
        }
      }
      for (int ind=0; ind<vPointsLateral.size(); ind++)
      {
        if (vPointsLateral[ind].y<y_value)
          {
            indY = ind;
            y_value = vPointsLateral[ind].y;
          }
      }

      indXGlobal = vIndFront[indX];
      indYGlobal = vIndLateral[indY];

      polygon[indXGlobal] =  Point(img_size[1]-1,0);
      polygon[indYGlobal] =  Point(img_size[1]-1,0);

    }

    else if (flags == BOTTOM_LEFT) // x_min, y_max
    {
      x_value = 1000;
      y_value = 0;
      for (int ind=0; ind<vPointsFront.size(); ind++)
      {
        if (vPointsFront[ind].x<x_value)
        {
          indX = ind;
          x_value = vPointsFront[ind].x;
        }
      }
      for (int ind=0; ind<vPointsLateral.size(); ind++)
      {
        if (vPointsLateral[ind].y>y_value)
          {
            indY = ind;
            y_value = vPointsLateral[ind].y;
          }
      }

      indXGlobal = vIndFront[indX];
      indYGlobal = vIndLateral[indY];

      polygon[indXGlobal] =  Point(0,img_size[0]-1);
      polygon[indYGlobal] =  Point(0,img_size[0]-1);
    }

    else if (flags == BOTTOM_RIGHT) // x_max, y_max
    {
      x_value = 0;
      y_value = 0;
      for (int ind=0; ind<vPointsFront.size(); ind++)
      {
        if (vPointsFront[ind].x>x_value)
        {
          indX = ind;
          x_value = vPointsFront[ind].x;
        }
      }
      for (int ind=0; ind<vPointsLateral.size(); ind++)
      {
        if (vPointsLateral[ind].y>y_value)
          {
            indY = ind;
            y_value = vPointsLateral[ind].y;
          }
      }

      indXGlobal = vIndFront[indX];
      indYGlobal = vIndLateral[indY];

      polygon[indXGlobal] =  Point(img_size[1]-1,img_size[0]-1);
      polygon[indYGlobal] =  Point(img_size[1]-1,img_size[0]-1);

    }

    else
    {
      cout << "Wrong flag" << endl;
      return false;
    }

   /*
    // Delete elements between points
    if ((polygon[indXGlobal+1].x >= 0 && polygon[indXGlobal+1].x <= 5 ) ||
        (polygon[indYGlobal+1].y >= 0 && polygon[indYGlobal+1].y <= 5 ) ||
        (polygon[indXGlobal+1].x >= img_size[1] -5 &&  polygon[indXGlobal+1].x <= img_size[1] ) ||
        (polygon[indYGlobal+1].y >= img_size[0] -5 && polygon[indYGlobal+1].y <= img_size[0] ))
      polygon.erase(polygon.begin()+min(indXGlobal, indYGlobal),  polygon.begin()+max(indXGlobal, indYGlobal));

    else if (vPointsLateral.size()>1 && vPointsFront.size()>1)
    {
      polygon.erase(polygon.begin(), polygon.begin()+min(indXGlobal, indYGlobal));
      polygon.erase(polygon.begin()+max(indXGlobal, indYGlobal), polygon.end() );
    }
   */

    // Delete elements between points
    polygon.erase(polygon.begin()+min(indXGlobal, indYGlobal),  polygon.begin()+max(indXGlobal, indYGlobal));

    return true;

  }


  bool closeOpenPolygon(vector<Point> &polygon, vector<Point> hull,MatSize img_size)
   {
      polygon = hull;
      return true;
   }

public:

  GetPolygonsAction(std::string name) :
    as_(nh_, name, boost::bind(&GetPolygonsAction::executeCB, this, _1), false),
    action_name_(name)
  {
    as_.start();
  }

  ~GetPolygonsAction(void)
  {
  }

  void executeCB(const irobot_inspection_pckg::getPolygonsGoalConstPtr &goal)
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

          ROS_INFO("Buscando poligonos...");
          string path_im= /*"/home/irobot/panoPolygonos/panoramaPoly11.tiff"*/ goal->path.data.c_str(); //CAMBIO
          double dimension_sheet_x = goal->sheet_size_x;
          double dimension_sheet_y = goal->sheet_size_y;


          Mat pano = imread(path_im); //panorama2


          // Get only the interest region (Bordes chapa por color)
          Mat frame_HSV, frame_threshold;
          /// Convert from BGR to HSV colorspace
          cvtColor(pano, frame_HSV, COLOR_BGR2HSV);

          // Detect white forms
          Mat lab_image;
          cv::cvtColor(pano, lab_image, CV_BGR2Lab);

          // Extract the L channel
          std::vector<cv::Mat> lab_planes(3);
          cv::split(lab_image, lab_planes);  // now we have the L image in lab_planes[0]

          // apply the CLAHE algorithm to the L channel
          cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE();
          clahe->setClipLimit(4);
          cv::Mat dst_;
          clahe->apply(lab_planes[0], dst_);

          // Merge the the color planes back into an Lab image
          dst_.copyTo(lab_planes[0]);
          cv::merge(lab_planes, lab_image);

         // convert back to RGB

         cv::Mat image_clahe, pano_thres;
         cv::cvtColor(lab_image, image_clahe, CV_Lab2BGR);

         cvtColor(image_clahe, frame_HSV, COLOR_BGR2HSV);
         inRange(frame_HSV, Scalar(87, 19, 229), Scalar(180, 255, 255), pano_thres);

          Mat kernel;
          kernel = cv::getStructuringElement(MORPH_ELLIPSE, Size(30, 30));
          morphologyEx(pano_thres, pano_thres, MORPH_CLOSE, kernel);
          kernel = cv::getStructuringElement(MORPH_ELLIPSE, Size(2, 2));
          morphologyEx(pano_thres, pano_thres, MORPH_OPEN, kernel);
          kernel = cv::getStructuringElement(MORPH_ELLIPSE, Size(45, 45));
          morphologyEx(pano_thres, pano_thres, MORPH_DILATE, kernel);

          /// Crop and extend borders
         int top, bottom, left, right;
         top = (int) (0.01*pano_thres.rows);
         bottom = (int) (0.025*pano_thres.rows);
         left = (int) (0.01*pano_thres.cols);
         right = (int) (0.025*pano_thres.cols);

          Rect crop(left,top,pano_thres.cols-2*right,pano_thres.rows-2*bottom);
          Mat ROI(pano_thres, crop);
          Mat pano_thres_aux;
          ROI.copyTo(pano_thres_aux);

          Mat dst;
          copyMakeBorder( pano_thres_aux, dst, top, bottom, left, right, BORDER_REPLICATE);

          /// Find contours
          Mat dist_8u;
          Mat markers = Mat::zeros(dst.size(), CV_8UC3);
          dst.convertTo(dist_8u, CV_8U);
          vector<vector<Point> > contours_polygon;
          vector<Vec4i> hierarchy;
          findContours(dist_8u, contours_polygon, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

          /// Find closed contours
          vector<vector<Point>> contours_closed, contours_opened;

          for( int i = 0; i< contours_polygon.size(); i=hierarchy[i][0] ) /// iterate through each contour.
             {
                 Rect r= boundingRect(contours_polygon[i]);
                 if(hierarchy[i][2]<0 && hierarchy[i][3] < 0) /// Check if there is a child contour
                 {
                   //rectangle(pano,Point(r.x-10,r.y-10), Point(r.x+r.width+10,r.y+r.height+10), Scalar(0,0,255),2,8,0); //Opened contour

                   if (r.area() > 45000)
                   {
                        contours_opened.push_back(contours_polygon[i]);
                        Scalar color( rand()&255, rand()&255, rand()&255 );
                        drawContours(markers, contours_polygon, static_cast<int>(i), color, 1);
                      //  rectangle(markers,r.tl(),r.br(),Scalar(255,255,255),10);
                   }
                 }
                 else
                 {
                     //rectangle(pano,Point(r.x-10,r.y-10), Point(r.x+r.width+10,r.y+r.height+10), Scalar(0,255,0),2,8,0); //closed contour

                   if (r.area() > 45000)
                   {
                        contours_closed.push_back(contours_polygon[i]);
                        Scalar color( rand()&255, rand()&255, rand()&255 );
                        drawContours(markers, contours_polygon, static_cast<int>(i), color, 1);
                   }
                 }
             }



          imwrite("/home/irobot/poligonos/marker.jpg", markers);

          // Get polygons of contours
          /// Approx Polygons of closed contours
          vector<vector<Point> > polygons;
          vector<vector<Point> >hull_closed( contours_closed.size() );

          polygons.resize(contours_closed.size());
          for (int k = 0; k < contours_closed.size(); k++)
          {
              convexHull( contours_closed[k], hull_closed[k] );
              polygons[k] = hull_closed[k];
              //approxPolyDP(Mat(contours_closed[k]), polygons[k], 15, true); //3
          }

          /// Close opened polygons
          vector<vector<Point> > polygons_opened;
          vector<vector<Point> >hull( contours_opened.size() );

          polygons_opened.resize(contours_opened.size());
          for (int i=0; i<contours_opened.size(); i++)
          {
            approxPolyDP(Mat(contours_opened[i]), polygons_opened[i], 15, true);
            convexHull( contours_opened[i], hull[i] );
          }

          namedWindow("markers",WINDOW_NORMAL);
          imshow("markers", markers);

          for (int i=0; i<polygons_opened.size();i++)
          {

            vector<Point> polygon = polygons_opened[i];

            bool isTouchingLeft=false, isTouchingRight=false,isTouchingTop=false,isTouchingBottom=false;
            vector<Point> vLeft, vRight, vTop, vBottom;
            vector<int> vIndLeft, vIndRight, vIndTop, vIndBottom;
            for (int k=0; k<polygon.size(); k++)
            {
              Point point = polygons_opened[i][k];
              if (point.x >= 0 && point.x < 5)
              {
                isTouchingLeft = true;
                vLeft.push_back(point);
                vIndLeft.push_back(k);
              }
              if (point.y >= 0 && point.y < 5)
              {
                isTouchingTop = true;
                vTop.push_back(point);
                vIndTop.push_back(k);
              }
              if (point.x <= pano.cols && point.x > pano.cols-100)
              {
                isTouchingRight = true;
                vRight.push_back(point);
                vIndRight.push_back(k);

              }
              if (point.y <= pano.rows && point.y > pano.rows-5)
              {
                isTouchingBottom = true;
                vBottom.push_back(point);
                vIndBottom.push_back(k);
              }
            }


            bool isClosed = false;

            if (isTouchingLeft && isTouchingTop)
              isClosed = closeTwoSideTouching(vLeft,vIndLeft, vTop, vIndTop, polygon, pano.size, TOP_LEFT);

            else if (isTouchingRight && isTouchingBottom)
              isClosed = closeTwoSideTouching(vRight,vIndRight, vBottom, vIndBottom, polygon, pano.size, BOTTOM_RIGHT);

            else if (isTouchingRight && isTouchingTop)
              isClosed = closeTwoSideTouching(vRight,vIndRight, vTop, vIndTop, polygon, pano.size, TOP_RIGHT);

            else if (isTouchingLeft && isTouchingBottom)
              isClosed = closeTwoSideTouching(vLeft,vIndLeft, vBottom, vIndBottom, polygon, pano.size, BOTTOM_LEFT);

            else if ((isTouchingTop && !isTouchingLeft && !isTouchingRight && !isTouchingBottom))
              isClosed = closeOnlyOneSideTouching(vTop, vIndTop, polygon, pano.size, ONLY_TOP);

            else if (isTouchingBottom  && !isTouchingLeft && !isTouchingRight && !isTouchingTop)
              isClosed = closeOnlyOneSideTouching(vBottom, vIndBottom, polygon, pano.size, ONLY_BOTTOM);

            else if (isTouchingLeft && !isTouchingTop && !isTouchingRight && !isTouchingBottom)
              isClosed = closeOnlyOneSideTouching(vLeft, vIndLeft, polygon, pano.size, ONLY_LEFT);

            else if (isTouchingRight && !isTouchingTop && !isTouchingLeft && !isTouchingBottom)
              isClosed = closeOnlyOneSideTouching(vRight, vIndRight, polygon, pano.size, ONLY_RIGHT);

            else
              isClosed = closeOpenPolygon(polygon, hull[i], pano.size);

            if (isClosed)
              polygons.push_back(polygon);

          }


          //Juntar dos polígonos en 1 si se cruzan.
          bool check = true;
          while (check)
          {
              int n_merged=0;
              for(int i=0; i<polygons.size(); i++)
              {

                  for(int j=0; j<polygons.size(); j++)
                  {
                      if (j<=i) continue;
                      Mat im;
                      vector<vector<Point>> p1;
                      p1.push_back(polygons[i]);
                      Mat im1(pano.rows, pano.cols,CV_8UC3,Scalar(0));
                      fillPoly(im1,p1,Scalar(255,255,255),8,0);

                      vector<vector<Point>> p2;
                      p2.push_back(polygons[j]);

                      Mat im2(pano.rows, pano.cols,CV_8UC3,Scalar(0));
                      fillPoly(im2,p2,Scalar(255,255,255),8,0);

                      im = im1+im2;

                      kernel = cv::getStructuringElement(MORPH_ELLIPSE, Size(5, 5));
                      morphologyEx(im, im, MORPH_DILATE, kernel);

                      Mat thres, dist_8u;
                      inRange(im, Scalar(200, 200, 200), Scalar(255, 255, 255), thres);
                      thres.convertTo(dist_8u, CV_8U);

                      vector<vector<Point> > contours_aux;
                      vector<Vec4i> hierarchy_aux;
                      findContours(dist_8u, contours_aux, hierarchy_aux, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
                      Scalar color( rand()&255, rand()&255, rand()&255 );

                      vector<int> id_elim;
                      for (int a=0; a<contours_aux.size(); a++)
                      {
                        Rect r_aux= boundingRect(contours_aux[a]);
                        if (r_aux.area() < 500)
                            id_elim.push_back(a);
                       }

                      for (int a=id_elim.size()-1; a>=0;a--)
                          contours_aux.erase(contours_aux.begin()+id_elim[a]);

                      if (contours_aux.size()==1)
                      {
                          //Eliminar pol[i],pol[j] y sustituir por el nuevo con convex hull
                          vector<vector<Point>> hull_aux( contours_aux.size() );
                          convexHull(contours_aux[0], hull_aux[0] );

                          Mat im_(pano.rows, pano.cols,CV_8UC3,Scalar(0));
                          vector<vector<Point>> p_1,p_2;
                          p_1.push_back(polygons[j]);
                          p_2.push_back(polygons[i]);;

                          polygons.erase(polygons.begin()+j);
                          polygons.erase(polygons.begin()+i);
                          polygons.push_back(hull_aux[0]);
                          n_merged++;
                      }
                  }
              }
              if (n_merged == 0)
                  check = false;
          }




          //Reduce vertices of polygons
          Mat im_aux(pano.rows, pano.cols,CV_8UC3, Scalar(0));
          fillPoly(im_aux,polygons,Scalar(255,255,255),8,0);

          Mat thres, thres_aux;
          inRange(im_aux, Scalar(200, 200, 200), Scalar(255, 255, 255), thres);
          thres.convertTo(thres_aux, CV_8U);

          vector<vector<Point> > contours_fin;
          vector<Vec4i> hierarchy_fin;
          findContours(thres_aux, contours_fin, hierarchy_fin, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
          for (int i=0; i<contours_fin.size();i++)
          {
              approxPolyDP(contours_fin[i],polygons[i],15,true);
          }


          /// Draw polygons
            for (int i=0; i<polygons.size(); i++)
            {
            for (int k=0; k<polygons[i].size(); k++)
            {
            circle(pano,polygons[i][k],5,Scalar(0,0,255));
            }

            Scalar color( rand()&255, rand()&0, rand()&255 );
            polylines(pano,polygons[i],true,color,5);


            }

          // Enviar mensaje polígonos
          double rel_m_pxl_x = dimension_sheet_x/pano.rows; ///metros/pixel
          double rel_m_pxl_y = dimension_sheet_y/pano.cols; ///metros/pixel


          irobot_inspection_pckg::polygonArray msg;
          for (int i=0; i<polygons.size(); i++)
          {
            geometry_msgs::Polygon poly_aux;
             for (int j=polygons[i].size()-1; j>=0; j--)
            {
              geometry_msgs::Point32 aux;
              aux.x = (pano.rows - polygons[i][j].y)*rel_m_pxl_x; ///En metros
              aux.y = (pano.cols - polygons[i][j].x)*rel_m_pxl_y; ///En metros
              aux.z = 0;

              poly_aux.points.push_back(aux);

            }

             msg.polygons.push_back(poly_aux);
             ROS_INFO("Poligono detectado");

          }


          namedWindow( "Panorama", CV_WINDOW_NORMAL );
          imshow ("Panorama", pano);
          imwrite("/home/irobot/poligonos/polygonos.jpg", pano);
          waitKey(0);

          //imwrite("/home/irobot-user/imgs_panorama/polygons.png", pano);


          // this sleep is not necessary, the sequence is computed at 1 Hz for demonstration purposes
          r.sleep();


          if(success)
          {
              result_.poly_array=msg;

              ROS_INFO("%s: Succeeded", action_name_.c_str());
              // set the action state to succeeded
              as_.setSucceeded(result_);
          }
   }
  }
};






int main(int argc, char **argv)
{
    ros::init(argc, argv, "getPolygonsAction_actionserver");
    ros::NodeHandle nh;

    GetPolygonsAction getpoly_server("getpolygon");
    ROS_INFO("Get Polygons action server is ready !!");

    ros::spin();

    ROS_INFO("Hello world!");
}
