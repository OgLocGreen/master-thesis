#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>

#include <irobot_fcpp_simul/ComputeDefectsDecompAction.h>
#include <irobot_fcpp_simul/FCPP_in.h>"
#include <irobot_fcpp_simul/FCPP_out.h>"

class DecompOutSorage_Service_Class
{
protected:

        //Vector de Defectos
       std::vector<irobot_fcpp_simul::defecto> defectos_vec;

        ros::NodeHandle n;
        ros::ServiceServer service;

        bool fcpp_out_service(irobot_fcpp_simul::FCPP_out::Request  &req,
                              irobot_fcpp_simul::FCPP_out::Response &res)
                {
                 res.defecto_out=defectos_vec;

                  ROS_INFO("sending back response");
                  return true;
                }

public:
        //Constructor
        DecompOutSorage_Service_Class(std::vector<irobot_fcpp_simul::defecto> vector_defectos)
        {
            defectos_vec=vector_defectos;
        }

        void loop()
        {
            service = n.advertiseService("fcpp_outdata_service", &DecompOutSorage_Service_Class::fcpp_out_service, this);
             ROS_INFO("Servicio de almacenamiento de los datos de salida para el FCPP---> LISTO");
             while (ros::ok()) { ros::spinOnce(); }
        }
};




int main(int argc, char **argv)
{

    ros::init(argc, argv, "computedefectdecomposition_node");
    ros::NodeHandle nh;

    // create the action client
      // true causes the client to spin its own thread
      actionlib::SimpleActionClient<irobot_fcpp_simul::ComputeDefectsDecompAction> ac("ComputeDefects", true);

      ROS_INFO("Waiting for action server to start.");
      // wait for the action server to start
      ac.waitForServer(); //will wait for infinite time

      ROS_INFO("Action server started, sending goal.");

      ros::ServiceClient client = nh.serviceClient<irobot_fcpp_simul::FCPP_in>("fcpp_data_service");

      irobot_fcpp_simul::FCPP_in srv;

      srv.request.id_input=-1;
      srv.request.get_working_zones=false;

      if (!client.call(srv))
      {ROS_ERROR("Failed to call service!!!!!");}

      int n_defectos=srv.response.n_defects;

      // send a goal to the action
      std::vector<irobot_fcpp_simul::defecto> vector_defectos;
      for(int i=0; i<n_defectos; i++)
      {
          irobot_fcpp_simul::defecto d_msg;
          irobot_fcpp_simul::ComputeDefectsDecompGoal goal;
                                                      goal.chapa_id=i;

          ac.sendGoal(goal);

          //wait for the action to return
          bool finished_before_timeout = ac.waitForResult(ros::Duration(30.0));

          if (finished_before_timeout)
          {
            actionlib::SimpleClientGoalState state = ac.getState();
            ROS_INFO("Action finished: %s",state.toString().c_str());
          }
          else
            ROS_INFO("Action did not finish before the time out.");


          d_msg=ac.getResult()->defecto;
          vector_defectos.push_back(d_msg);
     }

      //Subir los vectores de defectos a un servicio



    DecompOutSorage_Service_Class DecompServer(vector_defectos);
    DecompServer.loop();

    ros::spin();


    return 0;
}
