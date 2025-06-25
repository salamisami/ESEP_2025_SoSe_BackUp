#include "Operating.h"

//================================================= constructors & destructors =================================================

Operating::Operating(ContextData* data): State(data) {
}

Operating::~Operating() {
}

//===================================================== private functions =====================================================

//void Operating::privateFunction(){}

//===================================================== public functions =====================================================

void Operating::entry() {
    PRINT_STATE;
    data->sender->send_event((int8_t)Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_GREEN_ON);
    if(data->check_config()){
    	return;
    }
    if(data->history){
    	//TODO enter with History
    }
    //TODO enter without History
}

void Operating::exit() {
	if(!data->no_err_or_war){
		return;
	}
    PRINT_STATE;
    data->sender->send_event((int8_t)Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_GREEN_OFF);
}

State* Operating::button_stop_pressed() {
    return new IdleMode(data);
}
