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
from irobot_sm_flexbe_states.computerectanglefcpp_action_state import ComputeRectangleFCPPActionState
from irobot_sm_flexbe_states.getinspectionpathstate import GetInspectionPathState
from irobot_sm_flexbe_states.getPartialPanorama import GetPartialPanoramaState
from irobot_sm_flexbe_states.executepath_action_state import ExecutePathActionState
from irobot_sm_flexbe_states.getCompletePanorama import getCompletePanoramaState
from irobot_sm_flexbe_states.executepath_repair_action_state import ExecuteRepairPathActionState
# Additional imports can be added inside the following tags
# [MANUAL_IMPORT]

# [/MANUAL_IMPORT]


'''
Created on Thu Jun 13 2019
@author: Alvaro
'''
class IROBOT_eng_inspection_and_reparation_StateMachine_Sept19SM(Behavior):
	'''
	Maquina de estados que coordina los movimientos de un robot Summit Xl para la inspeccion completa de la superficie de una chapa de acero y la detección y reparación de defectos marcados en la misma.
	'''


	def __init__(self):
		super(IROBOT_eng_inspection_and_reparation_StateMachine_Sept19SM, self).__init__()
		self.name = 'IROBOT_eng_inspection_and_reparation_StateMachine_Sept19'

		# parameters of this behavior
		self.add_parameter('defecto_a_reparar', 0)

		# references to used behaviors

		# Additional initialization code can be added inside the following tags
		# [MANUAL_INIT]
		
		# [/MANUAL_INIT]

		# Behavior comments:



	def create(self):
		long_robot_x = 1.035
		long_robot_y = 0.95
		long_herr_x = 1
		long_herr_y = 1
		tras_herr_x = 40
		tras_herr_y = 40
		long_area_x = 2
		long_area_y = 2
		long_cam_x = 1
		long_cam_y = 1
		tras_cam_x = 0.58
		tras_cam_y = 0
		# x:1251 y:716, x:44 y:279, x:883 y:288, x:1708 y:384
		_state_machine = OperatableStateMachine(outcomes=['finished', 'failed', 'failed2', 'failed3'])
		_state_machine.userdata.zona0_id_int = 0
		_state_machine.userdata.fccp_type = 'c'
		_state_machine.userdata.antiguo_areax = 3.76
		_state_machine.userdata.antiguo_areay = 2.51
		_state_machine.userdata.folder_path0 = "/home/irobot/imagenesPanorama0/"
		_state_machine.userdata.calib_path = "/home/irobot/data.yml"
		_state_machine.userdata.id_marker = 9
		_state_machine.userdata.finish0 = False
		_state_machine.userdata.direction0 = "0grados"
		_state_machine.userdata.folder_pano_path = "/home/irobot/Documentos/Panoramas"
		_state_machine.userdata.folder_path1 = "/home/irobot/Documentos/imagenesPanorama180/"
		_state_machine.userdata.direction180 = "180grados"

		# Additional creation code can be added inside the following tags
		# [MANUAL_CREATE]
		
		# [/MANUAL_CREATE]

		# x:1163 y:188, x:623 y:390
		_sm_inspectionandpanorama_180_0 = OperatableStateMachine(outcomes=['finished', 'failed'], input_keys=['folder_path', 'calib_path', 'id_marker', 'direction', 'folder_pano_path'])

		with _sm_inspectionandpanorama_180_0:
			# x:99 y:178
			OperatableStateMachine.add('Calculation of path 180',
										ComputeRectangleFCPPActionState(zone_id=180),
										transitions={'done': 'getInspectionPath180', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off})

			# x:377 y:177
			OperatableStateMachine.add('getInspectionPath180',
										GetInspectionPathState(),
										transitions={'done': 'inspection180', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off},
										remapping={'path': 'path1'})

			# x:641 y:181
			OperatableStateMachine.add('inspection180',
										ExecutePathActionState(),
										transitions={'done': 'getPartialPanorama180', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off},
										remapping={'path': 'path1', 'folder_path': 'folder_path', 'calib_path': 'calib_path', 'id_marker': 'id_marker'})

			# x:875 y:181
			OperatableStateMachine.add('getPartialPanorama180',
										GetPartialPanoramaState(),
										transitions={'done': 'finished', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off},
										remapping={'folder_path': 'folder_path', 'direction': 'direction', 'folder_pano_path': 'folder_pano_path'})


		# x:1159 y:190, x:619 y:355
		_sm_inspectionandpanorama_0_1 = OperatableStateMachine(outcomes=['finished', 'failed'], input_keys=['folder_path', 'calib_path', 'id_marker', 'direction', 'folder_pano_path'])

		with _sm_inspectionandpanorama_0_1:
			# x:99 y:178
			OperatableStateMachine.add('Calculation of path 0',
										ComputeRectangleFCPPActionState(zone_id=0),
										transitions={'done': 'getInspectionPath0', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off})

			# x:377 y:177
			OperatableStateMachine.add('getInspectionPath0',
										GetInspectionPathState(),
										transitions={'done': 'inspection0', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off},
										remapping={'path': 'path0'})

			# x:875 y:181
			OperatableStateMachine.add('getPartialPanorama0',
										GetPartialPanoramaState(),
										transitions={'done': 'finished', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off},
										remapping={'folder_path': 'folder_path', 'direction': 'direction', 'folder_pano_path': 'folder_pano_path'})

			# x:641 y:181
			OperatableStateMachine.add('inspection0',
										ExecutePathActionState(),
										transitions={'done': 'getPartialPanorama0', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off},
										remapping={'path': 'path0', 'folder_path': 'folder_path', 'calib_path': 'calib_path', 'id_marker': 'id_marker'})



		with _state_machine:
			# x:169 y:205
			OperatableStateMachine.add('Load of input data',
										SetIRInputDataState(long_robotx=long_robot_x, long_roboty=long_robot_y, long_herrx=long_herr_x, long_herry=long_herr_y, tras_herrx=tras_herr_x, tras_herry=tras_herr_y, long_camx=long_cam_x, long_camy=long_cam_y, tras_camx=tras_cam_x, tras_camy=tras_cam_y, long_areax=long_area_x, long_areay=long_area_y),
										transitions={'done': 'Division into work zones', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off})

			# x:162 y:338
			OperatableStateMachine.add('Division into work zones',
										ComputeWorkingZonesState(),
										transitions={'done': 'InspectionAndPanorama_0', 'failed': 'failed'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off})

			# x:1182 y:619
			OperatableStateMachine.add('Wait for human decision',
										OperatorDecisionState(outcomes=['reset','end','repair'], hint=None, suggestion=None),
										transitions={'reset': 'Active viz topics', 'end': 'finished', 'repair': 'Get goal path'},
										autonomy={'reset': Autonomy.Off, 'end': Autonomy.Off, 'repair': Autonomy.Off})

			# x:1177 y:466
			OperatableStateMachine.add('Active viz topics',
										ActivateIRVizualizationState(),
										transitions={'done': 'Wait for human decision', 'failed': 'failed3'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off})

			# x:1146 y:226
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

			# x:1169 y:121
			OperatableStateMachine.add('Polygon detection',
										ComputeIRPolyDetectionState(),
										transitions={'done': 'Execute trapezoidal decompositions', 'failed': 'failed2'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off})

			# x:1432 y:223
			OperatableStateMachine.add('Calculation of repair paths',
										ComputeDefectsFCPPActionState(),
										transitions={'done': 'Active viz topics', 'failed': 'failed3'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off})

			# x:605 y:42
			OperatableStateMachine.add('InspectionAndPanorama_0',
										_sm_inspectionandpanorama_0_1,
										transitions={'finished': 'InspectionAndPanorama_180', 'failed': 'failed2'},
										autonomy={'finished': Autonomy.Inherit, 'failed': Autonomy.Inherit},
										remapping={'folder_path': 'folder_path0', 'calib_path': 'calib_path', 'id_marker': 'id_marker', 'direction': 'direction0', 'folder_pano_path': 'folder_pano_path'})

			# x:600 y:227
			OperatableStateMachine.add('InspectionAndPanorama_180',
										_sm_inspectionandpanorama_180_0,
										transitions={'finished': 'CompletePanorama', 'failed': 'failed2'},
										autonomy={'finished': Autonomy.Inherit, 'failed': Autonomy.Inherit},
										remapping={'folder_path': 'folder_path1', 'calib_path': 'calib_path', 'id_marker': 'id_marker', 'direction': 'direction180', 'folder_pano_path': 'folder_pano_path'})

			# x:616 y:410
			OperatableStateMachine.add('CompletePanorama',
										getCompletePanoramaState(),
										transitions={'done': 'Polygon detection', 'failed': 'failed2'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off},
										remapping={'name_0': 'direction0', 'name_180': 'direction180', 'folder_pano_path': 'folder_pano_path'})

			# x:1409 y:736
			OperatableStateMachine.add('ExecuteRepairPath',
										ExecuteRepairPathActionState(),
										transitions={'done': 'Wait for human decision', 'failed': 'failed3'},
										autonomy={'done': Autonomy.Off, 'failed': Autonomy.Off},
										remapping={'path': 'path_aux'})


		return _state_machine


	# Private functions can be added inside the following tags
	# [MANUAL_FUNC]
	
	# [/MANUAL_FUNC]
