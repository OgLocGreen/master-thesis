#!/usr/bin/env python

import rospy

from flexbe_core import EventState, Logger
from flexbe_core.proxy import ProxyActionClient

from geometry_msgs.msg import PoseArray

# example import of required action

import sys
sys.path.append('/home/irobot-user/irobot_qt_ws/devel/lib/python2.7/dist-packages')

from irobot_fcpp_simul.msg import ExecutePathAction, ExecutePathGoal, ExecutePathFeedback
from irobot_inspection_pckg.msg import getImagesAction, getImagesGoal


class ExecuteRepairPathActionState(EventState):
	'''
	State that activate the action to execute the movements to execute a path.


	=>path

	<= done 		FCPP completed.

	<= failed 		FCPP failed.
	'''

	def __init__(self):
		# See example_state.py for basic explanations.
		super(ExecuteRepairPathActionState, self).__init__(outcomes = ['done','failed'], input_keys=['path'])


		# Create the action client when building the behavior.
		# This will cause the behavior to wait for the client before starting execution
		# and will trigger a timeout error if it is not available.
		# Using the proxy client provides asynchronous access to the result and status
		# and makes sure only one client is used, no matter how often this state is used in a behavior.
		self._topic = 'executepath_action' #Aqui mismo topic que en el server
		self._client = ProxyActionClient({self._topic: ExecutePathAction}) # pass required clients as dict (topic: type)
		
		


		# It may happen that the action client fails to send the action goal.
		self._error = False


	def execute(self, userdata):
		# While this state is active, check if the action has been finished and evaluate the result.


		# Check if the client failed to send the goal.
		if self._error:
			return 'failed'


				
		# Check if the action has been finished
		if self._client.has_result(self._topic):
			# In this example, we also provide the amount of cleaned dishes as output key.
			#userdata.n_degrees = final_yaw


			return 'done'


		# If the action has not yet finished, no outcome will be returned and the state stays active.
		

	def on_enter(self, userdata):
		# When entering this state, we send the action goal once to let the robot start its work.

		# As documented above, we get the specification of which dishwasher to use as input key.
		# This enables a previous state to make this decision during runtime and provide the ID as its own output key.
		#n_degrees = userdata.n_degrees


		# Create the goal.
		print "ON ENTER"
		goal = ExecutePathGoal()
		goal.path = userdata.path

	


		# Send the goal.
		self._error = False # make sure to reset the error state since a previous state execution might have failed
		try:
			self._client.send_goal(self._topic, goal)
		except Exception as e:
			# Since a state failure not necessarily causes a behavior failure, it is recommended to only print warnings, not errors.
			# Using a linebreak before appending the error log enables the operator to collapse details in the GUI.
			Logger.logwarn('Failed to send the ExecutePath command:\n%s' % str(e))
			self._error = True


	

	def on_exit(self, userdata):
		# Make sure that the action is not running when leaving this state.
		# A situation where the action would still be active is for example when the operator manually triggers an outcome.
		if not self._client.has_result(self._topic):
			self._client.cancel(self._topic)
			Logger.loginfo('Cancelled active action goal.')



		
