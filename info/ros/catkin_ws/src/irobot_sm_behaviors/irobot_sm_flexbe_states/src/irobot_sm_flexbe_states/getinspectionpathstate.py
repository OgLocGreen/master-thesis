#!/usr/bin/env python

import rospy

from flexbe_core import EventState, Logger
from flexbe_core.proxy import ProxyActionClient

from geometry_msgs.msg import PoseArray


import sys
sys.path.append('/home/irobot-user/irobot_qt_ws/devel/lib/python2.7/dist-packages')

from irobot_fcpp_simul.srv import IROBOT_ir_data, IROBOT_ir_dataRequest

class GetInspectionPathState(EventState):
    '''
    State to active the trapezoidal decomposition in IR srv


    <= done                 Trap decomp activated
    <= failed               Trap decomp failed

    '''

    def __init__(self):
        # Declare outcomes, input_keys, and output_keys by calling the super constructor with the corresponding arguments.
        super(GetInspectionPathState, self).__init__(outcomes = ['done', 'failed'], output_keys=['path'])

        #self._path = PoseArray()
        self._path =[]

    def execute(self, userdata):
        # This method is called periodically while the state is active.
        userdata.path = self._path

        return 'done'

    def on_enter(self, userdata):
        # This method is called when the state becomes active, i.e. a transition from another state to this one is taken.
        # It is primarily used to start actions which are associated with this state.

        rospy.wait_for_service('/irobot_ir_data')

        try:
            client = rospy.ServiceProxy('/irobot_ir_data', IROBOT_ir_data)

            request= IROBOT_ir_dataRequest()

            request.get_inspection_path=True

            response=client(request)

            self._path=response.inspection_i_paths
            
        except rospy.ServiceException, e:
            print "Service call failed: %s"%e
            return 'failed'


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
        
