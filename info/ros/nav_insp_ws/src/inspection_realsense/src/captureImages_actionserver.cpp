#include <ros/ros.h>
#include <inspection_realsense/captureImagesAction.h>

#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <pcl_ros/transforms.h>

#include <cv_bridge/cv_bridge.h>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <actionlib/server/simple_action_server.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <signal.h>

#include <tf/transform_listener.h>

using namespace std;
using namespace cv;



class captureImagesAction
{
protected:
    ros::NodeHandle nh_;
    ros::NodeHandle nh;
    actionlib::SimpleActionServer<inspection_realsense::captureImagesAction> as_; // NodeHandle instance must be created before this line. Otherwise strange error occurs.
    std::string action_name_;

    // create messages that are used to published feedback/result
    inspection_realsense::captureImagesFeedback feedback_;
    inspection_realsense::captureImagesResult result_;

    message_filters::Subscriber<sensor_msgs::Image> sub_front;
    message_filters::Subscriber<sensor_msgs::Image> sub_rear;

    typedef message_filters::sync_policies::ApproximateTime <sensor_msgs::Image,
                                                             sensor_msgs::Image> MySyncPolicy;
    typedef message_filters::Synchronizer<MySyncPolicy> Sync;
    boost::shared_ptr<Sync> sync;

    // Variables
    string path_fold;
    bool first_bool;
    bool new_goal = true;
    int n_imgs_ant=-1;

    void callback(const sensor_msgs::Image::ConstPtr &msg_front,
                  const sensor_msgs::Image::ConstPtr &msg_rear)
    {
        if (!as_.isActive())
         {
          // first_bool = true;
           return;
         }

        if (new_goal)
        {
            new_goal = false;
            vector<cv::String> fn;
            stringstream aux;
            aux << path_fold <<"_front/" << "*.tiff";
            glob(aux.str(), fn, false);
            n_imgs_ant = fn.size();
        }

         if (first_bool)
         {
             // Eliminar todas las imagenes del directorio
             vector<cv::String> fn;
             stringstream aux;
             aux << "exec rm -r " << path_fold <<"_front/" << "*.tiff";
             aux << "exec rm -r " << path_fold <<"_rear/" << "*.tiff";

             cout << aux.str() << endl;
             system(aux.str().c_str());

             // irobot_fcpp_simul::bool_aux::ConstPtr bool_msg = ros::topic::waitForMessage<irobot_fcpp_simul::bool_aux>("/getImagesBool");
             first_bool = false;
         }

            // Convert ROS image to OpenCV image
            cv_bridge::CvImagePtr cv_ptr_front, cv_ptr_rear;
            try
            {
              cv_ptr_front = cv_bridge::toCvCopy(msg_front, sensor_msgs::image_encodings::BGR8);
              cv_ptr_rear = cv_bridge::toCvCopy(msg_rear, sensor_msgs::image_encodings::BGR8);

            }
            catch (cv_bridge::Exception& e)
            {
              ROS_ERROR("cv_bridge exception: %s", e.what());
              return;
            }
            Mat img_front, img_rear;
            img_front = cv_ptr_front->image;
            img_rear = cv_ptr_rear->image;

            //Apply homography
            Mat img_homography_front, img_homography_rear;


            float data_front[9] = {6.016344012082745, 30.14062607399775, -1696.231661764519,
                                   0.08856350362927527, 43.77080730172647, -5128.439446737068,
                                   3.620748308637643e-05, 0.01095165953183649, 1};


            float data_rear[9] ={-0.6301265052034912, -7.41300208446086, 3083.726098496922,
                             0.06351945027887879, -9.905867862139496, 4179.452812722296,
                             2.393600668406576e-05, -0.002808027645680259, 1};

            Mat H_front = Mat(3,3,CV_32FC1, data_front);
            Mat H_rear = Mat(3,3,CV_32FC1, data_rear);

            resize(img_front,img_front,Size(1500,1000));
            resize(img_rear,img_rear,Size(1500,1000));

            warpPerspective(img_front,img_homography_front,H_front,Size(6000, 4000)); //Ajustar el tamaño
            warpPerspective(img_rear,img_homography_rear,H_rear,Size(6000, 4000)); //Ajustar el tamaño

            resize(img_homography_front,img_homography_front,Size(1500,1000));
            resize(img_homography_rear,img_homography_rear,Size(1500,1000));

            //Save images
            stringstream name_front, name_rear;
            name_front << path_fold <<"_front/" << n_imgs_ant <<".tiff";
            name_rear << path_fold <<"_rear/" << n_imgs_ant <<".tiff";

            imwrite(name_front.str(), img_homography_front);
            imwrite(name_rear.str(), img_homography_rear);

            n_imgs_ant++;

            //Save positions
            waitKey(1);
    }

public:
    captureImagesAction(std::string name) :
        as_(nh_, name, false),
        action_name_(name)
    {
        //register the goal and feeback callbacks
        as_.registerGoalCallback(boost::bind(&captureImagesAction::goalCB, this));
        as_.registerPreemptCallback(boost::bind(&captureImagesAction::preemptCB, this));

        sub_front.subscribe(nh, "/summit_xl/front_realsense/color/image_raw" ,1);
        sub_rear.subscribe(nh, "/summit_xl/rear_realsense/color/image_raw" ,1);

        sync.reset(new Sync(MySyncPolicy(10), sub_front, sub_rear));
        sync->registerCallback(boost::bind(&captureImagesAction::callback, this, _1, _2));

        as_.start();
    }

    ~captureImagesAction(void)
     {
     }

    void goalCB()
    {
        nh = nh;
        auto goal = as_.acceptNewGoal();
        if (goal != NULL)
        {
            path_fold=goal->folder_path.data.c_str();
            new_goal = true;
        }

    }

    void preemptCB()
      {
        ROS_INFO("%s: Preempted", action_name_.c_str());
        // set the action state to preempted
        as_.setPreempted();
      }

    void executeCB(const inspection_realsense::captureImagesGoalConstPtr &goal)
     {
         // make sure that the action hasn't been canceled
         if (!as_.isActive())
         {
           new_goal = true;
           return;
         }
        ros::Rate r(30);

     }

};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "captureImages_actionserver");
    ros::NodeHandle nh;

    captureImagesAction captureImages("getimages");
    ROS_INFO("getImages action server is ready!");

    ros::spin();

}
