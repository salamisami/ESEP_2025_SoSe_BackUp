#include "RampFull.h"


//================================================= constructors & destructors =================================================
RampFull::RampFull(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

RampFull::~RampFull() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void RampFull::entry(){
	PRINT_STATE;
    
    data->sender->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::RAMP_FULL);
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_YELLOW_ON_FAST);
    data->is_ramp_full_local = true;
}

void RampFull::exit(){
	data->is_ramp_full_local = false;
    
	PRINT_STATE;
}

State* RampFull::laser_ramp_unblocked()
{
    return new RampNotFull(data);
}

State* RampFull::clone() {
    return new RampFull(data);
}
