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
    //TODO CODE
}

void RampErrorResolved::exit(){
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_RED_OFF);
    data->sender->send_event((int8_t) Topic::ERROR, (int) Error_Enum::RAMP_ERROR_RESOLVED);
    data->sender->send_event((int8_t) Topic::DELETE_W_MOTOR, (int) Error_Enum::ERROR_BOTH_R_FULL);
    data->error_warning_counter->error_or_warning_resolved();
    //TODO CODE
	PRINT_STATE;
}

State* RampErrorResolved::button_reset_released() 
{
    return new RampNoError(data);
}

State* RampErrorResolved::clone() {
    return new RampErrorResolved(data);
}
