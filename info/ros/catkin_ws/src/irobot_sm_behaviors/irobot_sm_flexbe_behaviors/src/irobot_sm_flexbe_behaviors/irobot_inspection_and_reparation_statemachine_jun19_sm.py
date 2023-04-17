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
from flexbe_states.operator_decision_state import OperatorDecisionState
from irobot_sm_flexbe_states.computeworkingzones_state import ComputeWorkingZonesState
from irobot_sm_flexbe_states.loadpolysprovisional_state import LoadPolygonsToIRServerState
from irobot_sm_flexbe_states.activateirvizualization_state import ActivateIRVizualizationState
from irobot_sm_flexbe_states.computeirpolygondecomposition_state import ComputeIRPolygonDecompositionState
from irobot_sm_flexbe_states.computerectanglefcpp_action_state import ComputeRectangleFCPPActionState
from irobot_sm_flexbe_states.computedefectsfcpp_action_state import ComputeDefectsFCPPActionState
from irobot_sm_flexbe_states.getdefectpathstate import GetDefectPathState
from irobot_sm_flexbe_states.executepath_action_state import ExecutePathActionState
from flexbe_states.wait_state import WaitState
from irobot_sm_flexbe_states.computepolydetection_state import ComputeIRPolyDetectionState
from irobot_sm_flexbe_states.computepanorama_state import ComputeIRPanoramaState
from irobot_sm_flexbe_states.mergepanorama_state import MergeIRPanoramasState
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
		# x:891 y:567, x:533 y:37, x:1327 y:765
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
										WaitState(wait_time=0.0),
										transitions={'done': 'finished'},
										autonomy={'done': Autonomy.Off})

			# x:295 y:175
			OperatableStateMachine.add('toma imagenes',
										WaitState(wait_time=0.0),
										transitions={'done': 'finished'},
										autonomy={'done': Autonomy.Off})



		with _state_machine:
			# x:34 y:53
			OperatableStateMachine.add('Cargado de los datos de entrada al problema',
										SetIRInputDataState(long_robotx=long_robot_x, long_roboty=long_robot_y, long_herrx=long_herr_x, long_herry=long_herr_y, tras_herrx=tras_herr_x, tras_herry=tras_herr_y, long_camx=long_cam_x, long_camy=long_cam_y, tras_camx=tras_cam_x, tras_camy=tras_cam_y, long_areax=long_area_x, long_areay=long_area_y),
										transitions={'done': 'Descomposicion en zonas de trabajo', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off})

			# x:525 y:436
			OperatableStateMachine.add('Espera decision operario',
										OperatorDecisionState(outcomes=['reset','fin','repara_defecto'], hint=None, suggestion=None),
										transitions={'reset': 'Activa las visualizaciones', 'fin': 'finished', 'repara_defecto': 'Obtiene el path a recorrer'},
										autonomy={'reset': Autonomy.Off, 'fin': Autonomy.Off, 'repara_defecto': Autonomy.Off})

			# x:82 y:145
			OperatableStateMachine.add('Descomposicion en zonas de trabajo',
										ComputeWorkingZonesState(),
										transitions={'done': 'Calcula Path 0', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off})

			# x:1268 y:278
			OperatableStateMachine.add('carga provisional de poligonos',
										LoadPolygonsToIRServerState(),
										transitions={'done': 'Ejecuta las descomposiciones trapezoidales', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off})

			# x:980 y:611
			OperatableStateMachine.add('Activa las visualizaciones',
										ActivateIRVizualizationState(),
										transitions={'done': 'Espera decision operario', 'failed': 'failed2'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off})

			# x:1216 y:375
			OperatableStateMachine.add('Ejecuta las descomposiciones trapezoidales',
										ComputeIRPolygonDecompositionState(),
										transitions={'done': 'Calcula paths defectos', 'failed': 'failed2'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off})

			# x:79 y:286
			OperatableStateMachine.add('Calcula Path 0',
										ComputeRectangleFCPPActionState(zone_id=0),
										transitions={'done': 'Calcula Path 90', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off})

			# x:339 y:281
			OperatableStateMachine.add('Calcula Path 90',
										ComputeRectangleFCPPActionState(zone_id=90),
										transitions={'done': 'Calcula Path 180', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off})

			# x:598 y:281
			OperatableStateMachine.add('Calcula Path 180',
										ComputeRectangleFCPPActionState(zone_id=180),
										transitions={'done': 'Calcula Path 270', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off})

			# x:850 y:285
			OperatableStateMachine.add('Calcula Path 270',
										ComputeRectangleFCPPActionState(zone_id=270),
										transitions={'done': 'Ejecuta FP inspeccion ', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off})

			# x:1117 y:476
			OperatableStateMachine.add('Calcula paths defectos',
										ComputeDefectsFCPPActionState(),
										transitions={'done': 'Activa las visualizaciones', 'failed': 'failed2'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off})

			# x:194 y:459
			OperatableStateMachine.add('Obtiene el path a recorrer',
										GetDefectPathState(),
										transitions={'done': 'Espera decision operario', 'failed': 'failed2'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off},
										remapping={'path': 'path_aux'})

			# x:475 y:591
			OperatableStateMachine.add('Ejecuta el path',
										ExecutePathActionState(),
										transitions={'done': 'Espera decision operario', 'failed': 'failed2'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off},
										remapping={'path': 'path_aux'})

			# x:1021 y:110
			OperatableStateMachine.add('Ejecuta FP inspeccion ',
										_sm_ejecuta_fp_inspeccion__0,
										transitions={'finished': 'Deteccion de los poligonos', 'failed': 'failed'},
										autonomy={'finished': Autonomy.Inherit, 'failed': Autonomy.Inherit})

			# x:1629 y:262
			OperatableStateMachine.add('Deteccion de los poligonos',
										ComputeIRPolyDetectionState(),
										transitions={'done': 'Ejecuta las descomposiciones trapezoidales', 'failed': 'failed2'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off})

			# x:1561 y:61
			OperatableStateMachine.add('Calculo panorama',
										ComputeIRPanoramaState(),
										transitions={'done': 'Deteccion de los poligonos', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off})

			# x:1569 y:170
			OperatableStateMachine.add('Panorama completo',
										MergeIRPanoramasState(),
										transitions={'done': 'Deteccion de los poligonos', 'failed': 'failed2'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off})


		return _state_machine


	# Private functions can be added inside the following tags
	# [MANUAL_FUNC]
	
	# [/MANUAL_FUNC]
