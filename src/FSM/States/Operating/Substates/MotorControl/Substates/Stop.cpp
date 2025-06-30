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
        return new Stop();
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
        return new Stop();
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
        return new Stop();
    }
    else
    {
        data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_RIGHT_START);
        return new Fast(data);
    }
}

State *Stop::motor_stop_fsm()
{
    return new Stop();
}