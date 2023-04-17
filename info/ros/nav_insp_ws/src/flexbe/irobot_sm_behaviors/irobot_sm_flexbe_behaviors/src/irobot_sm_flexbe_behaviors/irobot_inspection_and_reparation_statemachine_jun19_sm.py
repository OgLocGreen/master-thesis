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
from irobot_sm_flexbe_states.computerectanglefcpp_action_state import ComputeRectangleFCPPActionState
from flexbe_states.wait_state import WaitState as flexbe_states__WaitState
from irobot_sm_flexbe_states.findInitialPose import FindInitialPose
# Additional imports can be added inside the following tags
# [MANUAL_IMPORT]

# [/MANUAL_IMPORT]


'''
Created on Thu Jun 13 2019
@author: Alvaro
'''
class IROBOT_inspection_and_reparation_StateMachine_Jun19SM(Behavior):
	'''
	Maquina de estados que coordina los movimientos de un robot Summit Xl para la inspeccion completa de la superficie de una chapa de acero y la detección y reparación de defectos marcados en la misma.
	'''


	def __init__(self):
		super(IROBOT_inspection_and_reparation_StateMachine_Jun19SM, self).__init__()
		self.name = 'IROBOT_inspection_and_reparation_StateMachine_Jun19'

		# parameters of this behavior
		self.add_parameter('defecto_a_reparar', 0)

		# references to used behaviors

		# Additional initialization code can be added inside the following tags
		# [MANUAL_INIT]
		
		# [/MANUAL_INIT]

		# Behavior comments:



	def create(self):
		long_robot_x = 0.58
		long_robot_y = 0.44
		long_herr_x = 0.8
		long_herr_y = 0.8
		tras_herr_x = 70
		tras_herr_y = 60
		long_area_x = 10.41
		long_area_y = 3.85
		long_cam_x = 1
		long_cam_y = 1
		tras_cam_x = 40
		tras_cam_y = 40
		# x:1432 y:408, x:715 y:47, x:1327 y:765
		_state_machine = OperatableStateMachine(outcomes=['finished', 'failed', 'failed2'])
		_state_machine.userdata.zona0_id_int = 0
		_state_machine.userdata.fccp_type = 'c'
		_state_machine.userdata.antiguo_areax = 8
		_state_machine.userdata.antiguo_areay = 4

		# Additional creation code can be added inside the following tags
		# [MANUAL_CREATE]
		
		# [/MANUAL_CREATE]

		# x:48 y:439, x:725 y:406, x:339 y:397, x:654 y:349
		_sm_ejecuta_fp_inspeccion__0 = ConcurrencyContainer(outcomes=['finished', 'failed'], conditions=[
										('finished', [('Ejecutar path zona', 'done')]),
										('finished', [('toma imagenes', 'done')])
										])

		with _sm_ejecuta_fp_inspeccion__0:
			# x:40 y:174
			OperatableStateMachine.add('Ejecutar path zona',
										flexbe_states__WaitState(wait_time=0.0),
										transitions={'done': 'finished'},
										autonomy={'done': Autonomy.Off})

			# x:295 y:175
			OperatableStateMachine.add('toma imagenes',
										flexbe_states__WaitState(wait_time=0.0),
										transitions={'done': 'finished'},
										autonomy={'done': Autonomy.Off})



		with _state_machine:
			# x:34 y:53
			OperatableStateMachine.add('Cargado de los datos de entrada al problema',
										SetIRInputDataState(long_robotx=long_robot_x, long_roboty=long_robot_y, long_herrx=long_herr_x, long_herry=long_herr_y, tras_herrx=tras_herr_x, tras_herry=tras_herr_y, long_camx=long_cam_x, long_camy=long_cam_y, tras_camx=tras_cam_x, tras_camy=tras_cam_y, long_areax=long_area_x, long_areay=long_area_y, id_defect_repair=0, path_panorama=""),
										transitions={'done': 'Descomposicion en zonas de trabajo', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off})

			# x:46 y:173
			OperatableStateMachine.add('Descomposicion en zonas de trabajo',
										ComputeWorkingZonesState(),
										transitions={'done': 'posicionInicial', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off})

			# x:231 y:404
			OperatableStateMachine.add('Calcula Path 0',
										ComputeRectangleFCPPActionState(zone_id=0),
										transitions={'done': 'Calcula Path 90', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off})

			# x:471 y:404
			OperatableStateMachine.add('Calcula Path 90',
										ComputeRectangleFCPPActionState(zone_id=90),
										transitions={'done': 'Calcula Path 180', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off})

			# x:719 y:403
			OperatableStateMachine.add('Calcula Path 180',
										ComputeRectangleFCPPActionState(zone_id=180),
										transitions={'done': 'Calcula Path 270', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off})

			# x:956 y:403
			OperatableStateMachine.add('Calcula Path 270',
										ComputeRectangleFCPPActionState(zone_id=270),
										transitions={'done': 'Ejecuta FP inspeccion ', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off})

			# x:1200 y:393
			OperatableStateMachine.add('Ejecuta FP inspeccion ',
										_sm_ejecuta_fp_inspeccion__0,
										transitions={'finished': 'finished', 'failed': 'failed'},
										autonomy={'finished': Autonomy.Inherit, 'failed': Autonomy.Inherit})

			# x:64 y:281
			OperatableStateMachine.add('posicionInicial',
										FindInitialPose(pathplanning_vel=0.11, width_sheet=2.51, long_sheet=3, step=0.2, width_robot=0.5, long_robot=0.5),
										transitions={'done': 'Calcula Path 0', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off},
										remapping={'n_pasadas_totales': 'n_pasadas_totales'})


		return _state_machine


	# Private functions can be added inside the following tags
	# [MANUAL_FUNC]
	
	# [/MANUAL_FUNC]
