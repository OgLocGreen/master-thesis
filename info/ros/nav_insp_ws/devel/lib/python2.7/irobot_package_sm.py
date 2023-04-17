#!/usr/bin/env python
# -*- coding: utf-8 -*-
###########################################################
#               WARNING: Generated code!                  #
#              **************************                 #
# Manual changes may get lost if file is generated again. #
# Only code inside the [MANUAL] tags will be kept.        #
###########################################################

from flexbe_core import Behavior, Autonomy, OperatableStateMachine, ConcurrencyContainer, PriorityContainer, Logger
from irobot_sm_flexbe_behaviors.irobot_navigation_statemachine_feb19_sm import IROBOT_navigation_StateMachine_Feb19SM
from irobot_sm_flexbe_behaviors.irobot_eng_inspection_and_reparation_statemachine_sept19_sm import IROBOT_eng_inspection_and_reparation_StateMachine_Sept19SM
# Additional imports can be added inside the following tags
# [MANUAL_IMPORT]

# [/MANUAL_IMPORT]


'''
Created on Mon Jan 20 2020
@author: Sara
'''
class irobot_packageSM(Behavior):
	'''
	Juntar navegacion e inspeccion
	'''


	def __init__(self):
		super(irobot_packageSM, self).__init__()
		self.name = 'irobot_package'

		# parameters of this behavior

		# references to used behaviors
		self.add_behavior(IROBOT_navigation_StateMachine_Feb19SM, 'IROBOT_navigation_StateMachine_Feb19')
		self.add_behavior(IROBOT_eng_inspection_and_reparation_StateMachine_Sept19SM, 'IROBOT_eng_inspection_and_reparation_StateMachine_Sept19')

		# Additional initialization code can be added inside the following tags
		# [MANUAL_INIT]
		
		# [/MANUAL_INIT]

		# Behavior comments:



	def create(self):
		# x:786 y:84, x:184 y:315
		_state_machine = OperatableStateMachine(outcomes=['finished', 'failed'])
		_state_machine.userdata.folder_path1 = '/home/sara/imagenesDimensions0/'
		_state_machine.userdata.folder_path2 = '/home/sara/imagenesDimensions1/'

		# Additional creation code can be added inside the following tags
		# [MANUAL_CREATE]
		
		# [/MANUAL_CREATE]


		with _state_machine:
			# x:77 y:104
			OperatableStateMachine.add('IROBOT_navigation_StateMachine_Feb19',
										self.use_behavior(IROBOT_navigation_StateMachine_Feb19SM, 'IROBOT_navigation_StateMachine_Feb19'),
										transitions={'failed': 'failed', 'finished': 'IROBOT_eng_inspection_and_reparation_StateMachine_Sept19'},
										autonomy={'failed': Autonomy.Inherit, 'finished': Autonomy.Inherit})

			# x:378 y:101
			OperatableStateMachine.add('IROBOT_eng_inspection_and_reparation_StateMachine_Sept19',
										self.use_behavior(IROBOT_eng_inspection_and_reparation_StateMachine_Sept19SM, 'IROBOT_eng_inspection_and_reparation_StateMachine_Sept19'),
										transitions={'finished': 'finished', 'failed': 'failed', 'failed2': 'failed', 'failed3': 'failed'},
										autonomy={'finished': Autonomy.Inherit, 'failed': Autonomy.Inherit, 'failed2': Autonomy.Inherit, 'failed3': Autonomy.Inherit})


		return _state_machine


	# Private functions can be added inside the following tags
	# [MANUAL_FUNC]
	
	# [/MANUAL_FUNC]
