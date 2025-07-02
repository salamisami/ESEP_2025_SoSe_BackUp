#include "Idle.h"

//================================================= constructors & destructors =================================================
Idle::Idle(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

Idle::~Idle() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void Idle::entry(){
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_STOP);
	PRINT_STATE;
}

void Idle::exit(){
    //TODO:Update data
    PRINT_STATE;
}

State* Idle::motor_fast(){
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_RIGHT_START);
    updateData(MotorPieceState::FAST);
    return new Fast(data);
}

void Idle::updateData(MotorPieceState motorPieceState) {
    int id = data->event_paylod;
    
    if (motorPieceState == MotorPieceState::DELETE_W_MOTOR) {
        // Remove the ID from the list if it exists
        if (data->workpieceList.contains(id)) {
            data->workpieceList.remove(id);
        } else {
            printf("Warning: Trying to delete ID %d that doesn't exist in workpiece list\n", id);
        }
    } else {
        // Normal update/add logic
        if (data->workpieceList.contains(id)) {
            data->workpieceList.updateState(id, motorPieceState);
        } else {
            data->workpieceList.add(id, motorPieceState);
        }
    }
}
