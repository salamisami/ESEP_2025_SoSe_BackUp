#include "Fast.h"

//================================================= constructors & destructors
//=================================================
Fast::Fast(ContextData *data) : State(data) {
  // substate = new SubState(data);
}

Fast::~Fast() {}

//===================================================== private functions
//=====================================================

//===================================================== public functions
//=====================================================
void Fast::entry() {
  PRINT_STATE;
  MotorControl::updateData(data, MotorPieceState::FAST);
  data->sender->send_event((int8_t)Topic::ACTUATOR,
                           (int)ActuatorEnum::MOTOR_SLOW_OFF,
                           (int)EventPriority::SECOND_PRIO);
  data->sender->send_event((int8_t)Topic::ACTUATOR,
                           (int)ActuatorEnum::MOTOR_RIGHT_START,
                           (int)EventPriority::SECOND_PRIO);
}

void Fast::exit() { PRINT_STATE; }

State *Fast::delete_w_motor() {
  MotorControl::updateData(data, MotorPieceState::DELETE_W_MOTOR);
  if (data->workpieces) {
    return AREA_AS_INT_TO_STATE(
        data,
        MotorControl::motorTransition(data, MotorPieceState::DELETE_W_MOTOR));
  } else {
    return new Idle(data);
  }
}

State *Fast::motor_fast() {
  data->workpieceList.updateDataMotorFlags(
      data->workpieceList, data->motor_stopped, data->motor_slowed);
  return AREA_AS_INT_TO_STATE(
      data, MotorControl::motorTransition(data, MotorPieceState::FAST));
}

State *Fast::motor_stop_fsm() {
  return AREA_AS_INT_TO_STATE(
      data, MotorControl::motorTransition(data, MotorPieceState::STOPPED));
}

State *Fast::motor_slow() {
  return AREA_AS_INT_TO_STATE(
      data, MotorControl::motorTransition(data, MotorPieceState::SLOW));
}

State *Fast::clone() { return new Fast(data); }
