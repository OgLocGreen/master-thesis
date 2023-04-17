
"use strict";

let Register = require('./Register.js');
let RobotnikMotorsStatus = require('./RobotnikMotorsStatus.js');
let ptz = require('./ptz.js');
let BatteryDockingStatusStamped = require('./BatteryDockingStatusStamped.js');
let Pose2DArray = require('./Pose2DArray.js');
let inputs_outputs = require('./inputs_outputs.js');
let alarmsmonitor = require('./alarmsmonitor.js');
let Cartesian_Euler_pose = require('./Cartesian_Euler_pose.js');
let BatteryStatusStamped = require('./BatteryStatusStamped.js');
let LaserStatus = require('./LaserStatus.js');
let Registers = require('./Registers.js');
let encoders = require('./encoders.js');
let BatteryStatus = require('./BatteryStatus.js');
let MotorPID = require('./MotorPID.js');
let MotorsStatusDifferential = require('./MotorsStatusDifferential.js');
let BoolArray = require('./BoolArray.js');
let ElevatorStatus = require('./ElevatorStatus.js');
let named_inputs_outputs = require('./named_inputs_outputs.js');
let Alarms = require('./Alarms.js');
let MotorsStatus = require('./MotorsStatus.js');
let SubState = require('./SubState.js');
let SafetyModuleStatus = require('./SafetyModuleStatus.js');
let Data = require('./Data.js');
let ElevatorAction = require('./ElevatorAction.js');
let StringArray = require('./StringArray.js');
let named_input_output = require('./named_input_output.js');
let LaserMode = require('./LaserMode.js');
let Pose2DStamped = require('./Pose2DStamped.js');
let alarmmonitor = require('./alarmmonitor.js');
let AlarmSensor = require('./AlarmSensor.js');
let State = require('./State.js');
let BatteryDockingStatus = require('./BatteryDockingStatus.js');
let InverterStatus = require('./InverterStatus.js');
let QueryAlarm = require('./QueryAlarm.js');
let MotorStatus = require('./MotorStatus.js');
let Interfaces = require('./Interfaces.js');
let Axis = require('./Axis.js');
let SetElevatorFeedback = require('./SetElevatorFeedback.js');
let SetElevatorActionResult = require('./SetElevatorActionResult.js');
let SetElevatorActionFeedback = require('./SetElevatorActionFeedback.js');
let SetElevatorResult = require('./SetElevatorResult.js');
let SetElevatorAction = require('./SetElevatorAction.js');
let SetElevatorGoal = require('./SetElevatorGoal.js');
let SetElevatorActionGoal = require('./SetElevatorActionGoal.js');

module.exports = {
  Register: Register,
  RobotnikMotorsStatus: RobotnikMotorsStatus,
  ptz: ptz,
  BatteryDockingStatusStamped: BatteryDockingStatusStamped,
  Pose2DArray: Pose2DArray,
  inputs_outputs: inputs_outputs,
  alarmsmonitor: alarmsmonitor,
  Cartesian_Euler_pose: Cartesian_Euler_pose,
  BatteryStatusStamped: BatteryStatusStamped,
  LaserStatus: LaserStatus,
  Registers: Registers,
  encoders: encoders,
  BatteryStatus: BatteryStatus,
  MotorPID: MotorPID,
  MotorsStatusDifferential: MotorsStatusDifferential,
  BoolArray: BoolArray,
  ElevatorStatus: ElevatorStatus,
  named_inputs_outputs: named_inputs_outputs,
  Alarms: Alarms,
  MotorsStatus: MotorsStatus,
  SubState: SubState,
  SafetyModuleStatus: SafetyModuleStatus,
  Data: Data,
  ElevatorAction: ElevatorAction,
  StringArray: StringArray,
  named_input_output: named_input_output,
  LaserMode: LaserMode,
  Pose2DStamped: Pose2DStamped,
  alarmmonitor: alarmmonitor,
  AlarmSensor: AlarmSensor,
  State: State,
  BatteryDockingStatus: BatteryDockingStatus,
  InverterStatus: InverterStatus,
  QueryAlarm: QueryAlarm,
  MotorStatus: MotorStatus,
  Interfaces: Interfaces,
  Axis: Axis,
  SetElevatorFeedback: SetElevatorFeedback,
  SetElevatorActionResult: SetElevatorActionResult,
  SetElevatorActionFeedback: SetElevatorActionFeedback,
  SetElevatorResult: SetElevatorResult,
  SetElevatorAction: SetElevatorAction,
  SetElevatorGoal: SetElevatorGoal,
  SetElevatorActionGoal: SetElevatorActionGoal,
};
