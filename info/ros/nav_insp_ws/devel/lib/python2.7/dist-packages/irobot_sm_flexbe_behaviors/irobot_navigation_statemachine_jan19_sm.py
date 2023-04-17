#!/usr/bin/env python
# -*- coding: utf-8 -*-
###########################################################
#               WARNING: Generated code!                  #
#              **************************                 #
# Manual changes may get lost if file is generated again. #
# Only code inside the [MANUAL] tags will be kept.        #
###########################################################

#import roslib; roslib.load_manifest('behavior_irobot_navigation_statemachine_jan19')
from flexbe_core import Behavior, Autonomy, OperatableStateMachine, ConcurrencyContainer, PriorityContainer, Logger
from flexbe_states.wait_state import WaitState
from irobot_sm_flexbe_states.baserotation_action_state import BaseRotationActionState
from irobot_sm_flexbe_states.my_move_base_state import MyMoveBaseState
from flexbe_states.operator_decision_state import OperatorDecisionState
from irobot_sm_flexbe_states.completerectanglecoverage_action_state import CompleteRectangleCoverageActionState
from flexbe_states.subscriber_state import SubscriberState
from irobot_sm_flexbe_states.posestamped_pose2d_conversionstate import PoseStamped_Pose2D_ConversionState
from irobot_sm_flexbe_states.checkclickedposition_state import CheckClickedPosition_State
from irobot_sm_flexbe_states.getchapanavparams_state import GetChapaNavParams_State
from irobot_sm_flexbe_states.drawchapas_state import DrawChapasState
from irobot_sm_flexbe_states.getsimpleinspectionposes_state import GetSimpleInspectionPoses_State
from irobot_sm_flexbe_states.moverobotcoord_action_state import MoveRobotCoordActionState
from irobot_sm_flexbe_states.resetoctomap_state import ResetOctomapState
# Additional imports can be added inside the following tags
# [MANUAL_IMPORT]
from geometry_msgs.msg import Pose2D
# [/MANUAL_IMPORT]


'''
Created on Tue Jan 08 2019
@author: Alvaro Fernandez Garcia
'''
class IROBOT_navigation_StateMachine_Jan19SM(Behavior):
	'''
	Maquina de estados que coordina los comportamientos implementados hasta enero de 2019.

Incluye la capacidad de: resetear el mapa del entorno, navegar de manera autonoma hasta posiciones objetivo fijadas en Rviz, cubrir el area de chapas de manera simple o suponiendo un sensor de menor amplitud.

/!\ Necesario ejecutar previamente:
roslaunch spawn_package mpo700_complete_slam_example/factory.launch
	'''


	def __init__(self):
		super(IROBOT_navigation_StateMachine_Jan19SM, self).__init__()
		self.name = 'IROBOT_navigation_StateMachine_Jan19'

		# parameters of this behavior

		# references to used behaviors

		# Additional initialization code can be added inside the following tags
		# [MANUAL_INIT]
		
		# [/MANUAL_INIT]

		# Behavior comments:



	def create(self):
		topic_rviz_goal = "/my_2d_goal"
		dist_laserrobot = 1
		width_laser = 2
		step_path = 4
		vel_path = 0.25
		inspection_frame = "inspection_frame"
		# x:1125 y:52, x:738 y:21
		_state_machine = OperatableStateMachine(outcomes=['failed', 'finished'])
		_state_machine.userdata.rviz_goal_posestamped = []
		_state_machine.userdata.rviz_goal_pose2D = []
		_state_machine.userdata.grados = 180.0

		# Additional creation code can be added inside the following tags
		# [MANUAL_CREATE]
		
		# [/MANUAL_CREATE]

		# x:1163 y:129, x:608 y:354
		_sm_inspeccion_simple_0 = OperatableStateMachine(outcomes=['done', 'failed'], input_keys=['id_chapa'])

		with _sm_inspeccion_simple_0:
			# x:36 y:123
			OperatableStateMachine.add('Obteniendo poses objetivo',
										GetSimpleInspectionPoses_State(retroceso=0.75),
										transitions={'done': 'Alcanzando posicion inicial'},
										autonomy={'done': Autonomy.Off},
										remapping={'id': 'id_chapa', 'output_pose0': 'output_pose0', 'output_pose1': 'output_pose1', 'output_poselong': 'output_poselong'})

			# x:559 y:127
			OperatableStateMachine.add('Inspeccion simple - parte1',
										MoveRobotCoordActionState(vel=vel_path, frame=inspection_frame),
										transitions={'done': 'Inspeccio simple - parte2', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off},
										remapping={'waypoint': 'output_pose1'})

			# x:818 y:122
			OperatableStateMachine.add('Inspeccio simple - parte2',
										MoveRobotCoordActionState(vel=vel_path, frame=inspection_frame),
										transitions={'done': 'done', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off},
										remapping={'waypoint': 'output_poselong'})

			# x:303 y:127
			OperatableStateMachine.add('Alcanzando posicion inicial',
										MoveRobotCoordActionState(vel=0.5, frame=inspection_frame),
										transitions={'done': 'Inspeccion simple - parte1', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off},
										remapping={'waypoint': 'output_pose0'})


		# x:58 y:414, x:328 y:413
		_sm_recibiendo_nuevo_goal_1 = OperatableStateMachine(outcomes=['goal_chapa', 'goal_generico'], output_keys=['rviz_goal_pose2D', 'id_chapa'])

		with _sm_recibiendo_nuevo_goal_1:
			# x:156 y:54
			OperatableStateMachine.add('Esperando topico',
										SubscriberState(topic=topic_rviz_goal, blocking=True, clear=False),
										transitions={'received': 'Conversion a Pose2D', 'unavailable': 'Conversion a Pose2D'},
										autonomy={'received': Autonomy.Off, 'unavailable': Autonomy.High},
										remapping={'message': 'rviz_goal_posestamped'})

			# x:159 y:143
			OperatableStateMachine.add('Conversion a Pose2D',
										PoseStamped_Pose2D_ConversionState(),
										transitions={'done': 'Comprobando si el goal es una chapa'},
										autonomy={'done': Autonomy.Off},
										remapping={'input_posestamped': 'rviz_goal_posestamped', 'output_pose2D': 'rviz_goal_pose2D'})

			# x:150 y:237
			OperatableStateMachine.add('Comprobando si el goal es una chapa',
										CheckClickedPosition_State(),
										transitions={'inside_area': 'goal_chapa', 'outside_area': 'goal_generico'},
										autonomy={'inside_area': Autonomy.Off, 'outside_area': Autonomy.Off},
										remapping={'input_pose2D': 'rviz_goal_pose2D', 'id_chapa': 'id_chapa'})



		with _state_machine:
			# x:90 y:36
			OperatableStateMachine.add('Espera',
										WaitState(wait_time=10),
										transitions={'done': 'Reseteando mapa'},
										autonomy={'done': Autonomy.Off})

			# x:32 y:311
			OperatableStateMachine.add('Realizando primera exploracion',
										BaseRotationActionState(),
										transitions={'done': 'Esperando decision del operador', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off},
										remapping={'n_degrees': 'grados'})

			# x:253 y:426
			OperatableStateMachine.add('Desplazandose a posicion objetivo',
										MyMoveBaseState(),
										transitions={'arrived': 'Esperando decision del operador', 'failed': 'failed'},
										autonomy={'arrived': Autonomy.Off, 'failed': Autonomy.Off},
										remapping={'waypoint': 'rviz_goal_pose2D'})

			# x:947 y:319
			OperatableStateMachine.add('Desplazandose a chapa',
										MyMoveBaseState(),
										transitions={'arrived': 'Seleccionando tipo de inspeccion', 'failed': 'failed'},
										autonomy={'arrived': Autonomy.Off, 'failed': Autonomy.Off},
										remapping={'waypoint': 'output_pose2D'})

			# x:929 y:402
			OperatableStateMachine.add('Seleccionando tipo de inspeccion',
										OperatorDecisionState(outcomes=['simple','compleja','cancelar'], hint=None, suggestion=None),
										transitions={'simple': 'Inspeccion simple', 'compleja': 'Inspeccion compleja de la chapa', 'cancelar': 'Esperando decision del operador'},
										autonomy={'simple': Autonomy.High, 'compleja': Autonomy.High, 'cancelar': Autonomy.High})

			# x:619 y:479
			OperatableStateMachine.add('Inspeccion compleja de la chapa',
										CompleteRectangleCoverageActionState(pathplanning_step=step_path, pathplanning_distlr=dist_laserrobot, pathplanning_widthlaser=width_laser, pathplanning_vel=vel_path),
										transitions={'done': 'Esperando decision del operador', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off},
										remapping={'rect_long': 'rect_long', 'rect_width': 'rect_width', 'path': 'path'})

			# x:291 y:37
			OperatableStateMachine.add('Esperando decision del operador',
										OperatorDecisionState(outcomes=['NuevoGoal','ResetEntorno','Finalizar'], hint=None, suggestion=None),
										transitions={'NuevoGoal': 'Recibiendo nuevo goal', 'ResetEntorno': 'Reseteando mapa', 'Finalizar': 'finished'},
										autonomy={'NuevoGoal': Autonomy.Off, 'ResetEntorno': Autonomy.Off, 'Finalizar': Autonomy.Off})

			# x:541 y:284
			OperatableStateMachine.add('Recibiendo nuevo goal',
										_sm_recibiendo_nuevo_goal_1,
										transitions={'goal_chapa': 'Preparando inspeccion', 'goal_generico': 'Desplazandose a posicion objetivo'},
										autonomy={'goal_chapa': Autonomy.Inherit, 'goal_generico': Autonomy.Inherit},
										remapping={'rviz_goal_pose2D': 'rviz_goal_pose2D', 'id_chapa': 'id_chapa'})

			# x:937 y:157
			OperatableStateMachine.add('Preparando inspeccion',
										GetChapaNavParams_State(),
										transitions={'done': 'Desplazandose a chapa'},
										autonomy={'done': Autonomy.Off},
										remapping={'id': 'id_chapa', 'output_pose2D': 'output_pose2D', 'output_long': 'rect_long', 'output_width': 'rect_width'})

			# x:46 y:206
			OperatableStateMachine.add('Dibujando chapas en Rviz',
										DrawChapasState(),
										transitions={'done': 'Realizando primera exploracion', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off})

			# x:1031 y:490
			OperatableStateMachine.add('Inspeccion simple',
										_sm_inspeccion_simple_0,
										transitions={'done': 'Esperando decision del operador', 'failed': 'failed'},
										autonomy={'done': Autonomy.Inherit, 'failed': Autonomy.Inherit},
										remapping={'id_chapa': 'id_chapa'})

			# x:66 y:121
			OperatableStateMachine.add('Reseteando mapa',
										ResetOctomapState(),
										transitions={'done': 'Dibujando chapas en Rviz', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off})


		return _state_machine


	# Private functions can be added inside the following tags
	# [MANUAL_FUNC]
	
	# [/MANUAL_FUNC]
