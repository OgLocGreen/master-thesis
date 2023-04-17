#!/usr/bin/env python
import rospy


from flexbe_core import EventState, Logger
from flexbe_core.proxy import ProxyActionClient

import roslib

# example import of required action

import sys
sys.path.append('/home/irobot-user/irobot_qt_ws/devel/lib/python2.7/dist-packages')

from irobot_fcpp_simul.srv import IROBOT_ir_data, IROBOT_ir_dataRequest



class ComputeRectangleFCPPActionState(EventState):
    '''
    State that send a msg to the srv to compute the fcpp of a rectangle area.


    
    -- zone_id  int     dependiendo de orientacion: 0, 90,270, 180

    ># fcpp_type char   'c' inspeccion 

    <= done         FCPP completed.

    <= failed       FCPP failed.
    '''

    def __init__(self, zone_id):
        # See example_state.py for basic explanations.
        super(ComputeRectangleFCPPActionState, self).__init__(outcomes = ['done','failed'])


        self._zone_id=zone_id

        if zone_id==0:
            self._zone_id=0
        if zone_id==90 | zone_id==1:
            self._zone_id=1
        if zone_id==180 | zone_id==2:
            self._zone_id=2
        if zone_id==270 | zone_id==3:
            self._zone_id=3



    def execute(self, userdata):
        # This method is called periodically while the state is active.
        print "Solicitando calculo de path de zona-------->"

        exito_inicial=0
        if exito_inicial==1:
            return 'done'


        rospy.wait_for_service('/irobot_ir_data')
        try:
            print "Loading data..."
            client = rospy.ServiceProxy('/irobot_ir_data', IROBOT_ir_data)
            request= IROBOT_ir_dataRequest()

            #request.compute_fcpp_zone_i=True
	    request.compute_fcpp_inspection_zone_i=True

            request.id_zona=self._zone_id

            client(request)

            exito_inicial=1

            return 'done'
        except rospy.ServiceException, e:
            print "Service call failed: %s"%e
            return 'failed'
        

    def on_enter(self, userdata):
        # When entering this state, we send the action goal once to let the robot start its work.

        # As documented above, we get the specification of which dishwasher to use as input key.
        # This enables a previous state to make this decision during runtime and provide the ID as its own output key.
        #n_degrees = userdata.n_degrees

        pass

    def on_exit(self, userdata):
        # Make sure that the action is not running when leaving this state.
        # A situation where the action would still be active is for example when the operator manually triggers an outcome.

        pass
        
