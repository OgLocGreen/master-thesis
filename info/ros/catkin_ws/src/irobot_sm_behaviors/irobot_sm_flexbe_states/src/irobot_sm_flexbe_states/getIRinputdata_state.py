#!/usr/bin/env python
import rospy

from flexbe_core import EventState, Logger

import roslib
from std_srvs.srv import EmptyRequest, Empty
import octomap_msgs.srv

class GetIRInputDataState(EventState):
	'''
	State that implements a client to the "/octomap_server/reset" service.

	<= done 				Octomap has been sucesfully reset
	<= failed 				Octomap has not been sucesfully reset

	'''

	def __init__(self):
		# Declare outcomes, input_keys, and output_keys by calling the super constructor with the corresponding arguments.
		super(ResetOctomapState, self).__init__(outcomes = ['done', 'failed'])




	def execute(self, userdata):
		# This method is called periodically while the state is active.
	
	    rospy.wait_for_service('/octomap_server/reset')
	    try:
	        client = rospy.ServiceProxy('/octomap_server/reset', Empty)
	        request= EmptyRequest()
	        client(request)
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
		
