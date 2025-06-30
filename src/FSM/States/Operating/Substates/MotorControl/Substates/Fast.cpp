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
        return new Fast();
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
    return new Fast();
}

State *Fast::motor_stop_fsm()
{
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_STOP);
    return new Stop(data);
}