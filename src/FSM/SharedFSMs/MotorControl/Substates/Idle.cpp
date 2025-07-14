#include "Idle.h"

//================================================= constructors & destructors
//=================================================
Idle::Idle(ContextData *data) : State(data) {
  // substate = new SubState(data);
}

Idle::~Idle() {}

//===================================================== private functions
//=====================================================

//===================================================== public functions
//=====================================================
void Idle::entry() {

  data->current_motor_speed = MotorPieceState::STOPPED;
  if (data->motorpieceRequest != (int8_t)Topic::DELETE_W_MOTOR) {
    MotorControl::updateData(data, MotorPieceState::STOPPED);
  } else {
    data->current_motor_speed = MotorPieceState::STOPPED;
  }
  data->sender->send_event((int8_t)Topic::ACTUATOR,
                           (int)ActuatorEnum::MOTOR_STOP,
                           (int)EventPriority::SECOND_PRIO);
  data->sender->send_event((int8_t)Topic::ACTUATOR,
                           (int)ActuatorEnum::MOTOR_SLOW_OFF,
                           (int)EventPriority::SECOND_PRIO);
  PRINT_STATE;
}

void Idle::exit() { PRINT_STATE; }

State *Idle::motor_fast() {
  data->workpieceList.updateDataMotorFlags(
      data->workpieceList, data->motor_stopped, data->motor_slowed,
      MotorPieceState::FAST, data->event_payload);
  return AREA_AS_INT_TO_STATE(
      data, MotorControl::motorTransition(data, MotorPieceState::FAST));
}

State *Idle::motor_stop_fsm() {
  data->workpieceList.updateDataMotorFlags(
      data->workpieceList, data->motor_stopped, data->motor_slowed,
      MotorPieceState::STOPPED, data->event_payload);
  return AREA_AS_INT_TO_STATE(
      data, MotorControl::motorTransition(data, MotorPieceState::STOPPED));
}

State *Idle::motor_slow() {
  data->workpieceList.updateDataMotorFlags(
      data->workpieceList, data->motor_stopped, data->motor_slowed,
      MotorPieceState::SLOW, data->event_payload);
  return AREA_AS_INT_TO_STATE(
      data, MotorControl::motorTransition(data, MotorPieceState::SLOW));
}

State *Idle::clone() { return new Idle(data); }
