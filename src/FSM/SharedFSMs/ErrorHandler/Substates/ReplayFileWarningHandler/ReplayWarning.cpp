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
    
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_YELLOW_ON_FAST);
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::LED_RESET_ON);
    printf("can't find replay-file\n");
    data->error_warning_counter->error_or_warning_occured();
    printf("Warning: No data to read for Replay.\n");
}

void ReplayWarning::exit(){
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_YELLOW_OFF);
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::LED_RESET_OFF);
    data->error_warning_counter->error_or_warning_resolved();
    
	PRINT_STATE;
}

State* ReplayWarning::button_reset_released()
{
    return new ReplayNoWarning(data);
}

State* ReplayWarning::clone() {
    return new ReplayWarning(data);
}
