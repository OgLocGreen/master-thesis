#!/usr/bin/env python
import rospy

from flexbe_core import EventState, Logger

import roslib


import sys
sys.path.append('/home/irobot-user/irobot_qt_ws/devel/lib/python2.7/dist-packages')

from irobot_fcpp_simul.srv import IROBOT_ir_data, IROBOT_ir_dataRequest

class ComputeIRPolygonDecompositionState(EventState):
    '''
    State to active the trapezoidal decomposition in IR srv


    <= done                 Trap decomp activated
    <= failed               Trap decomp failed

    '''

    def __init__(self):
        # Declare outcomes, input_keys, and output_keys by calling the super constructor with the corresponding arguments.
        super(ComputeIRPolygonDecompositionState, self).__init__(outcomes = ['done', 'failed'])

        self.exito_inicial=0

    def execute(self, userdata):
        # This method is called periodically while the state is active.
        print "Activando descomposicion trapezoidal -------->"

        
        if self.exito_inicial==1:
            return 'done'


        rospy.wait_for_service('/irobot_ir_data')
        try:

            client = rospy.ServiceProxy('/irobot_ir_data', IROBOT_ir_data)

            request= IROBOT_ir_dataRequest()

            request.get_defect_i=True

            client(request)

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
        
