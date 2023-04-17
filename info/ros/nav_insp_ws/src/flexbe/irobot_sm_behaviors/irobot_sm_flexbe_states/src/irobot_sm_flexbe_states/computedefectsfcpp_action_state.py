#!/usr/bin/env python
import rospy


from flexbe_core import EventState, Logger
from flexbe_core.proxy import ProxyActionClient

import roslib

# example import of required action

import sys
sys.path.append('/home/irobot-user/irobot_qt_ws/devel/lib/python2.7/dist-packages')

from irobot_fcpp_simul.srv import IROBOT_ir_data, IROBOT_ir_dataRequest



class ComputeDefectsFCPPActionState(EventState):
    '''
    State that send a msg to the srv to compute the fcpp of all the defects.


    
    -- zone_id  int     dependiendo de orientacion: 0, 90,270, 180

    ># fcpp_type char   'c' inspeccion 

    <= done         FCPP completed.

    <= failed       FCPP failed.
    '''

    def __init__(self):
        # See example_state.py for basic explanations.
        super(ComputeDefectsFCPPActionState, self).__init__(outcomes = ['done','failed'])



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

            request.get_defect_i=True


            response=client(request)

            for i in range(0, response.n_defectos):
                request_i= IROBOT_ir_dataRequest()

                request_i.compute_fcpp_defect_i=True
                request_i.id_defecto=i


                client(request_i)

                print "Calculado path para un defecto"


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
        
