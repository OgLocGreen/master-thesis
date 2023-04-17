#!/usr/bin/env python
from flexbe_core import EventState, Logger
from flexbe_core.proxy import ProxyActionClient

from inspection_realsense.msg import stopRobotAction, stopRobotGoal, stopRobotFeedback

import os

"""
Created on 3/12/2020

@author: Sara Roos
"""

class OperatorDecisionStateInspection(EventState):
	'''
	Implements a state where the operator has to manually choose an outcome.
	Autonomy Level of all outcomes should be set to Full, because this state is not able to choose an outcome on its own.
	Only exception is the suggested outcome, which will be returned immediately by default.
	This state can be used to create alternative execution paths by setting the suggestion to High autonomy instead of Full.

	-- outcomes     string[]    A list of all possible outcomes of this state.
	-- hint         string      Text displayed to the operator to give instructions how to decide.
	-- suggestion   string      The outcome which is suggested. Will be returned if the level of autonomy is high enough.

	'''


	def __init__(self):
		'''
		Constructor
		'''
		super(OperatorDecisionStateInspection, self).__init__(outcomes=['parar','failed'])

		self._topic = 'stopRobot' #Aqui mismo topic que en el server
		self._client = ProxyActionClient({self._topic: stopRobotAction}) # pass required clients as dict (topic: type)


		# It may happen that the action client fails to send the action goal.
		self._error = False
		
		
	def execute(self, userdata):
		'''
		Execute this state
		'''
		# Create the goal.
		goal = stopRobotGoal()
		goal.stop_robot = True


		# Send the goal.
		self._error = False # make sure to reset the error state since a previous state execution might have failed
		try:
			self._client.send_goal(self._topic, goal)
		except Exception as e:
			# Since a state failure not necessarily causes a behavior failure, it is recommended to only print warnings, not errors.
			# Using a linebreak before appending the error log enables the operator to collapse details in the GUI.
			Logger.logwarn('Failed to send the ExecutePath command:\n%s' % str(e))
			self._error = True

		if self._error:
			return 'failed'
		#if self._suggestion is not None and self._my_outcomes.count(self._suggestion) > 0:
		#	return self._suggestion

		os.system("rosnode kill /findinitialpose")
		os.system("rosnode kill /moveforward")
		os.system("rosnode kill /movebackward")
		os.system("rosnode kill /moveleftstep")
		os.system("rosnode kill /captureImages")	
		os.system("rosnode kill /repub_cmd_vel")	
	
	def on_enter(self, userdata):
		# Create the goal.
		goal = stopRobotGoal()
		goal.stop_robot = True


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


	#	os.system("gnome-terminal -x rosrun inspection_realsense findinitialpose_actionserver")
	#	os.system("gnome-terminal -x rosrun inspection_realsense moveforward_actionserver")
	#	os.system("gnome-terminal -x rosrun inspection_realsense movebackward_actionserver")
	#	os.system("gnome-terminal -x rosrun inspection_realsense moveleftstep_actionserver")
	#	os.system("gnome-terminal -x rosrun inspection_realsense captureImages_actionserver")
	#	os.system("gnome-terminal -x rosrun inspection_realsense repub_cmd_vel")
		
