#include "Slow.h"

//================================================= constructors & destructors =================================================
Slow::Slow(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

Slow::~Slow() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void Slow::entry(){
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_STOP);
	PRINT_STATE;
}

void Slow::exit(){
    //TODO:Update data
    PRINT_STATE;
}

State* Slow::motor_fast(){
    if (data->motor_slowed){
        return new Slow(data);
    }
    else{
        data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_SLOW_OFF);
        updateData(MotorPieceState::FAST);
        return new Fast(data);
    }
}

State* Slow::motor_stop_fsm(){
        data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_SLOW_OFF);
        data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_STOP);
        updateData(MotorPieceState::STOPPED);
        return new Stop(data);
}

State *Slow::delete_w_motor()
{
    if (data->workpieces)
    {
        return new Slow(data);
    }
    else
    {
        data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_SLOW_OFF);
        updateData(MotorPieceState::DELETE_W_MOTOR);
        return new Idle(data);
    }
}
State* Slow::motor_slow(){
    return new Slow(data);
}

void Slow::updateData(MotorPieceState motorPieceState) {
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

State* Slow::clone() {
    return new Slow(data);
}
