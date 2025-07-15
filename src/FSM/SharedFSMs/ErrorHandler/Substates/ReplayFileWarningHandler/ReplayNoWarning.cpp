#include "ReplayNoWarning.h"


//================================================= constructors & destructors =================================================
ReplayNoWarning::ReplayNoWarning(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

ReplayNoWarning::~ReplayNoWarning() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void ReplayNoWarning::entry(){
	PRINT_STATE;
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::LED_RESET_ON);
}

void ReplayNoWarning::exit(){
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::LED_RESET_OFF);
	PRINT_STATE;
}


State* ReplayNoWarning::cant_find_rep_conf() {
    return new ReplayWarning(data);
}

State* ReplayNoWarning::clone() {
    return new ReplayNoWarning(data);
}