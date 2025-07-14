#include "Slow.h"

//================================================= constructors & destructors
//=================================================
Slow::Slow(ContextData *data) : State(data) {
  // substate = new SubState(data);
}

Slow::~Slow() {}

//===================================================== private functions
//=====================================================

//===================================================== public functions
//=====================================================
void Slow::entry() {
  data->current_motor_speed = MotorPieceState::SLOW;
  if ((int)data->motorpieceRequest != (int)Topic::DELETE_W_MOTOR) {
    MotorControl::updateData(data, MotorPieceState::SLOW);
  }

  data->current_motor_speed = MotorPieceState::SLOW;
  data->sender->send_event((int8_t)Topic::ACTUATOR,
                           (int)ActuatorEnum::MOTOR_SLOW_ON,
                           (int)EventPriority::SECOND_PRIO);
  data->sender->send_event((int8_t)Topic::ACTUATOR,
                           (int)ActuatorEnum::MOTOR_RIGHT_START,
                           (int)EventPriority::SECOND_PRIO);
  PRINT_STATE;
}

void Slow::exit() { PRINT_STATE; }

State *Slow::delete_w_motor() {
  MotorControl::updateData(data, MotorPieceState::DELETE_W_MOTOR);
  if (data->workpieces) {
    return AREA_AS_INT_TO_STATE(
        data,
        MotorControl::motorTransition(data, MotorPieceState::DELETE_W_MOTOR));
  } else {
    return new Idle(data);
  }
}

State *Slow::motor_fast() {
  data->workpieceList.updateDataMotorFlags(
      data->workpieceList, data->motor_stopped, data->motor_slowed,
      MotorPieceState::FAST, data->event_payload);
  return AREA_AS_INT_TO_STATE(
      data, MotorControl::motorTransition(data, MotorPieceState::FAST));
}

State *Slow::motor_stop_fsm() {
  data->workpieceList.updateDataMotorFlags(
      data->workpieceList, data->motor_stopped, data->motor_slowed,
      MotorPieceState::STOPPED, data->event_payload);
  return AREA_AS_INT_TO_STATE(
      data, MotorControl::motorTransition(data, MotorPieceState::STOPPED));
}

State *Slow::motor_slow() {
  data->workpieceList.updateDataMotorFlags(
      data->workpieceList, data->motor_stopped, data->motor_slowed,
      MotorPieceState::SLOW, data->event_payload);
  return AREA_AS_INT_TO_STATE(
      data, MotorControl::motorTransition(data, MotorPieceState::SLOW));
}

State *Slow::clone() { return new Slow(data); }
