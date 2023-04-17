#! /usr/bin/env python

from __future__ import print_function
import rospy

from action_server_package.srv import *
from geometry_msgs.msg import Point, PolygonStamped
from time import sleep

     
def draw_chapas():

    rospy.wait_for_service('chapa_storage')

    try:
        chapas_server = rospy.ServiceProxy('/chapa_storage', ChapaStorage)
        chapas_resp = chapas_server(0)
        n_chapas=chapas_resp.number_of_chapas
    except  rospy.ServiceException:
        return



    for i in xrange(0,n_chapas):
        chapas_resp=chapas_server(i)

        string_topic="chapa_id%s" % i
        pub = rospy.Publisher(string_topic, PolygonStamped, queue_size=10)
        
        polyStamp=PolygonStamped()

        polyStamp.header.frame_id="map"

        polyStamp.polygon.points.append(chapas_resp.coordA)
        polyStamp.polygon.points.append(chapas_resp.coordB)
        polyStamp.polygon.points.append(chapas_resp.coordC)
        polyStamp.polygon.points.append(chapas_resp.coordD)

        sleep(1)#Para asegurarse de que se publica
        for i in xrange(0,50):
            pub.publish(polyStamp)

    return 

if __name__ == '__main__':
    try:
        # Initializes a rospy node so that the SimpleActionClient can
        # publish and subscribe over ROS.
        rospy.init_node('draw_chapas_py')
        draw_chapas()
        print("---------CHAPAS DIBUJADAS")
    except rospy.ROSInterruptException:
        print("program interrupted before completion", file=sys.stderr)