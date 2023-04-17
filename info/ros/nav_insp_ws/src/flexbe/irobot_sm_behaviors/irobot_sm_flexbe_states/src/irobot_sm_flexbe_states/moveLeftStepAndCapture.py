#!/usr/bin/env python
from flexbe_core import EventState, Logger
from flexbe_core.proxy import ProxyActionClient

# example import of required action
from inspection_realsense.msg import moveLeftStepAction, moveLeftStepGoal, captureImagesAction, captureImagesGoal


"""
Created on 3/12/2020

@author: Sara Roos
"""


class moveLeftStepAndCapture(EventState):
	'''
	State to find the initial pose for the inspection

	-- pathplanning_vel 		double

	<= done 		Rotation completed.

	<= failed 		Rotation failed.
	'''

	def __init__(self, vel, step):
		# See example_state.py for basic explanations.
		super(moveLeftStepAndCapture, self).__init__(outcomes = ['done','failed'], input_keys=['folder_path'])
	
		self._vel = vel 
		self._step = step
 
		# Create the action client when building the behavior.
		# This will cause the behavior to wait for the client before starting execution
		# and will trigger a timeout error if it is not available.
		# Using the proxy client provides asynchronous access to the result and status
		# and makes sure only one client is used, no matter how often this state is used in a behavior.
		self._topic = 'moveLeftStep' #Aqui mismo topic que en el server
		self._client = ProxyActionClient({self._topic: moveLeftStepAction}) # pass required clients as dict (topic: type)

		self._topic_i = 'captureImages' #Mismo nombre que en el server
		self._client_i = ProxyActionClient({self._topic_i: captureImagesAction})

		# It may happen that the action client fails to send the action goal.
		self._error = False
		self._error_i = False

	def execute(self, userdata):
		# While this state is active, check if the action has been finished and evaluate the result.

		# Check if the client failed to send the goal.
		if self._error:
			return 'failed'

		if self._error_i:
			return 'failed'

		# Check if the action has been finished
		if self._client.has_result(self._topic):
			result = self._client.get_result(self._topic)

			# In this example, we also provide the amount of cleaned dishes as output key.
			#userdata.n_degrees = final_yaw
			self._client_i.cancel(self._topic_i)
			return 'done'

		# If the action has not yet finished, no outcome will be returned and the state stays active.
		

	def on_enter(self, userdata):
		# When entering this state, we send the action goal once to let the robot start its work.

		# As documented above, we get the specification of which dishwasher to use as input key.
		# This enables a previous state to make this decision during runtime and provide the ID as its own output key.
		#n_degrees = userdata.n_degrees

		# Create the goal.
		goal = moveLeftStepGoal()
		goal.vel = self._vel
		goal.step = self._step

		goal_i = captureImagesGoal()
		goal_i.folder_path.data = userdata.folder_path


		# Send the goal.
		self._error = False # make sure to reset the error state since a previous state execution might have failed
		try:
			self._client.send_goal(self._topic, goal)
		except Exception as e:
			# Since a state failure not necessarily causes a behavior failure, it is recommended to only print warnings, not errors.
			# Using a linebreak before appending the error log enables the operator to collapse details in the GUI.
			Logger.logwarn('Failed to send the moveLeftStep command:\n%s' % str(e))
			self._error = True


		# Send the goal i.
		self._error_i = False # make sure to reset the error state since a previous state execution might have failed
		try:
			self._client_i.send_goal(self._topic_i, goal_i)
		except Exception as e:
			# Since a state failure not necessarily causes a behavior failure, it is recommended to only print warnings, not errors.
			# Using a linebreak before appending the error log enables the operator to collapse details in the GUI.
			Logger.logwarn('Failed to send the getImages command:\n%s' % str(e))
			self._error_i = True



	def on_exit(self, userdata):
		# Make sure that the action is not running when leaving this state.
		# A situation where the action would still be active is for example when the operator manually triggers an outcome.

		if not self._client.has_result(self._topic):
			self._client.cancel(self._topic)
			self._client_i.cancel(self._topic_i)
			Logger.loginfo('Cancelled active action goal.')
		