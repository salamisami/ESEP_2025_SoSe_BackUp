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
    
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_YELLOW_ON_FAST);
    data->error_warning_counter->error_or_warning_occured();
    printf("Warning: No config data. Please first Calibrate.\n");
}

void CalibWarning::exit(){
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_YELLOW_OFF);
    data->error_warning_counter->error_or_warning_resolved();
    
	PRINT_STATE;
}

State* CalibWarning::button_reset_released()
{
    return new CalibNoWarning(data);
}

State* CalibWarning::clone() {
    return new CalibWarning(data);
}
