#!/usr/bin/env python
# -*- coding: utf-8 -*-
###########################################################
#               WARNING: Generated code!                  #
#              **************************                 #
# Manual changes may get lost if file is generated again. #
# Only code inside the [MANUAL] tags will be kept.        #
###########################################################

from flexbe_core import Behavior, Autonomy, OperatableStateMachine, ConcurrencyContainer, PriorityContainer, Logger
from irobot_sm_flexbe_states.executerectanglefcpp_action_state import ExecuteRectangleFCPPActionState as irobot_sm_flexbe_states__ExecuteRectangleFCPPActionState
from irobot_sm_flexbe_states.executepath_action_state import ExecutePathActionState
from irobot_sm_flexbe_states.getImages import GetImagesState
# Additional imports can be added inside the following tags
# [MANUAL_IMPORT]

# [/MANUAL_IMPORT]


'''
Created on Wed Dec 04 2019
@author: Sara Roos
'''
class irobot_inspection_descentralizedSM(Behavior):
	'''
	Coordinar inspección y reparación. Pero descentralizado
	'''


	def __init__(self):
		super(irobot_inspection_descentralizedSM, self).__init__()
		self.name = 'irobot_inspection_descentralized'

		# parameters of this behavior

		# references to used behaviors

		# Additional initialization code can be added inside the following tags
		# [MANUAL_INIT]
		
		# [/MANUAL_INIT]

		# Behavior comments:



	def create(self):
		# x:636 y:443, x:210 y:417
		_state_machine = OperatableStateMachine(outcomes=['finished', 'failed'])
		_state_machine.userdata.folder_path = "/home/sara/Documentos/imagenesPanorama/"
		_state_machine.userdata.calib_path = "/home/sara/data.yml"
		_state_machine.userdata.id_marker = 9
		_state_machine.userdata.zone_id = 0
		_state_machine.userdata.fcpp_type = 'c'

		# Additional creation code can be added inside the following tags
		# [MANUAL_CREATE]
		
		# [/MANUAL_CREATE]

		# x:30 y:478, x:130 y:478, x:230 y:478, x:330 y:478, x:430 y:478, x:530 y:478
		_sm_path_and_image_0_0 = ConcurrencyContainer(outcomes=['finished', 'failed'], input_keys=['folder_path', 'calib_path', 'marker_id', 'path'], conditions=[
										('finished', [('execute path 0', 'done'), ('getImage 0', 'done')]),
										('failed', [('execute path 0', 'failed')]),
										('failed', [('getImage 0', 'failed')])
										])

		with _sm_path_and_image_0_0:
			# x:83 y:169
			OperatableStateMachine.add('execute path 0',
										ExecutePathActionState(),
										transitions={'done': 'finished', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off},
										remapping={'path': 'path'})

			# x:347 y:82
			OperatableStateMachine.add('getImage 0',
										GetImagesState(),
										transitions={'done': 'finished', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off},
										remapping={'folder_path': 'folder_path', 'calib_path': 'calib_path', 'id_marker': 'marker_id'})



		with _state_machine:
			# x:77 y:136
			OperatableStateMachine.add('ExecuteRectangle0',
										irobot_sm_flexbe_states__ExecuteRectangleFCPPActionState(),
										transitions={'done': 'Path and image 0', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off},
										remapping={'zone_id': 'zone_id', 'fcpp_type': 'fcpp_type', 'path': 'path'})

			# x:409 y:90
			OperatableStateMachine.add('Path and image 0',
										_sm_path_and_image_0_0,
										transitions={'finished': 'finished', 'failed': 'failed'},
										autonomy={'finished': Autonomy.Inherit, 'failed': Autonomy.Inherit},
										remapping={'folder_path': 'folder_path', 'calib_path': 'calib_path', 'marker_id': 'id_marker', 'path': 'path'})


		return _state_machine


	# Private functions can be added inside the following tags
	# [MANUAL_FUNC]
	
	# [/MANUAL_FUNC]
