#!/usr/bin/env python

import rospy

from flexbe_core import EventState, Logger

from geometry_msgs.msg import Pose2D
from action_server_package.srv import *
from aux_controllers.srv import *
import tf2_ros
from geometry_msgs.msg import TransformStamped

'''
Created on 09.01.2019

@author: Alvaro Fernandez
'''

import numpy as np



class GetSimpleInspectionPoses_State(EventState):
	'''
	State that receive a chapa id and returns the the middle pose and generates the frame in his coord A.

	--retroceso			Distancia respecto a chapa

	># id  object		Input to the calculation function.

	#> output_pose0 	object		Pose a inicial
	#> output_pose1 	double		Largo de la chapa.
	#> output_poselong 	double		Ancho de la chapa.

	<= done 		fin 

	'''

	def __init__(self, retroceso):
		# Declare outcomes, input_keys, and output_keys by calling the super constructor with the corresponding arguments.
		super(GetSimpleInspectionPoses_State, self).__init__(outcomes = ['done'],
												   	  input_keys=['id'],
												   	  output_keys=['output_pose0', 'output_pose1', 'output_poselong'])

		self._retroceso = retroceso
		# Store state parameter for later use.
		self._output_pose0 = Pose2D()
		self._output_pose1 = Pose2D()
		self._output_poselong = Pose2D()

	def execute(self, userdata):
		# This method is called periodically while the state is active.
		# Main purpose is to check state conditions and trigger a corresponding outcome.
		# If no outcome is returned, the state will stay active.

		userdata.output_pose0 = self._output_pose0
		userdata.output_pose1 = self._output_pose1
		userdata.output_poselong = self._output_poselong

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

		#Pose1. Pose entre A y B

		##y_media=0.5*(chapas_resp.coordA.y+chapas_resp.coordB.y) - chapas_resp.coordA.y#referido a la esquinaA

		self._output_pose0.x=0.0
		self._output_pose0.y=chapas_resp.width_chapa*0.5
		self._output_pose0.theta=0.0

		#Pose0. Retrasada una cierta distancia
		self._output_pose1.x=-self._retroceso
		self._output_pose1.y=chapas_resp.width_chapa*0.5
		self._output_pose1.theta=0.0		 

		#PoseLong. Pose para recorrer la longitud de la chapa
		self._output_poselong.x=chapas_resp.long_chapa
		self._output_poselong.y=chapas_resp.width_chapa*0.5
		self._output_poselong.theta=0.0