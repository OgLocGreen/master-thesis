#!/usr/bin/env python

import rospy

from flexbe_core import EventState, Logger

from geometry_msgs.msg import Pose2D
from action_server_package.srv import *
from aux_controllers.srv import *
import tf
import tf2_ros
from geometry_msgs.msg import TransformStamped

'''
Created on 12.12.2018

@author: Alvaro Fernandez
'''
import math
import numpy as np



class GetChapaNavParams_State(EventState):
	'''
	State that receive a chapa id and returns the the middle pose and generates the frame in his coord A.

	># id  object		Input to the calculation function.

	#> output_pose2D 	object		Pose a la que navegar con move_base.
	#> output_long 		double		Largo de la chapa.
	#> output_width 	double		Ancho de la chapa.

	<= done 		fin 

	'''

	def __init__(self):
		# Declare outcomes, input_keys, and output_keys by calling the super constructor with the corresponding arguments.
		super(GetChapaNavParams_State, self).__init__(outcomes = ['done'],
												   	  input_keys=['id'],
												   	  output_keys=['output_pose2D', 'output_long', 'output_width'])

		# Store state parameter for later use.
		self._output_pose2D = Pose2D()
		self._output_long = 0.0
		self._output_width = 0.0

	def execute(self, userdata):
		# This method is called periodically while the state is active.
		# Main purpose is to check state conditions and trigger a corresponding outcome.
		# If no outcome is returned, the state will stay active.

		userdata.output_pose2D = self._output_pose2D
		userdata.output_long = self._output_long
		userdata.output_width = self._output_width

		return 'done'

	def on_enter(self, userdata):
		# This method is called when the state becomes active, i.e. a transition from another state to this one is taken.
		# It is primarily used to start actions which are associated with this state.
		chapa_id=userdata.id

		rospy.wait_for_service('chapa_storage')
		try:
			chapas_server = rospy.ServiceProxy('/chapa_storage', ChapaStorage)
			chapas_resp = chapas_server(chapa_id)
		except	rospy.ServiceException, e:
			print "Service call failed: %s"%e

		#Obtiene el largo y ancho de la chapa
		self._output_long=chapas_resp.long_chapa
		self._output_width=chapas_resp.width_chapa

		#Calcula el punto medio de la chapa
		#self._output_pose2D.x=0.25*(chapas_resp.coordA.x+chapas_resp.coordB.x+chapas_resp.coordC.x+chapas_resp.coordD.x)
		#self._output_pose2D.y=0.25*(chapas_resp.coordA.y+chapas_resp.coordB.y+chapas_resp.coordC.y+chapas_resp.coordD.y)
		#Para simular mas rapido devolvemos coordenada A
		self._output_pose2D.x=0.5*(chapas_resp.coordA.x+chapas_resp.coordB.x)
		self._output_pose2D.y=0.5*(chapas_resp.coordA.y+chapas_resp.coordB.y)


		#Genera el frame en la coord A de la chapa


		R=[ [chapas_resp.coordD.x-chapas_resp.coordA.x,  chapas_resp.coordB.x-chapas_resp.coordA.x,  0,  0],
			[chapas_resp.coordD.y-chapas_resp.coordA.y,  chapas_resp.coordB.y-chapas_resp.coordA.y,  0,  0],
			[		0			 					  ,			0								  ,  1,  0],
			[		0			 					  ,			0								  ,  0,  1]]	
		
		euler = tf.transformations.euler_from_matrix(R)

		self._output_pose2D.theta=euler[2]


		rospy.wait_for_service('frame_service')
		try:
			frame_server = rospy.ServiceProxy('/frame_service', SetFrame)
			chapas_resp = frame_server( False,
										chapas_resp.coordA.x, chapas_resp.coordA.y, chapas_resp.coordA.z,
										euler[0], euler[1], euler[2])
		except	rospy.ServiceException, e:
			print "Service call failed: %s"%e
			#return 'failed'
