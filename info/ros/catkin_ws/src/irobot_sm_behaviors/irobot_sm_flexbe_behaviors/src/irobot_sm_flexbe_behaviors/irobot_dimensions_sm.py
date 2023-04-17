#!/usr/bin/env python
# -*- coding: utf-8 -*-
###########################################################
#               WARNING: Generated code!                  #
#              **************************                 #
# Manual changes may get lost if file is generated again. #
# Only code inside the [MANUAL] tags will be kept.        #
###########################################################

from flexbe_core import Behavior, Autonomy, OperatableStateMachine, ConcurrencyContainer, PriorityContainer, Logger
from irobot_sm_flexbe_states.findfirstcorner_state import FindFirstCornerState as irobot_sm_flexbe_states__FindFirstCornerState
from irobot_sm_flexbe_states.obtaindimension import ObtainDimensionState as irobot_sm_flexbe_states__ObtainDimensionState
# Additional imports can be added inside the following tags
# [MANUAL_IMPORT]

# [/MANUAL_IMPORT]


'''
Created on Mon Nov 11 2019
@author: Sara Roos
'''
class IROBOT_dimensionsSM(Behavior):
	'''
	Get dimensions of the sheet
	'''


	def __init__(self):
		super(IROBOT_dimensionsSM, self).__init__()
		self.name = 'IROBOT_dimensions'

		# parameters of this behavior

		# references to used behaviors

		# Additional initialization code can be added inside the following tags
		# [MANUAL_INIT]
		
		# [/MANUAL_INIT]

		# Behavior comments:



	def create(self):
		# x:426 y:363, x:130 y:374
		_state_machine = OperatableStateMachine(outcomes=['finished', 'failed'], input_keys=['folder_path1', 'folder_path2'])
		_state_machine.userdata.folder_path1 = '/home/sara/imagenesDimensions0/'
		_state_machine.userdata.folder_path2 = '/home/sara/imagenesDimensions1/'

		# Additional creation code can be added inside the following tags
		# [MANUAL_CREATE]
		
		# [/MANUAL_CREATE]


		with _state_machine:
			# x:183 y:19
			OperatableStateMachine.add('FindCorners and GetImages',
										irobot_sm_flexbe_states__FindFirstCornerState(),
										transitions={'done': 'obtainDimensions', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off},
										remapping={'n_imgs1': 'n_imgs1', 'n_imgs2': 'n_imgs2'})

			# x:342 y:161
			OperatableStateMachine.add('obtainDimensions',
										irobot_sm_flexbe_states__ObtainDimensionState(),
										transitions={'done': 'finished', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off},
										remapping={'n_imgs1': 'n_imgs1', 'folder_path1': 'folder_path1', 'n_imgs2': 'n_imgs2', 'folder_path2': 'folder_path2', 'largo': 'large', 'ancho': 'width'})


		return _state_machine


	# Private functions can be added inside the following tags
	# [MANUAL_FUNC]
	
	# [/MANUAL_FUNC]
