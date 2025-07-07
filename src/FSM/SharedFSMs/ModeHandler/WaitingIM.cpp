#include "WaitingIM.h"

//================================================= constructors & destructors =================================================
WaitingIM::WaitingIM(ContextData* data) :State(data) {

}

WaitingIM::~WaitingIM() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void WaitingIM::entry() {
    PRINT_STATE;
    data->timer->start_timer(2000, TIMER_ID::WAITING_IM);
}

void WaitingIM::exit() {
    PRINT_STATE;
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_GREEN_OFF);
    
}

//load history
State* WaitingIM::button_start_released() {
	//TODO check config
	bool config = true;
	if(!config){
		//TODO data->sender->send_event(event_code, event_value, priority);
		return nullptr;
	}

    if(data->operating_history->empty()){
        return new Operating(data);
    }
    auto loaded_state = data->operating_history->top();
    data->operating_history->pop();
    return loaded_state;
}

State* WaitingIM::timer(TIMER_ID id) {
    if(id == TIMER_ID::WAITING_IM) {
        return new TimerReceivedIM(data);
    }
    return nullptr;
}
