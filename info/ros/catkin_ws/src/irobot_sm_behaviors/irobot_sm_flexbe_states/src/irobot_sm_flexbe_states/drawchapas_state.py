#!/usr/bin/env python
import rospy

from flexbe_core import EventState, Logger

from action_server_package.srv import *
from geometry_msgs.msg import Point, PolygonStamped
from time import sleep


class DrawChapasState(EventState):
	'''
	State that draws in rviz the spolygons storaged in ChapaStorage

	<= done 			
	<= failed

	'''

	def __init__(self):
		# Declare outcomes, input_keys, and output_keys by calling the super constructor with the corresponding arguments.
		super(DrawChapasState, self).__init__(outcomes = ['done', 'failed'])

		# Store state parameter for later use.
		#self._target_time = rospy.Duration(target_time)

		# The constructor is called when building the state machine, not when actually starting the behavior.
		# Thus, we cannot save the starting time now and will do so later.
		#self._start_time = None


	def execute(self, userdata):
		# This method is called periodically while the state is active.
		# Main purpose is to check state conditions and trigger a corresponding outcome.
		# If no outcome is returned, the state will stay active.

		# if rospy.Time.now() - self._start_time > self._target_time:
		# 	return 'continue' # One of the outcomes declared above.
		
		rospy.wait_for_service('chapa_storage')


		try:
			chapas_server = rospy.ServiceProxy('/chapa_storage', ChapaStorage)
			chapas_resp = chapas_server(0)
			n_chapas=chapas_resp.number_of_chapas
		except	rospy.ServiceException, e:
			print "Service call failed: %s"%e
			return 'failed'


		for i in xrange(0,n_chapas):
			chapas_resp=chapas_server(i)

			string_topic="chapa_id%s" % i
			pub = rospy.Publisher(string_topic, PolygonStamped, queue_size=10)
			
			polyStamp=PolygonStamped()

			polyStamp.header.frame_id="map"

			polyStamp.polygon.points.append(chapas_resp.coordA)
			polyStamp.polygon.points.append(chapas_resp.coordB)
			polyStamp.polygon.points.append(chapas_resp.coordC)
			polyStamp.polygon.points.append(chapas_resp.coordD)

			sleep(1)#Para asegurarse de que se publica
			for i in xrange(0,50):
				pub.publish(polyStamp)

		return 'done'

	def on_enter(self, userdata):
		# This method is called when the state becomes active, i.e. a transition from another state to this one is taken.
		# It is primarily used to start actions which are associated with this state.

		# The following code is just for illustrating how the behavior logger works.
		# Text logged by the behavior logger is sent to the operator and displayed in the GUI.

		# time_to_wait = (self._target_time - (rospy.Time.now() - self._start_time)).to_sec()

		# if time_to_wait > 0:
		# 	Logger.loginfo('Need to wait for %.1f seconds.' % time_to_wait)
		pass


	def on_exit(self, userdata):
		# This method is called when an outcome is returned and another state gets active.
		# It can be used to stop possibly running processes started by on_enter.

		pass # Nothing to do in this example.


	def on_start(self):
		# This method is called when the behavior is started.
		# If possible, it is generally better to initialize used resources in the constructor
		# because if anything failed, the behavior would not even be started.

		# In this example, we use this event to set the correct start time.
		#self._start_time = rospy.Time.now()
		pass

	def on_stop(self):
		# This method is called whenever the behavior stops execution, also if it is cancelled.
		# Use this event to clean up things like claimed resources.

		pass # Nothing to do in this example.
		
