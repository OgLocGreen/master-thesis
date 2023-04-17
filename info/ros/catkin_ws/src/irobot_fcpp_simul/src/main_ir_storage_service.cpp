#include <ros/ros.h>

#include "irobot_ir_storage_service_class.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "main_ir_storage_service");
    ros::NodeHandle nh;

    IROBOT_ir_Storage_Service_Class *srv_class= new IROBOT_ir_Storage_Service_Class();

    srv_class->loop();


}
