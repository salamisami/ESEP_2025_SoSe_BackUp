#include "RampErrorResolved.h"

//================================================= constructors & destructors =================================================
RampErrorResolved::RampErrorResolved(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

RampErrorResolved::~RampErrorResolved() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void RampErrorResolved::entry(){
	PRINT_STATE;
    
}

void RampErrorResolved::exit(){
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_RED_OFF);
    data->sender->send_event((int8_t) Topic::ERROR, (int) Error_Enum::RAMP_ERROR_RESOLVED);
    data->sender->send_event((int8_t) Topic::MOTOR_SLOW, (int) Error_Enum::ERROR_BOTH_R_FULL); 
    
	PRINT_STATE;
}

State* RampErrorResolved::button_reset_released() 
{
    return new RampNoError(data);
}

State* RampErrorResolved::clone() {
    return new RampErrorResolved(data);
}