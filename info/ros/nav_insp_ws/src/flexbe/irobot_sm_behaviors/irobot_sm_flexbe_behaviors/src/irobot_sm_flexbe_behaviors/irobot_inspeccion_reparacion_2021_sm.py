#!/usr/bin/env python
# -*- coding: utf-8 -*-
###########################################################
#               WARNING: Generated code!                  #
#              **************************                 #
# Manual changes may get lost if file is generated again. #
# Only code inside the [MANUAL] tags will be kept.        #
###########################################################

from flexbe_core import Behavior, Autonomy, OperatableStateMachine, ConcurrencyContainer, PriorityContainer, Logger
from irobot_sm_flexbe_behaviors.inspection_sheet_sm import Inspection_sheetSM
from irobot_sm_flexbe_behaviors.irobot_eng_inspection_and_reparation_statemachine_sept19_sm import IROBOT_eng_inspection_and_reparation_StateMachine_Sept19SM
# Additional imports can be added inside the following tags
# [MANUAL_IMPORT]

# [/MANUAL_IMPORT]


'''
Created on Mon Feb 08 2021
@author: Sara Roos
'''
class irobot_inspeccion_reparacion_2021SM(Behavior):
	'''
	Lleva a cabo la inspeccion y reparación de una chapa de dimensiones conocidas.
	'''


	def __init__(self):
		super(irobot_inspeccion_reparacion_2021SM, self).__init__()
		self.name = 'irobot_inspeccion_reparacion_2021'

		# parameters of this behavior

		# references to used behaviors
		self.add_behavior(Inspection_sheetSM, 'Inspection_sheet')
		self.add_behavior(IROBOT_eng_inspection_and_reparation_StateMachine_Sept19SM, 'IROBOT_eng_inspection_and_reparation_StateMachine_Sept19')

		# Additional initialization code can be added inside the following tags
		# [MANUAL_INIT]
		
		# [/MANUAL_INIT]

		# Behavior comments:



	def create(self):
		# x:870 y:103, x:349 y:274
		_state_machine = OperatableStateMachine(outcomes=['finished', 'failed'])

		# Additional creation code can be added inside the following tags
		# [MANUAL_CREATE]
		
		# [/MANUAL_CREATE]


		with _state_machine:
			# x:138 y:85
			OperatableStateMachine.add('Inspection_sheet',
										self.use_behavior(Inspection_sheetSM, 'Inspection_sheet'),
										transitions={'finished': 'IROBOT_eng_inspection_and_reparation_StateMachine_Sept19', 'failed': 'failed'},
										autonomy={'finished': Autonomy.Inherit, 'failed': Autonomy.Inherit})

			# x:405 y:88
			OperatableStateMachine.add('IROBOT_eng_inspection_and_reparation_StateMachine_Sept19',
										self.use_behavior(IROBOT_eng_inspection_and_reparation_StateMachine_Sept19SM, 'IROBOT_eng_inspection_and_reparation_StateMachine_Sept19'),
										transitions={'finished': 'finished', 'failed': 'failed', 'failed2': 'failed', 'failed3': 'failed'},
										autonomy={'finished': Autonomy.Inherit, 'failed': Autonomy.Inherit, 'failed2': Autonomy.Inherit, 'failed3': Autonomy.Inherit})


		return _state_machine


	# Private functions can be added inside the following tags
	# [MANUAL_FUNC]
	
	# [/MANUAL_FUNC]
