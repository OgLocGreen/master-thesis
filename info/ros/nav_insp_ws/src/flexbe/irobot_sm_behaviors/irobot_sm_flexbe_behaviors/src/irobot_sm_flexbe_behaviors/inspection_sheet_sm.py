#!/usr/bin/env python
# -*- coding: utf-8 -*-
###########################################################
#               WARNING: Generated code!                  #
#              **************************                 #
# Manual changes may get lost if file is generated again. #
# Only code inside the [MANUAL] tags will be kept.        #
###########################################################

from flexbe_core import Behavior, Autonomy, OperatableStateMachine, ConcurrencyContainer, PriorityContainer, Logger
from irobot_sm_flexbe_states.findInitialPose import FindInitialPose
from irobot_sm_flexbe_states.moveForwardBackward import moveForward
from irobot_sm_flexbe_states.moveLeftStep import moveLeftStep
from irobot_sm_flexbe_states.moveBackward import moveBackward
from irobot_sm_flexbe_states.decision_state_inspeccion_finalizada import DecisionStateInspection
from irobot_sm_flexbe_states.check_new_scan_backward import checkNewScanBackward
from irobot_sm_flexbe_states.captureImages import captureImages
from irobot_sm_flexbe_states.moveForwardAndCapture import moveForwardAndCapture
from irobot_sm_flexbe_states.moveBackwardAndCapture import moveBackwardAndCapture
from irobot_sm_flexbe_states.moveLeftStepAndCapture import moveLeftStepAndCapture
from irobot_sm_flexbe_states.obstacleDetection import obstacleDetection
from irobot_sm_flexbe_states.operator_decision_state_inspection import OperatorDecisionStateInspection
from flexbe_states.wait_state import WaitState as flexbe_states__WaitState
from irobot_sm_flexbe_states.computeGlobalPanorama import computeGlobalPanoramaState
from irobot_sm_flexbe_states.computePanorama import computePanoramaState
# Additional imports can be added inside the following tags
# [MANUAL_IMPORT]

# [/MANUAL_IMPORT]


'''
Created on Thu Dec 03 2020
@author: Sara
'''
class Inspection_sheetSM(Behavior):
	'''
	Inspecciona la chapa según la información de las realsense centrales
	'''


	def __init__(self):
		super(Inspection_sheetSM, self).__init__()
		self.name = 'Inspection_sheet'

		# parameters of this behavior

		# references to used behaviors

		# Additional initialization code can be added inside the following tags
		# [MANUAL_INIT]
		
		# [/MANUAL_INIT]

		# Behavior comments:



	def create(self):
		ancho_chapa = 2.51
		largo_chapa = 4.38
		robot_vel = 0.10
		step = 0.25
		ancho_base_robot = 0.58
		largo_base_robot = 0.71
		folder_path = "/home/irobot/imgs_panorama"
		# x:631 y:446, x:620 y:315
		_state_machine = OperatableStateMachine(outcomes=['finished', 'failed'])
		_state_machine.userdata.n_pasadas_actuales = 0
		_state_machine.userdata.n_pasadas_totales = 0
		_state_machine.userdata.mode_forward = 0
		_state_machine.userdata.mode_backward = 1
		_state_machine.userdata.n_imgs_actuales = 0
		_state_machine.userdata.n_imgs_ant = 0
		_state_machine.userdata.folder_path = "/home/irobot/imgs_panorama"
		_state_machine.userdata.finish = 0
		_state_machine.userdata.direction0 = "0grados"
		_state_machine.userdata.folder_path_front = "/home/irobot/imgs_panorama_front"
		_state_machine.userdata.folder_path_rear = "/home/irobot/imgs_panorama_rear"
		_state_machine.userdata.direction180 = "180grados"
		_state_machine.userdata.step = 0.4
		_state_machine.userdata.ancho_chapa = 2.51
		_state_machine.userdata.largo_chapa = 3.76
		_state_machine.userdata.id_polygon = 0

		# Additional creation code can be added inside the following tags
		# [MANUAL_CREATE]
		
		# [/MANUAL_CREATE]

		# x:30 y:365, x:130 y:365
		_sm_inspeccion_0 = OperatableStateMachine(outcomes=['finished', 'failed'], input_keys=['n_pasadas_totales', 'n_pasadas_actuales', 'mode_forward', 'mode_backward', 'n_imgs_actuales', 'folder_path'])

		with _sm_inspeccion_0:
			# x:296 y:97
			OperatableStateMachine.add('movimientoDelante',
										moveForward(pathplanning_vel=robot_vel),
										transitions={'done': 'comprobarFinInspeccion', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off},
										remapping={'n_pasadas_ant': 'n_pasadas_actuales', 'n_imgs_ant': 'n_imgs_actuales', 'folder_path': 'folder_path', 'n_pasadas_actuales': 'n_pasadas_actuales', 'n_imgs_actuales': 'n_imgs_actuales'})

			# x:800 y:96
			OperatableStateMachine.add('movimientoIzquierda',
										moveLeftStep(vel=robot_vel, step=step),
										transitions={'done': 'movimientoAtras', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off})

			# x:796 y:271
			OperatableStateMachine.add('movimientoAtras',
										moveBackward(pathplanning_vel=robot_vel),
										transitions={'done': 'comprobarFinInspeccion2', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off},
										remapping={'n_pasadas_ant': 'n_pasadas_actuales', 'n_imgs_ant': 'n_imgs_actuales', 'n_pasadas_actuales': 'n_pasadas_actuales', 'n_imgs_actuales': 'n_imgs_actuales'})

			# x:536 y:90
			OperatableStateMachine.add('comprobarFinInspeccion',
										DecisionStateInspection(),
										transitions={'si': 'finished', 'no': 'movimientoIzquierda', 'posible': 'comprobarSiNuevoEscaneo'},
										autonomy={'si': Autonomy.Off, 'no': Autonomy.Off, 'posible': Autonomy.Off},
										remapping={'n_pasadas_totales': 'n_pasadas_totales', 'n_pasadas_actuales': 'n_pasadas_actuales', 'mode_in': 'mode_backward', 'mode_out': 'mode'})

			# x:527 y:456
			OperatableStateMachine.add('comprobarFinInspeccion2',
										DecisionStateInspection(),
										transitions={'si': 'finished', 'no': 'movimientoIzquierda2', 'posible': 'comprobarSiNuevoEscaneo'},
										autonomy={'si': Autonomy.Off, 'no': Autonomy.Off, 'posible': Autonomy.Off},
										remapping={'n_pasadas_totales': 'n_pasadas_totales', 'n_pasadas_actuales': 'n_pasadas_actuales', 'mode_in': 'mode_forward', 'mode_out': 'mode'})

			# x:19 y:248
			OperatableStateMachine.add('movimientoIzquierda2',
										moveLeftStep(vel=robot_vel, step=step),
										transitions={'done': 'movimientoDelante', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off})

			# x:529 y:270
			OperatableStateMachine.add('comprobarSiNuevoEscaneo',
										checkNewScanBackward(pathplanning_vel=robot_vel),
										transitions={'failed': 'failed', 'si_mode0': 'movimientoDelante', 'si_mode1': 'movimientoAtras', 'no': 'finished'},
										autonomy={'failed': Autonomy.Off, 'si_mode0': Autonomy.Off, 'si_mode1': Autonomy.Off, 'no': Autonomy.Off},
										remapping={'mode': 'mode'})


		# x:458 y:233, x:130 y:365
		_sm_movimiento_1 = OperatableStateMachine(outcomes=['finished', 'failed'], input_keys=['n_pasadas_totales', 'n_pasadas_actuales', 'mode_forward', 'mode_backward', 'n_imgs_actuales', 'folder_path'])

		with _sm_movimiento_1:
			# x:67 y:218
			OperatableStateMachine.add('Buscando Posicion Inicial',
										FindInitialPose(pathplanning_vel=robot_vel, width_sheet=ancho_chapa, long_sheet=largo_chapa, step=step, width_robot=ancho_base_robot, long_robot=largo_base_robot),
										transitions={'done': 'Inspeccion', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off},
										remapping={'n_pasadas_totales': 'n_pasadas_totales'})

			# x:262 y:216
			OperatableStateMachine.add('Inspeccion',
										_sm_inspeccion_0,
										transitions={'finished': 'finished', 'failed': 'failed'},
										autonomy={'finished': Autonomy.Inherit, 'failed': Autonomy.Inherit},
										remapping={'n_pasadas_totales': 'n_pasadas_totales', 'n_pasadas_actuales': 'n_pasadas_actuales', 'mode_forward': 'mode_forward', 'mode_backward': 'mode_backward', 'n_imgs_actuales': 'n_imgs_actuales', 'folder_path': 'folder_path'})


		# x:30 y:365, x:130 y:365
		_sm_detectando_obstaculos_2 = OperatableStateMachine(outcomes=['finished', 'failed'])

		with _sm_detectando_obstaculos_2:
			# x:101 y:77
			OperatableStateMachine.add('detectando obstaculos',
										obstacleDetection(),
										transitions={'done': 'finished', 'failed': 'failed', 'obstaculo': 'Obstaculo detectado'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off, 'obstaculo': Autonomy.Off})

			# x:298 y:85
			OperatableStateMachine.add('Obstaculo detectado',
										OperatorDecisionStateInspection(),
										transitions={'parar': 'failed', 'failed': 'failed'},
										autonomy={'parar': Autonomy.Off, 'failed': Autonomy.Off})


		# x:30 y:388, x:130 y:388
		_sm_inspeccion_3 = OperatableStateMachine(outcomes=['finished', 'failed'], input_keys=['n_pasadas_totales', 'n_pasadas_actuales', 'mode_forward', 'mode_backward', 'n_imgs_actuales', 'folder_path'])

		with _sm_inspeccion_3:
			# x:255 y:27
			OperatableStateMachine.add('movimientoDelante',
										moveForward(pathplanning_vel=robot_vel),
										transitions={'done': 'comprobarFinInspeccion', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off},
										remapping={'n_pasadas_ant': 'n_pasadas_actuales', 'n_imgs_ant': 'n_imgs_actuales', 'folder_path': 'folder_path', 'n_pasadas_actuales': 'n_pasadas_actuales', 'n_imgs_actuales': 'n_imgs_actuales'})

			# x:533 y:163
			OperatableStateMachine.add('movimientoIzquierda',
										moveLeftStep(vel=robot_vel, step=step),
										transitions={'done': 'movimientoAtras', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off})

			# x:833 y:83
			OperatableStateMachine.add('movimientoAtras',
										moveBackward(pathplanning_vel=robot_vel),
										transitions={'done': 'comprobarFinInspeccion2', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off},
										remapping={'n_pasadas_ant': 'n_pasadas_actuales', 'n_imgs_ant': 'n_imgs_actuales', 'n_pasadas_actuales': 'n_pasadas_actuales', 'n_imgs_actuales': 'n_imgs_actuales'})

			# x:241 y:239
			OperatableStateMachine.add('comprobarFinInspeccion',
										DecisionStateInspection(),
										transitions={'si': 'finished', 'no': 'movimientoIzquierda', 'posible': 'comprobarSiNuevoEscaneo'},
										autonomy={'si': Autonomy.Off, 'no': Autonomy.Off, 'posible': Autonomy.Off},
										remapping={'n_pasadas_totales': 'n_pasadas_totales', 'n_pasadas_actuales': 'n_pasadas_actuales', 'mode_in': 'mode_backward', 'mode_out': 'mode'})

			# x:432 y:524
			OperatableStateMachine.add('comprobarFinInspeccion2',
										DecisionStateInspection(),
										transitions={'si': 'finished', 'no': 'movimientoIzquierda2', 'posible': 'comprobarSiNuevoEscaneo'},
										autonomy={'si': Autonomy.Off, 'no': Autonomy.Off, 'posible': Autonomy.Off},
										remapping={'n_pasadas_totales': 'n_pasadas_totales', 'n_pasadas_actuales': 'n_pasadas_actuales', 'mode_in': 'mode_forward', 'mode_out': 'mode'})

			# x:19 y:248
			OperatableStateMachine.add('movimientoIzquierda2',
										moveLeftStep(vel=robot_vel, step=step),
										transitions={'done': 'movimientoDelante', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off})

			# x:427 y:342
			OperatableStateMachine.add('comprobarSiNuevoEscaneo',
										checkNewScanBackward(pathplanning_vel=robot_vel),
										transitions={'failed': 'failed', 'si_mode0': 'movimientoDelante', 'si_mode1': 'movimientoAtras', 'no': 'finished'},
										autonomy={'failed': Autonomy.Off, 'si_mode0': Autonomy.Off, 'si_mode1': Autonomy.Off, 'no': Autonomy.Off},
										remapping={'mode': 'mode'})


		# x:385 y:426, x:171 y:431, x:654 y:466, x:648 y:135, x:260 y:416, x:452 y:369, x:287 y:310
		_sm_inspeccion_detectobstaculos_4 = ConcurrencyContainer(outcomes=['finished', 'failed', 'rearmado'], input_keys=['n_pasadas_totales', 'n_pasadas_actuales', 'mode_forward', 'mode_backward', 'n_imgs_actuales', 'folder_path'], conditions=[
										('failed', [('detectando obstaculos', 'failed')]),
										('finished', [('detectando obstaculos', 'finished')]),
										('finished', [('movimiento', 'finished')]),
										('failed', [('movimiento', 'failed')])
										])

		with _sm_inspeccion_detectobstaculos_4:
			# x:378 y:179
			OperatableStateMachine.add('detectando obstaculos',
										_sm_detectando_obstaculos_2,
										transitions={'finished': 'finished', 'failed': 'failed'},
										autonomy={'finished': Autonomy.Inherit, 'failed': Autonomy.Inherit})

			# x:178 y:177
			OperatableStateMachine.add('movimiento',
										_sm_movimiento_1,
										transitions={'finished': 'finished', 'failed': 'failed'},
										autonomy={'finished': Autonomy.Inherit, 'failed': Autonomy.Inherit},
										remapping={'n_pasadas_totales': 'n_pasadas_totales', 'n_pasadas_actuales': 'n_pasadas_actuales', 'mode_forward': 'mode_forward', 'mode_backward': 'mode_backward', 'n_imgs_actuales': 'n_imgs_actuales', 'folder_path': 'folder_path'})


		# x:1179 y:189, x:512 y:18
		_sm_inspeccion_and_capture_5 = OperatableStateMachine(outcomes=['finished', 'failed'], input_keys=['n_pasadas_totales', 'n_pasadas_actuales', 'mode_forward', 'mode_backward', 'n_imgs_actuales', 'folder_path'])

		with _sm_inspeccion_and_capture_5:
			# x:135 y:91
			OperatableStateMachine.add('pasadaDelante',
										moveForwardAndCapture(pathplanning_vel=robot_vel),
										transitions={'done': 'comprobarFinInspeccion', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off},
										remapping={'n_pasadas_ant': 'n_pasadas_actuales', 'n_imgs_ant': 'n_imgs_actuales', 'folder_path': 'folder_path', 'n_pasadas_actuales': 'n_pasadas_actuales', 'n_imgs_actuales': 'n_imgs_actuales'})

			# x:446 y:94
			OperatableStateMachine.add('comprobarFinInspeccion',
										DecisionStateInspection(),
										transitions={'si': 'finished', 'no': 'pasadaIzqAndCapture', 'posible': 'comprobarSiNuevoEscaneo'},
										autonomy={'si': Autonomy.Off, 'no': Autonomy.Off, 'posible': Autonomy.Off},
										remapping={'n_pasadas_totales': 'n_pasadas_totales', 'n_pasadas_actuales': 'n_pasadas_actuales', 'mode_in': 'mode_backward', 'mode_out': 'mode'})

			# x:434 y:518
			OperatableStateMachine.add('comprobarFinInspeccion2',
										DecisionStateInspection(),
										transitions={'si': 'finished', 'no': 'pasadaIzqAndCapture_2', 'posible': 'comprobarSiNuevoEscaneo'},
										autonomy={'si': Autonomy.Off, 'no': Autonomy.Off, 'posible': Autonomy.Off},
										remapping={'n_pasadas_totales': 'n_pasadas_totales', 'n_pasadas_actuales': 'n_pasadas_actuales', 'mode_in': 'mode_forward', 'mode_out': 'mode'})

			# x:438 y:284
			OperatableStateMachine.add('comprobarSiNuevoEscaneo',
										checkNewScanBackward(pathplanning_vel=robot_vel),
										transitions={'failed': 'failed', 'si_mode0': 'pasadaDelante', 'si_mode1': 'pasadaAtras', 'no': 'finished'},
										autonomy={'failed': Autonomy.Off, 'si_mode0': Autonomy.Off, 'si_mode1': Autonomy.Off, 'no': Autonomy.Off},
										remapping={'mode': 'mode'})

			# x:829 y:225
			OperatableStateMachine.add('pasadaAtras',
										moveBackwardAndCapture(pathplanning_vel=robot_vel),
										transitions={'done': 'comprobarFinInspeccion2', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off},
										remapping={'n_pasadas_ant': 'n_pasadas_actuales', 'n_imgs_ant': 'n_imgs_actuales', 'folder_path': 'folder_path', 'n_pasadas_actuales': 'n_pasadas_actuales', 'n_imgs_actuales': 'n_imgs_actuales'})

			# x:243 y:518
			OperatableStateMachine.add('pasadaIzqAndCapture_2',
										moveLeftStepAndCapture(vel=robot_vel, step=step),
										transitions={'done': 'pasadaDelante', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off},
										remapping={'folder_path': 'folder_path'})

			# x:829 y:98
			OperatableStateMachine.add('pasadaIzqAndCapture',
										moveLeftStepAndCapture(vel=robot_vel, step=step),
										transitions={'done': 'pasadaAtras', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off},
										remapping={'folder_path': 'folder_path'})


		# x:30 y:365, x:130 y:365, x:230 y:388, x:330 y:388
		_sm_container_6 = ConcurrencyContainer(outcomes=['finished', 'failed'], input_keys=['n_pasadas_actuales', 'mode_forward', 'mode_backward', 'n_imgs_actuales', 'folder_path', 'n_pasadas_totales', 'finish'], conditions=[
										('finished', [('Inspeccion', 'finished'), ('capture', 'done')]),
										('failed', [('Inspeccion', 'failed'), ('capture', 'failed')])
										])

		with _sm_container_6:
			# x:261 y:44
			OperatableStateMachine.add('Inspeccion',
										_sm_inspeccion_3,
										transitions={'finished': 'finished', 'failed': 'failed'},
										autonomy={'finished': Autonomy.Inherit, 'failed': Autonomy.Inherit},
										remapping={'n_pasadas_totales': 'n_pasadas_totales', 'n_pasadas_actuales': 'n_pasadas_actuales', 'mode_forward': 'mode_forward', 'mode_backward': 'mode_backward', 'n_imgs_actuales': 'n_imgs_actuales', 'folder_path': 'folder_path'})

			# x:355 y:152
			OperatableStateMachine.add('capture',
										captureImages(folder_path=folder_path),
										transitions={'done': 'finished', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off},
										remapping={'finish': 'finish'})


		# x:822 y:406, x:507 y:7
		_sm_inspeccion_7 = OperatableStateMachine(outcomes=['finished', 'failed'], input_keys=['n_pasadas_totales', 'n_pasadas_actuales', 'mode_forward', 'mode_backward', 'n_imgs_actuales', 'folder_path'])

		with _sm_inspeccion_7:
			# x:296 y:97
			OperatableStateMachine.add('movimientoDelante',
										moveForward(pathplanning_vel=robot_vel),
										transitions={'done': 'comprobarFinInspeccion', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off},
										remapping={'n_pasadas_ant': 'n_pasadas_actuales', 'n_imgs_ant': 'n_imgs_actuales', 'folder_path': 'folder_path', 'n_pasadas_actuales': 'n_pasadas_actuales', 'n_imgs_actuales': 'n_imgs_actuales'})

			# x:800 y:96
			OperatableStateMachine.add('movimientoIzquierda',
										moveLeftStep(vel=robot_vel, step=step),
										transitions={'done': 'movimientoAtras', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off})

			# x:796 y:271
			OperatableStateMachine.add('movimientoAtras',
										moveBackward(pathplanning_vel=robot_vel),
										transitions={'done': 'comprobarFinInspeccion2', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off},
										remapping={'n_pasadas_ant': 'n_pasadas_actuales', 'n_imgs_ant': 'n_imgs_actuales', 'n_pasadas_actuales': 'n_pasadas_actuales', 'n_imgs_actuales': 'n_imgs_actuales'})

			# x:536 y:90
			OperatableStateMachine.add('comprobarFinInspeccion',
										DecisionStateInspection(),
										transitions={'si': 'finished', 'no': 'movimientoIzquierda', 'posible': 'comprobarSiNuevoEscaneo'},
										autonomy={'si': Autonomy.Off, 'no': Autonomy.Off, 'posible': Autonomy.Off},
										remapping={'n_pasadas_totales': 'n_pasadas_totales', 'n_pasadas_actuales': 'n_pasadas_actuales', 'mode_in': 'mode_backward', 'mode_out': 'mode'})

			# x:527 y:456
			OperatableStateMachine.add('comprobarFinInspeccion2',
										DecisionStateInspection(),
										transitions={'si': 'finished', 'no': 'movimientoIzquierda2', 'posible': 'comprobarSiNuevoEscaneo'},
										autonomy={'si': Autonomy.Off, 'no': Autonomy.Off, 'posible': Autonomy.Off},
										remapping={'n_pasadas_totales': 'n_pasadas_totales', 'n_pasadas_actuales': 'n_pasadas_actuales', 'mode_in': 'mode_forward', 'mode_out': 'mode'})

			# x:19 y:248
			OperatableStateMachine.add('movimientoIzquierda2',
										moveLeftStep(vel=robot_vel, step=step),
										transitions={'done': 'movimientoDelante', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off})

			# x:529 y:270
			OperatableStateMachine.add('comprobarSiNuevoEscaneo',
										checkNewScanBackward(pathplanning_vel=robot_vel),
										transitions={'failed': 'failed', 'si_mode0': 'movimientoDelante', 'si_mode1': 'movimientoAtras', 'no': 'finished'},
										autonomy={'failed': Autonomy.Off, 'si_mode0': Autonomy.Off, 'si_mode1': Autonomy.Off, 'no': Autonomy.Off},
										remapping={'mode': 'mode'})



		with _state_machine:
			# x:46 y:227
			OperatableStateMachine.add('Buscando Posicion Inicial',
										FindInitialPose(pathplanning_vel=robot_vel, width_sheet=ancho_chapa, long_sheet=largo_chapa, step=step, width_robot=ancho_base_robot, long_robot=largo_base_robot),
										transitions={'done': 'Inspeccion_and_capture', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off},
										remapping={'n_pasadas_totales': 'n_pasadas_totales'})

			# x:286 y:221
			OperatableStateMachine.add('Inspeccion',
										_sm_inspeccion_7,
										transitions={'finished': 'finished', 'failed': 'failed'},
										autonomy={'finished': Autonomy.Inherit, 'failed': Autonomy.Inherit},
										remapping={'n_pasadas_totales': 'n_pasadas_totales', 'n_pasadas_actuales': 'n_pasadas_actuales', 'mode_forward': 'mode_forward', 'mode_backward': 'mode_backward', 'n_imgs_actuales': 'n_imgs_actuales', 'folder_path': 'folder_path'})

			# x:152 y:564
			OperatableStateMachine.add('Container',
										_sm_container_6,
										transitions={'finished': 'finished', 'failed': 'failed'},
										autonomy={'finished': Autonomy.Inherit, 'failed': Autonomy.Inherit},
										remapping={'n_pasadas_actuales': 'n_pasadas_actuales', 'mode_forward': 'mode_forward', 'mode_backward': 'mode_backward', 'n_imgs_actuales': 'n_imgs_actuales', 'folder_path': 'folder_path', 'n_pasadas_totales': 'n_pasadas_totales', 'finish': 'finish'})

			# x:286 y:134
			OperatableStateMachine.add('Inspeccion_and_capture',
										_sm_inspeccion_and_capture_5,
										transitions={'finished': 'computePanorama0', 'failed': 'failed'},
										autonomy={'finished': Autonomy.Inherit, 'failed': Autonomy.Inherit},
										remapping={'n_pasadas_totales': 'n_pasadas_totales', 'n_pasadas_actuales': 'n_pasadas_actuales', 'mode_forward': 'mode_forward', 'mode_backward': 'mode_backward', 'n_imgs_actuales': 'n_imgs_actuales', 'folder_path': 'folder_path'})

			# x:243 y:35
			OperatableStateMachine.add('Inspeccion_detectObstaculos',
										_sm_inspeccion_detectobstaculos_4,
										transitions={'finished': 'finished', 'failed': 'failed', 'rearmado': 'espera'},
										autonomy={'finished': Autonomy.Inherit, 'failed': Autonomy.Inherit, 'rearmado': Autonomy.Inherit},
										remapping={'n_pasadas_totales': 'n_pasadas_totales', 'n_pasadas_actuales': 'n_pasadas_actuales', 'mode_forward': 'mode_forward', 'mode_backward': 'mode_backward', 'n_imgs_actuales': 'n_imgs_actuales', 'folder_path': 'folder_path'})

			# x:60 y:43
			OperatableStateMachine.add('espera',
										flexbe_states__WaitState(wait_time=1),
										transitions={'done': 'Inspeccion_detectObstaculos'},
										autonomy={'done': Autonomy.Off})

			# x:931 y:134
			OperatableStateMachine.add('computeGlobalPanorama',
										computeGlobalPanoramaState(),
										transitions={'done': 'finished', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off},
										remapping={'folder_path': 'folder_path_front', 'direction': 'direction0', 'folder_pano_path': 'folder_path', 'step': 'step', 'width_sheet': 'ancho_chapa', 'long_sheet': 'largo_chapa'})

			# x:726 y:134
			OperatableStateMachine.add('computePanorama180',
										computePanoramaState(),
										transitions={'done': 'computeGlobalPanorama', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off},
										remapping={'folder_path': 'folder_path_rear', 'direction': 'direction180', 'folder_pano_path': 'folder_path', 'step': 'step', 'width_sheet': 'ancho_chapa', 'long_sheet': 'largo_chapa'})

			# x:518 y:136
			OperatableStateMachine.add('computePanorama0',
										computePanoramaState(),
										transitions={'done': 'computePanorama180', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off},
										remapping={'folder_path': 'folder_path_front', 'direction': 'direction0', 'folder_pano_path': 'folder_path', 'step': 'step', 'width_sheet': 'ancho_chapa', 'long_sheet': 'largo_chapa'})


		return _state_machine


	# Private functions can be added inside the following tags
	# [MANUAL_FUNC]
	
	# [/MANUAL_FUNC]
