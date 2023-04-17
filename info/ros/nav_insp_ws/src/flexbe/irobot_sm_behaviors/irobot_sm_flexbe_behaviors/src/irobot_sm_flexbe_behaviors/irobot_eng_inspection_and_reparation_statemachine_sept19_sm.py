#!/usr/bin/env python
# -*- coding: utf-8 -*-
###########################################################
#               WARNING: Generated code!                  #
#              **************************                 #
# Manual changes may get lost if file is generated again. #
# Only code inside the [MANUAL] tags will be kept.        #
###########################################################

from flexbe_core import Behavior, Autonomy, OperatableStateMachine, ConcurrencyContainer, PriorityContainer, Logger
from irobot_sm_flexbe_states.setIRinputdata_state import SetIRInputDataState
from irobot_sm_flexbe_states.computeworkingzones_state import ComputeWorkingZonesState
from flexbe_states.operator_decision_state import OperatorDecisionState
from irobot_sm_flexbe_states.activateirvizualization_state import ActivateIRVizualizationState
from irobot_sm_flexbe_states.computeirpolygondecomposition_state import ComputeIRPolygonDecompositionState
from irobot_sm_flexbe_states.getdefectpathstate import GetDefectPathState
from irobot_sm_flexbe_states.computepolydetection_state import ComputeIRPolyDetectionState
from irobot_sm_flexbe_states.computedefectsfcpp_action_state import ComputeDefectsFCPPActionState
from irobot_sm_flexbe_states.executepath_repair_action_state import ExecuteRepairPathActionState
from irobot_sm_flexbe_states.findInitialPose import FindInitialPose
from irobot_sm_flexbe_states.obstacleDetection import obstacleDetection
from irobot_sm_flexbe_states.operator_decision_state_irobot import OperatorDecisionStateIRobot
# Additional imports can be added inside the following tags
# [MANUAL_IMPORT]

# [/MANUAL_IMPORT]


'''
Created on 2020
@author: Sara
'''
class IROBOT_eng_inspection_and_reparation_StateMachine_Sept19SM(Behavior):
	'''
	Maquina de estados que coordina los movimientos de un robot Summit Xl para la inspeccion completa de la superficie de una chapa de acero.
	'''


	def __init__(self):
		super(IROBOT_eng_inspection_and_reparation_StateMachine_Sept19SM, self).__init__()
		self.name = 'IROBOT_eng_inspection_and_reparation_StateMachine_Sept19'

		# parameters of this behavior
		self.add_parameter('defecto_a_reparar', 2)

		# references to used behaviors

		# Additional initialization code can be added inside the following tags
		# [MANUAL_INIT]
		
		# [/MANUAL_INIT]

		# Behavior comments:



	def create(self):
		long_robot_x = 0.9
		long_robot_y = 0.8
		long_herr_x = 0.1
		long_herr_y = 0.05
		tras_herr_x = 43
		tras_herr_y = 40
		long_area_x = 3.78
		long_area_y = 2.51
		long_cam_x = 1
		long_cam_y = 1
		tras_cam_x = 0.58
		tras_cam_y = 0
		step = 0.3
		path_panorama = "/home/irobot/panorama.png"
		robot_vel = 0.15
		# x:1251 y:716, x:44 y:279, x:883 y:288, x:1708 y:384
		_state_machine = OperatableStateMachine(outcomes=['finished', 'failed', 'failed2', 'failed3'])
		_state_machine.userdata.reparation_vel = 0.15

		# Additional creation code can be added inside the following tags
		# [MANUAL_CREATE]
		
		# [/MANUAL_CREATE]

		# x:30 y:478, x:447 y:451
		_sm_obstaculo_detectado_0 = PriorityContainer(outcomes=['rearmado', 'parar'])

		with _sm_obstaculo_detectado_0:
			# x:320 y:95
			OperatableStateMachine.add('esperandoRearme',
										OperatorDecisionStateIRobot(),
										transitions={'seguir': 'rearmado', 'parar': 'parar', 'failed': 'parar'},
										autonomy={'seguir': Autonomy.Off, 'parar': Autonomy.Off, 'failed': Autonomy.Off})


		# x:30 y:478, x:130 y:478, x:230 y:478, x:330 y:478
		_sm_detectando_obstaculos_1 = OperatableStateMachine(outcomes=['finished', 'failed', 'rearmado', 'parar'])

		with _sm_detectando_obstaculos_1:
			# x:296 y:86
			OperatableStateMachine.add('Obstacle detection',
										obstacleDetection(),
										transitions={'done': 'finished', 'failed': 'failed', 'obstaculo': 'Obstaculo detectado'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off, 'obstaculo': Autonomy.Off})

			# x:529 y:85
			OperatableStateMachine.add('Obstaculo detectado',
										_sm_obstaculo_detectado_0,
										transitions={'rearmado': 'rearmado', 'parar': 'parar'},
										autonomy={'rearmado': Autonomy.Inherit, 'parar': Autonomy.Inherit})


		# x:30 y:478, x:130 y:478, x:230 y:478, x:615 y:104, x:430 y:478, x:298 y:483, x:607 y:161, x:730 y:478
		_sm_reparacion_2 = ConcurrencyContainer(outcomes=['finished', 'failed'], input_keys=['path_aux', 'reparation_vel'], conditions=[
										('finished', [('ExecuteRepairPath', 'done')]),
										('failed', [('ExecuteRepairPath', 'failed')]),
										('failed', [('detectando obstaculos', 'parar')]),
										('failed', [('detectando obstaculos', 'failed')]),
										('finished', [('detectando obstaculos', 'finished')]),
										('finished', [('detectando obstaculos', 'rearmado')])
										])

		with _sm_reparacion_2:
			# x:354 y:86
			OperatableStateMachine.add('detectando obstaculos',
										_sm_detectando_obstaculos_1,
										transitions={'finished': 'finished', 'failed': 'failed', 'rearmado': 'finished', 'parar': 'failed'},
										autonomy={'finished': Autonomy.Inherit, 'failed': Autonomy.Inherit, 'rearmado': Autonomy.Inherit, 'parar': Autonomy.Inherit})

			# x:66 y:89
			OperatableStateMachine.add('ExecuteRepairPath',
										ExecuteRepairPathActionState(),
										transitions={'done': 'finished', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off},
										remapping={'path': 'path_aux', 'robot_vel': 'reparation_vel'})



		with _state_machine:
			# x:318 y:212
			OperatableStateMachine.add('Load of input data',
										SetIRInputDataState(long_robotx=long_robot_x, long_roboty=long_robot_y, long_herrx=long_herr_x, long_herry=long_herr_y, tras_herrx=tras_herr_x, tras_herry=tras_herr_y, long_camx=long_cam_x, long_camy=long_cam_y, tras_camx=tras_cam_x, tras_camy=tras_cam_y, long_areax=long_area_x, long_areay=long_area_y, id_defect_repair=self.defecto_a_reparar, path_panorama=path_panorama),
										transitions={'done': 'Division into work zones', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off})

			# x:325 y:349
			OperatableStateMachine.add('Division into work zones',
										ComputeWorkingZonesState(),
										transitions={'done': 'Polygon detection', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off})

			# x:1182 y:619
			OperatableStateMachine.add('Wait for human decision',
										OperatorDecisionState(outcomes=['reset','end','repair'], hint=None, suggestion=None),
										transitions={'reset': 'Active viz topics', 'end': 'finished', 'repair': 'Get goal path'},
										autonomy={'reset': Autonomy.Off, 'end': Autonomy.Off, 'repair': Autonomy.Off})

			# x:1181 y:493
			OperatableStateMachine.add('Active viz topics',
										ActivateIRVizualizationState(),
										transitions={'done': 'Wait for human decision', 'failed': 'failed3'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off})

			# x:842 y:516
			OperatableStateMachine.add('Execute trapezoidal decompositions',
										ComputeIRPolygonDecompositionState(),
										transitions={'done': 'Calculation of repair paths', 'failed': 'failed2'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off})

			# x:967 y:750
			OperatableStateMachine.add('Get goal path',
										GetDefectPathState(),
										transitions={'done': 'ExecuteRepairPath', 'failed': 'failed3'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off},
										remapping={'path': 'path_aux'})

			# x:579 y:522
			OperatableStateMachine.add('Polygon detection',
										ComputeIRPolyDetectionState(),
										transitions={'done': 'Execute trapezoidal decompositions', 'failed': 'failed2'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off})

			# x:1432 y:223
			OperatableStateMachine.add('Calculation of repair paths',
										ComputeDefectsFCPPActionState(),
										transitions={'done': 'Active viz topics', 'failed': 'failed3'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off})

			# x:1409 y:736
			OperatableStateMachine.add('ExecuteRepairPath',
										ExecuteRepairPathActionState(),
										transitions={'done': 'Wait for human decision', 'failed': 'failed3'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off},
										remapping={'path': 'path_aux', 'robot_vel': 'reparation_vel'})

			# x:336 y:514
			OperatableStateMachine.add('PosicionInicial',
										FindInitialPose(pathplanning_vel=robot_vel, width_sheet=long_area_y, long_sheet=long_area_x, step=step, width_robot=long_robot_y, long_robot=long_robot_x),
										transitions={'done': 'Polygon detection', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off},
										remapping={'n_pasadas_totales': 'n_pasadas_totales'})

			# x:1291 y:820
			OperatableStateMachine.add('Reparacion',
										_sm_reparacion_2,
										transitions={'finished': 'Wait for human decision', 'failed': 'failed3'},
										autonomy={'finished': Autonomy.Inherit, 'failed': Autonomy.Inherit},
										remapping={'path_aux': 'path_aux', 'reparation_vel': 'reparation_vel'})

			# x:46 y:710
			OperatableStateMachine.add('Obstacle detection',
										obstacleDetection(),
										transitions={'done': 'finished', 'failed': 'finished', 'obstaculo': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off, 'obstaculo': Autonomy.Off})


		return _state_machine


	# Private functions can be added inside the following tags
	# [MANUAL_FUNC]
	
	# [/MANUAL_FUNC]
