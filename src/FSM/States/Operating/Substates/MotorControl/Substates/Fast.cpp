#include "Fast.h"

//================================================= constructors & destructors =================================================
Fast::Fast(ContextData *data) : State(data)
{
    // substate = new SubState(data);
}

Fast::~Fast() {}

//===================================================== private functions =====================================================

//===================================================== public functions =====================================================
void Fast::entry()
{
    PRINT_STATE;
}

void Fast::exit()
{
    PRINT_STATE;
}

State *Fast::delete_w_motor()
{
    if (data->workpieces)
    {
        return new Fast(data);
    }
    else
    {
        return new Idle(data);
    }
}

State *Fast::motor_slow()
{
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_SLOW_ON);
    return new Slow(data);
}
State *Fast::motor_fast()
{
    return new Fast(data);
}

State *Fast::motor_stop_fsm()
{
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_STOP);
    return new Stop(data);
}

void Fast::updateData(MotorPieceState motorPieceState) {
    int id = data->event_payload;
    
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
