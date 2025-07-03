#include "CalibWarning.h"


//================================================= constructors & destructors =================================================
CalibWarning::CalibWarning(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

CalibWarning::~CalibWarning() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void CalibWarning::entry(){
	PRINT_STATE;
    //TODO CODE
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_YELLOW_ON_FAST);
}

void CalibWarning::exit(){
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_YELLOW_OFF);
    //TODO CODE
	PRINT_STATE;
}

State* CalibWarning::button_reset_released()
{
    return new CalibNoWarning(data);
}