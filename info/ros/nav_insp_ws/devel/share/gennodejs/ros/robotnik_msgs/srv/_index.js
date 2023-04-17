
"use strict";

let set_float_value = require('./set_float_value.js')
let get_modbus_register = require('./get_modbus_register.js')
let SetMotorMode = require('./SetMotorMode.js')
let SetElevator = require('./SetElevator.js')
let SetMotorStatus = require('./SetMotorStatus.js')
let get_mode = require('./get_mode.js')
let set_digital_output = require('./set_digital_output.js')
let get_digital_input = require('./get_digital_input.js')
let SetMotorPID = require('./SetMotorPID.js')
let SetNamedDigitalOutput = require('./SetNamedDigitalOutput.js')
let set_modbus_register = require('./set_modbus_register.js')
let set_mode = require('./set_mode.js')
let set_CartesianEuler_pose = require('./set_CartesianEuler_pose.js')
let enable_disable = require('./enable_disable.js')
let ResetFromSubState = require('./ResetFromSubState.js')
let set_height = require('./set_height.js')
let InsertTask = require('./InsertTask.js')
let GetBool = require('./GetBool.js')
let set_ptz = require('./set_ptz.js')
let get_alarms = require('./get_alarms.js')
let QueryAlarms = require('./QueryAlarms.js')
let ack_alarm = require('./ack_alarm.js')
let axis_record = require('./axis_record.js')
let set_named_digital_output = require('./set_named_digital_output.js')
let home = require('./home.js')
let SetLaserMode = require('./SetLaserMode.js')
let set_odometry = require('./set_odometry.js')
let set_analog_output = require('./set_analog_output.js')

module.exports = {
  set_float_value: set_float_value,
  get_modbus_register: get_modbus_register,
  SetMotorMode: SetMotorMode,
  SetElevator: SetElevator,
  SetMotorStatus: SetMotorStatus,
  get_mode: get_mode,
  set_digital_output: set_digital_output,
  get_digital_input: get_digital_input,
  SetMotorPID: SetMotorPID,
  SetNamedDigitalOutput: SetNamedDigitalOutput,
  set_modbus_register: set_modbus_register,
  set_mode: set_mode,
  set_CartesianEuler_pose: set_CartesianEuler_pose,
  enable_disable: enable_disable,
  ResetFromSubState: ResetFromSubState,
  set_height: set_height,
  InsertTask: InsertTask,
  GetBool: GetBool,
  set_ptz: set_ptz,
  get_alarms: get_alarms,
  QueryAlarms: QueryAlarms,
  ack_alarm: ack_alarm,
  axis_record: axis_record,
  set_named_digital_output: set_named_digital_output,
  home: home,
  SetLaserMode: SetLaserMode,
  set_odometry: set_odometry,
  set_analog_output: set_analog_output,
};
