#!/usr/bin/env python

import rospy

from flexbe_core import EventState, Logger

from geometry_msgs.msg import PoseStamped, Pose2D
from tf.transformations import euler_from_quaternion

'''
Created on 27.11.2018

@author: Alvaro Fernandez
'''


class PoseStamped_Pose2D_ConversionState(EventState):
	'''
	Conversion de geometry_msg::PoseStamped a geometry_msg::Pose2D

	># input_posestamped  object		Input to the calculation function.

	#> output_pose2D object		The result of the calculation.

	<= done 		Posicion seleccionada

	'''

	def __init__(self):
		# Declare outcomes, input_keys, and output_keys by calling the super constructor with the corresponding arguments.
		super(PoseStamped_Pose2D_ConversionState, self).__init__(outcomes = ['done'],
												   				 input_keys=['input_posestamped'],
												   				 output_keys=['output_pose2D'])

		# Store state parameter for later use.
		self._posestamped = PoseStamped() 
		self._pose2D = Pose2D()



	def execute(self, userdata):
		# This method is called periodically while the state is active.
		# Main purpose is to check state conditions and trigger a corresponding outcome.
		# If no outcome is returned, the state will stay active.

		userdata.output_pose2D = self._pose2D

		return 'done'

	def on_enter(self, userdata):
		# This method is called when the state becomes active, i.e. a transition from another state to this one is taken.
		# It is primarily used to start actions which are associated with this state.


		self._posestamped = userdata.input_posestamped #No se uede usar userdata en el co
		# The following code is just for illustrating how the behavior logger works.
		# Text logged by the behavior logger is sent to the operator and displayed in the GUI.

		self._pose2D.x=self._posestamped.pose.position.x
		self._pose2D.y=self._posestamped.pose.position.y
		q = ( self._posestamped.pose.orientation.x,
			  self._posestamped.pose.orientation.y,
			  self._posestamped.pose.orientation.z,
			  self._posestamped.pose.orientation.w)
		euler=euler_from_quaternion(q)
		self._pose2D.theta=euler[2]


