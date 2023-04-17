#!/usr/bin/env python
# -*- coding: utf-8 -*-
###########################################################
#               WARNING: Generated code!                  #
#              **************************                 #
# Manual changes may get lost if file is generated again. #
# Only code inside the [MANUAL] tags will be kept.        #
###########################################################

from flexbe_core import Behavior, Autonomy, OperatableStateMachine, ConcurrencyContainer, PriorityContainer, Logger
from flexbe_states.wait_state import WaitState as flexbe_states__WaitState
from irobot_sm_flexbe_states.getdefectpathstate import GetDefectPathState
from irobot_sm_flexbe_states.executepath_repair_action_state import ExecuteRepairPathActionState
from flexbe_states.operator_decision_state import OperatorDecisionState
from irobot_sm_flexbe_states.computedefectsfcpp_action_state import ComputeDefectsFCPPActionState
from irobot_sm_flexbe_states.computeirpolygondecomposition_state import ComputeIRPolygonDecompositionState
from irobot_sm_flexbe_states.loadpolysprovisional_state import LoadPolygonsToIRServerState
from irobot_sm_flexbe_states.setIRinputdata_state import SetIRInputDataState
from irobot_sm_flexbe_states.computeworkingzones_state import ComputeWorkingZonesState
# Additional imports can be added inside the following tags
# [MANUAL_IMPORT]

# [/MANUAL_IMPORT]


'''
Created on Fri Dec 11 2020
@author: Sara Roos
'''
class reparation_sheetSM(Behavior):
	'''
	Reparación defectos
	'''


	def __init__(self):
		super(reparation_sheetSM, self).__init__()
		self.name = 'reparation_sheet'

		# parameters of this behavior

		# references to used behaviors

		# Additional initialization code can be added inside the following tags
		# [MANUAL_INIT]
		
		# [/MANUAL_INIT]

		# Behavior comments:



	def create(self):
		long_robotx = 0.6
		long_roboty = 0.6
		long_herrx = 0.8
		long_herry = 0.8
		long_camx = 1
		long_camy = 1
		tras_camx = 40
		tras_camy = 40
		long_areax = 3
		long_areay = 2.5
		tras_herrx = 70
		tras_herry = 60
		# x:1181 y:71, x:540 y:578
		_state_machine = OperatableStateMachine(outcomes=['finished', 'failed'])

		# Additional creation code can be added inside the following tags
		# [MANUAL_CREATE]
		
		# [/MANUAL_CREATE]


		with _state_machine:
			# x:53 y:42
			OperatableStateMachine.add('Buscar defectos',
										flexbe_states__WaitState(wait_time=1),
										transitions={'done': 'Carga de los datos de entrada'},
										autonomy={'done': Autonomy.Off})

			# x:677 y:196
			OperatableStateMachine.add('Enviar goal path',
										GetDefectPathState(),
										transitions={'done': 'Reparar defecto', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off},
										remapping={'path': 'path'})

			# x:920 y:303
			OperatableStateMachine.add('Reparar defecto',
										ExecuteRepairPathActionState(),
										transitions={'done': 'Esperar decision', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off},
										remapping={'path': 'path'})

			# x:931 y:54
			OperatableStateMachine.add('Esperar decision',
										OperatorDecisionState(outcomes=['repair', 'end'], hint=None, suggestion=None),
										transitions={'repair': 'Enviar goal path', 'end': 'finished'},
										autonomy={'repair': Autonomy.Off, 'end': Autonomy.Off})

			# x:645 y:57
			OperatableStateMachine.add('Calcular paths reparacion',
										ComputeDefectsFCPPActionState(),
										transitions={'done': 'Esperar decision', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off})

			# x:360 y:43
			OperatableStateMachine.add('Descomposiciones trapezoidales',
										ComputeIRPolygonDecompositionState(),
										transitions={'done': 'Calcular paths reparacion', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off})

			# x:297 y:249
			OperatableStateMachine.add('carga provisional poligonos',
										LoadPolygonsToIRServerState(),
										transitions={'done': 'Descomposiciones trapezoidales', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off})

			# x:35 y:258
			OperatableStateMachine.add('Carga de los datos de entrada',
										SetIRInputDataState(long_robotx=long_robotx, long_roboty=long_roboty, long_herrx=long_herrx, long_herry=long_herry, tras_herrx=tras_herrx, tras_herry=tras_herry, long_camx=long_camx, long_camy=long_camy, tras_camx=tras_camx, tras_camy=tras_camy, long_areax=long_areax, long_areay=long_areay),
										transitions={'done': 'Descomposicion en zonas de trabajo', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off})

			# x:37 y:501
			OperatableStateMachine.add('Descomposicion en zonas de trabajo',
										ComputeWorkingZonesState(),
										transitions={'done': 'carga provisional poligonos', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off})


		return _state_machine


	# Private functions can be added inside the following tags
	# [MANUAL_FUNC]
	
	# [/MANUAL_FUNC]
