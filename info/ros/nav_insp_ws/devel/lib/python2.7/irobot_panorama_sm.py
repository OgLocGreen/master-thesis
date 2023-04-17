#!/usr/bin/env python
# -*- coding: utf-8 -*-
###########################################################
#               WARNING: Generated code!                  #
#              **************************                 #
# Manual changes may get lost if file is generated again. #
# Only code inside the [MANUAL] tags will be kept.        #
###########################################################

from flexbe_core import Behavior, Autonomy, OperatableStateMachine, ConcurrencyContainer, PriorityContainer, Logger
from irobot_sm_flexbe_states.getImages import GetImagesState
from irobot_sm_flexbe_states.getPartialPanorama import GetPartialPanoramaState
# Additional imports can be added inside the following tags
# [MANUAL_IMPORT]

# [/MANUAL_IMPORT]


'''
Created on Mon Dec 02 2019
@author: Sara Roos
'''
class IROBOT_panoramaSM(Behavior):
	'''
	Get images and make panorama
	'''


	def __init__(self):
		super(IROBOT_panoramaSM, self).__init__()
		self.name = 'IROBOT_panorama'

		# parameters of this behavior

		# references to used behaviors

		# Additional initialization code can be added inside the following tags
		# [MANUAL_INIT]
		
		# [/MANUAL_INIT]

		# Behavior comments:



	def create(self):
		# x:448 y:360, x:130 y:365
		_state_machine = OperatableStateMachine(outcomes=['finished', 'failed'])
		_state_machine.userdata.folder_path = "/home/sara/Documentos/imagenes1/"
		_state_machine.userdata.calib_path = "/home/sara/data.yml"
		_state_machine.userdata.id_marker = 9

		# Additional creation code can be added inside the following tags
		# [MANUAL_CREATE]
		
		# [/MANUAL_CREATE]


		with _state_machine:
			# x:131 y:121
			OperatableStateMachine.add('getImages',
										GetImagesState(),
										transitions={'done': 'getPartialPanorama', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off},
										remapping={'folder_path': 'folder_path', 'calib_path': 'calib_path', 'id_marker': 'id_marker', 'n_imgs': 'n_imgs'})

			# x:387 y:62
			OperatableStateMachine.add('getPartialPanorama',
										GetPartialPanoramaState(),
										transitions={'done': 'finished', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off},
										remapping={'folder_path': 'folder_path'})


		return _state_machine


	# Private functions can be added inside the following tags
	# [MANUAL_FUNC]
	
	# [/MANUAL_FUNC]
