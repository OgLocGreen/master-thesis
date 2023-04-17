#!/usr/bin/env python
import rospy

from flexbe_core import EventState, Logger

import roslib
from std_srvs.srv import EmptyRequest, Empty

import sys
sys.path.append('/home/irobot-user/irobot_qt_ws/devel/lib/python2.7/dist-packages')

from irobot_fcpp_simul.srv import IROBOT_ir_data, IROBOT_ir_dataRequest

class SetIRInputDataState(EventState):
	'''
	State that implements a client to the irobot ir storage service to set the input data.

	-- long_robotx
	-- long_roboty
	-- long_herrx
	-- long_herry
	-- tras_herrx
	-- tras_herry
	-- long_camx
	-- long_camy 
	-- tras_camx
	-- tras_camy,
	-- long_areax
	-- long_areay



	<= done 				Input data info set
	<= failed 				Input data info failed

	'''

	def __init__(self, long_robotx, long_roboty,
	      			  long_herrx, long_herry, tras_herrx, tras_herry,
	      			  long_camx, long_camy, tras_camx, tras_camy,
	      			  long_areax, long_areay, id_defect_repair, path_panorama):
		# Declare outcomes, input_keys, and output_keys by calling the super constructor with the corresponding arguments.
		super(SetIRInputDataState, self).__init__(outcomes = ['done', 'failed'])

		self._longrx=long_robotx
		self._longry=long_roboty

		self._longhx=long_herrx
		self._longhy=long_herry
		self._trashx=tras_herrx
		self._trashy=tras_herry

		self._longcx=long_camx
		self._longcy=long_camy
		self._trascx=tras_camx
		self._trascy=tras_camy

		self._longax=long_areax
		self._longay=long_areay

		self._id_defect_repair=id_defect_repair
		self._path_panorama=path_panorama




	def execute(self, userdata):
		# This method is called periodically while the state is active.
	    print "Cargando datos de entrada-------->"

	    exito_inicial=0
	    if exito_inicial==1:
	    	return 'done'


	    rospy.wait_for_service('/irobot_ir_data')
	    try:
	    	print "Loading data..."
	        client = rospy.ServiceProxy('/irobot_ir_data', IROBOT_ir_data)
	        request= IROBOT_ir_dataRequest()

	        request.load_inputdata=True

	        request.long_robotx=self._longrx
	        request.long_roboty=self._longry

	        request.long_herrx=self._longhx
	        request.long_herry=self._longhy
	        request.tras_herrx=self._trashx
	        request.tras_herry=self._trashy

	        request.long_camx=self._longcx
	        request.long_camy=self._longcy
	        request.tras_camx=self._trascx
	        request.tras_camy=self._trascy

	        request.long_areax=self._longax
	        request.long_areay=self._longay

		request.id_defect_repair=self._id_defect_repair
		request.path_panorama=self._path_panorama

	        client(request)

	        exito_inicial=1

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
		
