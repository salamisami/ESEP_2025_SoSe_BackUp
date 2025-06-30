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
        return new Fast(data);
    }
}

State* Slow::motor_stop_fsm(){
        data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_SLOW_OFF);
        data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_STOP);
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
        return new Idle(data);
    }
}
State* Slow::motor_slow(){
    return new Slow(data);
}
