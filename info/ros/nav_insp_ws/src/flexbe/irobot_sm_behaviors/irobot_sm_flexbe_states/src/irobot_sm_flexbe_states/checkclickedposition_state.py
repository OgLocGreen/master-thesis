#!/usr/bin/env python

import rospy

from flexbe_core import EventState, Logger

from geometry_msgs.msg import Pose2D, Point
from action_server_package.srv import *

'''
Created on 8.12.2018

@author: Alvaro Fernandez
'''

def areaInside3Points(P1, P2, P3):
	return 0.5*abs(P1.x*(P2.y - P3.y) + P2.x*(P3.y - P1.y) + P3.x*(P1.y - P2.y))

def areaRectangle (Pa, Pb, Pc, Pd):
	return 0.5*abs((Pa.y-Pc.y)*(Pd.x-Pb.x)+(Pb.y-Pd.y)*(Pa.x-Pc.x)) 

	
def isPinRectangle(r, P):
	'''
		r: A list of four points, each has a x- and a y- coordinate
		P: A point
	'''
	#Comprueba que punto esta dentro de un rectangulo.
	#El area del recatnagulo debe ser igual a la suma del area de los triangulos que se forman con el punto y los vertices
	#Vasadi eb https://martin-thoma.com/how-to-check-if-a-point-is-inside-a-rectangle/

	rect_area = areaRectangle(r[0], r[1], r[2], r[3])

	sum_area=0
	for i in xrange(0, 3):
		triang_i=areaInside3Points(P,r[i], r[i+1])
		sum_area=sum_area+triang_i

	sum_area=sum_area + areaInside3Points(P,r[0], r[3])


	if (abs(rect_area - sum_area) < 1) and (sum_area != 0):
		return True
	else:
		return False





class CheckClickedPosition_State(EventState):
	'''
	Evalua si la Pose2D que recibe se encuentra dentro de un area

	># input_pose2D  object		Posicion clicada.

	###> output_pose2D object		Posicion hacia la que debe dirigirse el robot.
	#> id_chapa 	int		Id de la chapa que se ha clicado

	<= inside_area 		El punto se encuentra dentro del area 

	<= outside_area		El punto se encuentra fuera del area 

	'''

	def __init__(self):
		# Declare outcomes, input_keys, and output_keys by calling the super constructor with the corresponding arguments.
		super(CheckClickedPosition_State, self).__init__(outcomes = ['inside_area', 'outside_area'],
												   				 input_keys=['input_pose2D'],
												   				 output_keys=['id_chapa'])

		# Store state parameter for later use.
		self._input_pose2D = Pose2D()
		#self._output_pose2D = Pose2D()
		
		

		self._inside = False
		self._id_chapa=-1


	def execute(self, userdata):
		# This method is called periodically while the state is active.
		# Main purpose is to check state conditions and trigger a corresponding outcome.
		# If no outcome is returned, the state will stay active.

		#userdata.output_pose2D = self._output_pose2D
		userdata.id_chapa=self._id_chapa

		if self._inside == True:
			return 'inside_area'
		else:
			return 'outside_area'

	def on_enter(self, userdata):
		# This method is called when the state becomes active, i.e. a transition from another state to this one is taken.
		# It is primarily used to start actions which are associated with this state.


		self._input_pose2D = userdata.input_pose2D #No se puede usar userdata en el co
		
		# The following code is just for illustrating how the behavior logger works.
		# Text logged by the behavior logger is sent to the operator and displayed in the GUI.

		#PROVISIONAL. SUSTITUIR POR OTRO METODO DE ENTRADA EN SU MOMENTO
		# rectangle=[	Point( 3, 3, 0),
		# 			Point( 3,-3, 0),
		# 			Point(-3,-3, 0),
		# 			Point(-3, 3, 0)]

		rospy.wait_for_service('chapa_storage')
		try:
			chapas_server = rospy.ServiceProxy('/chapa_storage', ChapaStorage)
			chapas_resp = chapas_server(0)
			n_chapas=chapas_resp.number_of_chapas
		except	rospy.ServiceException, e:
			print "Service call failed: %s"%e
			#METER ALGUN TIPO DE ERROR?

		for i in xrange(0,n_chapas):
			chapas_resp=chapas_server(i)
			rectangle=[	chapas_resp.coordA,
			            chapas_resp.coordB,
			            chapas_resp.coordC,
			            chapas_resp.coordD]
			id_chapa=i

			self._inside=isPinRectangle( rectangle, Point(self._input_pose2D.x, self._input_pose2D.y, 0))

			if self._inside == True :
				#De momento se la pose de la esquina A
				#self._output_pose2D.x=0.25*(chapas_resp.coordA.x+chapas_resp.coordB.x+chapas_resp.coordC.x+chapas_resp.coordD.x)
				#self._output_pose2D.y=0.25*(chapas_resp.coordA.y+chapas_resp.coordB.y+chapas_resp.coordC.y+chapas_resp.coordD.y)
				
				self._id_chapa=id_chapa				
				break



