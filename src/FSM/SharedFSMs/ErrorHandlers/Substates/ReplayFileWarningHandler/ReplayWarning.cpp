#include "ReplayWarning.h"


//================================================= constructors & destructors =================================================
ReplayWarning::ReplayWarning(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

ReplayWarning::~ReplayWarning() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void ReplayWarning::entry(){
	PRINT_STATE;
    //TODO CODE
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_YELLOW_ON_FAST);
}

void ReplayWarning::exit(){
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_YELLOW_OFF);
    //TODO CODE
	PRINT_STATE;
}

State* ReplayWarning::button_reset_released()
{
    return new ReplayNoWarning(data);
}