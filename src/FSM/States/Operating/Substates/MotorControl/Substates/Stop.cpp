#include "Stop.h"

//================================================= constructors & destructors =================================================
Stop::Stop(ContextData *data) : State(data)
{
    // substate = new SubState(data);
}

Stop::~Stop() {}

//===================================================== private functions =====================================================

//===================================================== public functions =====================================================
void Stop::entry()
{
    PRINT_STATE;
}

void Stop::exit()
{
    PRINT_STATE;
}

State *Stop::delete_w_motor()
{
    if (data->workpieces)
    {
        return new Stop(data);
    }
    else
    {
        updateData(MotorPieceState::DELETE_W_MOTOR);
        return new Idle(data);
    }
}

State *Stop::motor_slow()
{
    if (data->motor_stopped)
    {
        return new Stop(data);
    }
    else
    {
        updateData(MotorPieceState::SLOW);
        return new Slow(data);
    }
}

State *Stop::motor_fast()
{
    if (data->motor_stopped)
    {
        return new Stop(data);
    }
    else
    {
        data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_RIGHT_START);
        updateData(MotorPieceState::FAST);
        return new Fast(data);
    }
}

State *Stop::motor_stop_fsm()
{
    return new Stop(data);
}

void Stop::updateData(MotorPieceState motorPieceState) {
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

State* Stop::clone() {
    return new Stop(data);
}
