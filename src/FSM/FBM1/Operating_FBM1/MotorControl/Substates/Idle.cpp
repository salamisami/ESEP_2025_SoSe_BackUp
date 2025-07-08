#include "Idle.h"

//================================================= constructors & destructors =================================================
Idle::Idle(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

Idle::~Idle() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void Idle::entry(){
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_STOP, (int) EventPriority::SECOND_PRIO);
	PRINT_STATE;
}

void Idle::exit(){
    PRINT_STATE;
}

State* Idle::motor_fast(){
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_RIGHT_START, (int) EventPriority::SECOND_PRIO);
    data->current_motor_speed = MotorPieceState::FAST;
    updateData(MotorPieceState::FAST);
    return new Fast(data);
}

State *Idle::motor_stop_fsm()
{
  updateData(MotorPieceState::STOPPED);
  data->current_motor_speed = MotorPieceState::STOPPED;
    for (auto& pair : *data->pieces_map) {
    Piece* piece = pair.second;  
    piece->piece_tracker->stop();               
}
  data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_STOP);
  return new Stop(data);
}

void Idle::updateData(MotorPieceState motorPieceState) {
    int id = data->event_payload;
    
    if (motorPieceState == MotorPieceState::DELETE_W_MOTOR) {
        // Remove the ID from the list if it exists
        if (data->workpieceList.contains(id)) {
            data->workpieceList.remove(id);
        } else {
            printf("Warning: Trying to delete ID %d that doesn't exist in workpiece list\n", id);
        }
    } else {
        // Add the ID if it doesn't exist, then update ALL workpieces to new state
        if (!data->workpieceList.contains(id)) {
            data->workpieceList.add(id, motorPieceState);
        }
        data->workpieceList.updateStateAll(motorPieceState);
    }
    data->workpieces = !data->workpieceList.isEmpty();
}

State* Idle::clone() {
    return new Idle(data);
}
