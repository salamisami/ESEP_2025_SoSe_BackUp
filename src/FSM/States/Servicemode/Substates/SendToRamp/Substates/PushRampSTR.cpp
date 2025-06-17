#include "PushRampSTR.h"

//================================================= constructors & destructors =================================================
PushRampSTR::PushRampSTR(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

PushRampSTR::~PushRampSTR() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void PushRampSTR::entry(){
	PRINT_STATE;
    data->timer->start_timer(250, TIMER_ID::PUSHRAMPSTR);
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::SORTING_ON);
}

void PushRampSTR::exit(){
    PRINT_STATE;
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::SORTING_OFF);
}

State* PushRampSTR::timer(TIMER_ID id){
    if(id == TIMER_ID::PUSHRAMPSTR){
        return new IdleSTR(data);
    }
    return nullptr;
}