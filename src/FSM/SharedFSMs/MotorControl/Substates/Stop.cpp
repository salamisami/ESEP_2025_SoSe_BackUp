#include "Stop.h"

//================================================= constructors & destructors
//=================================================
Stop::Stop(ContextData* data) : State(data) {
  // substate = new SubState(data);
}

Stop::~Stop() {}

//===================================================== private functions
//=====================================================

//===================================================== public functions
//=====================================================
void Stop::entry() {
  PRINT_STATE;
  data->current_motor_speed = MotorPieceState::STOPPED;
  
  if((int) data->motorpieceRequest != (int) Topic::DELETE_W_MOTOR) {
    MotorControl::updateData(data, MotorPieceState::STOPPED);
  }
  data->sender->send_event((int8_t) Topic::ACTUATOR,
    (int) ActuatorEnum::MOTOR_SLOW_OFF,
    (int) EventPriority::SECOND_PRIO);
  data->sender->send_event((int8_t) Topic::ACTUATOR,
    (int) ActuatorEnum::MOTOR_STOP,
    (int) EventPriority::SECOND_PRIO);

  for(auto& pair : *data->pieces_map) {
    Piece* piece = pair.second; // pair.second is the value (Piece*)
    // Switch case for motor states
    piece->piece_tracker->stop();
  }
}

void Stop::exit() { PRINT_STATE; }

State* Stop::delete_w_motor() {
  MotorControl::updateData(data, MotorPieceState::DELETE_W_MOTOR);
  if(data->workpieces) {
    return AREA_AS_INT_TO_STATE(
      data,
      MotorControl::motorTransition(data, MotorPieceState::DELETE_W_MOTOR));
  } else {
    return new Idle(data);
  }
}

State* Stop::motor_fast() {
  data->workpieceList.updateDataMotorFlags(
    data->workpieceList, data->motor_stopped, data->motor_slowed,
    MotorPieceState::FAST, data->event_payload);
  return AREA_AS_INT_TO_STATE(
    data, MotorControl::motorTransition(data, MotorPieceState::FAST));
}

State* Stop::motor_stop_fsm() {
  data->workpieceList.updateDataMotorFlags(
    data->workpieceList, data->motor_stopped, data->motor_slowed,
    MotorPieceState::STOPPED, data->event_payload);
  return AREA_AS_INT_TO_STATE(
    data, MotorControl::motorTransition(data, MotorPieceState::STOPPED));
}

State* Stop::motor_slow() {
  data->workpieceList.updateDataMotorFlags(
    data->workpieceList, data->motor_stopped, data->motor_slowed,
    MotorPieceState::SLOW, data->event_payload);
  return AREA_AS_INT_TO_STATE(
    data, MotorControl::motorTransition(data, MotorPieceState::SLOW));
}

State* Stop::clone() { return new Stop(data); }
