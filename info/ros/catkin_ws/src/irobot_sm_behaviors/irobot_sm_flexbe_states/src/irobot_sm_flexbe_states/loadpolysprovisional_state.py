#!/usr/bin/env python
import rospy

from flexbe_core import EventState, Logger

import roslib
from std_srvs.srv import EmptyRequest, Empty

from geometry_msgs.msg import Point32, Polygon


import sys
sys.path.append('/home/irobot-user/irobot_qt_ws/devel/lib/python2.7/dist-packages')

from irobot_fcpp_simul.srv import IROBOT_ir_data, IROBOT_ir_dataRequest

class LoadPolygonsToIRServerState(EventState):
    '''
    Provisonal state to load polygons to the irobot ir storage service


    <= done                 Input data info set
    <= failed               Input data info failed

    '''

    def __init__(self):
        # Declare outcomes, input_keys, and output_keys by calling the super constructor with the corresponding arguments.
        super(LoadPolygonsToIRServerState, self).__init__(outcomes = ['done', 'failed'])

        self.exito_inicial=0

    def execute(self, userdata):
        # This method is called periodically while the state is active.
        print "Cargando poligonos-------->"

        
        if self.exito_inicial==1:
            return 'done'


        rospy.wait_for_service('/irobot_ir_data')
        try:

            client = rospy.ServiceProxy('/irobot_ir_data', IROBOT_ir_data)

            print "Loading defecto 1"
            request= IROBOT_ir_dataRequest()

            request.load_polygon=True

            poly1= Polygon()

            p0=Point32()
            p1=Point32()
            p2=Point32()
            p3=Point32()
            p4=Point32()
            p5=Point32()

            escala=6.0


            p0.x=8.0/escala-1
            p0.y=7.0/escala
            poly1.points.append(p0)

            p1.x=18.0/escala-1
            p1.y=8.0/escala
            poly1.points.append(p1)

            p2.x=24.0/escala-1
            p2.y=6.0/escala
            poly1.points.append(p2)

            p3.x=15.0/escala-1
            p3.y=3.0/escala
            poly1.points.append(p3)



            request.input_poly=poly1

            client(request)

            #----

            print "Loading defecto 2"
            request2= IROBOT_ir_dataRequest()

            request2.load_polygon=True

            poly2= Polygon()
            

            p0.x= 35.0/escala
            p0.y=10.0/escala
            poly2.points.append(p0)

            p1.x=38.5/escala
            p1.y=5.5/escala
            poly2.points.append(p1)

            p2.x=34.0/escala
            p2.y=2.9/escala
            poly2.points.append(p2)

            
            request2.input_poly=poly2

            client(request2)

            #----

            print "Loading defecto 3"
            request3= IROBOT_ir_dataRequest()

            request3.load_polygon=True

            poly3= Polygon()
            p=Point32()

            p0.x=15.5/escala
            p0.y=20.0/escala
            poly3.points.append(p0)

            p1.x=28.0/escala
            p1.y=21.0/escala
            poly3.points.append(p1)

            p2.x=35.0/escala
            p2.y=19.0/escala
            poly3.points.append(p2)

            p3.x=38.0/escala
            p3.y=15.0/escala
            poly3.points.append(p3)

            p4.x=32.0/escala
            p4.y=15.0/escala
            poly3.points.append(p4)

            p5.x=25.0/escala
            p5.y=18.0/escala
            poly3.points.append(p5)


            request3.input_poly=poly3


            client(request3)




            self.exito_inicial=1

            return 'done'
        except rospy.ServiceException, e:
            print "Service call failed: %s"%e
            return 'failed'


    def on_enter(self, userdata):
        # This method is called when the state becomes active, i.e. a transition from another state to this one is taken.
        # It is primarily used to start actions which are associated with this state.

        pass


    def on_exit(self, userdata):
        # This method is called when an outcome is returned and another state gets active.
        # It can be used to stop possibly running processes started by on_enter.

        pass # Nothing to do in this example.


    def on_start(self):
        # This method is called when the behavior is started.
        # If possible, it is generally better to initialize used resources in the constructor
        # because if anything failed, the behavior would not even be started.

        pass


    def on_stop(self):
        # This method is called whenever the behavior stops execution, also if it is cancelled.
        # Use this event to clean up things like claimed resources.

        pass # Nothing to do in this example.
        
