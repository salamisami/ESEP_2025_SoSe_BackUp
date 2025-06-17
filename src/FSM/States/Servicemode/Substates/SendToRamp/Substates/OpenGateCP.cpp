#include "OpenGateCP.h"

//================================================= constructors & destructors =================================================
OpenGateCP::OpenGateCP(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

OpenGateCP::~OpenGateCP() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void OpenGateCP::entry(){
	PRINT_STATE;
    data->timer->start_timer(250, TIMER_ID::OPEN_GATE_CP);
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::SORTING_ON);
}

void OpenGateCP::exit(){
    PRINT_STATE;
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::SORTING_OFF);
}

State* OpenGateCP::timer(TIMER_ID id){
    if(id == TIMER_ID::OPEN_GATE_CP){
        return new IdleGateCP(data);
    }
    return nullptr;
}