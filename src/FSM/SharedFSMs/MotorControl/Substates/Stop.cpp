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
    MotorControl::updateData(data, MotorPieceState::STOPPED);
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_SLOW_OFF, (int) EventPriority::SECOND_PRIO);
    data->sender->send_event((int8_t)Topic::ACTUATOR, (int)ActuatorEnum::MOTOR_STOP, (int)EventPriority::SECOND_PRIO);
}

void Stop::exit()
{
    PRINT_STATE;
}

State *Stop::delete_w_motor()
{
    MotorControl::updateData(data, MotorPieceState::DELETE_W_MOTOR);
    if (data->workpieces)
    {
        return nullptr;
    }
    else
    {

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
        return new Fast(data);
    }
}

State *Stop::motor_stop_fsm()
{
    return new Stop(data);
}

State *Stop::clone()
{
    return new Stop(data);
}
