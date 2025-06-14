#include "Waiting.h"

//================================================= constructors & destructors =================================================
Waiting::Waiting(ContextData* data):State(data){
    
}

Waiting::~Waiting() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void Waiting::entry(){
	std::cout << __PRETTY_FUNCTION__ << std::endl;
    data->timer->start_timer(2000, TIMER_ID::WAITING_BUTTON_START);
}

void Waiting::exit(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

I_State* Waiting::button_start_released(){
    return new Operating(data);
}

I_State* Waiting::timer(TIMER_ID id){
    if(id == TIMER_ID::WAITING_BUTTON_START){
        return new Timer_Received(data);
    }
    return nullptr;
}

/**
State* Operating::estop() {
    data->stateStack->push(substate);
    return new EmergencyStop(data);
}

State* Operating::forward() {
    State* newSubstate = substate->forward();
    if(newSubstate != nullptr) {
        State::exit();
        delete substate;
        substate = newSubstate;
        State::entry();
    }
    return nullptr;
}


State* Operating::service() {
    State* newSubstate = substate->service();
    if(newSubstate != nullptr) {
        return newSubstate;
    }
    return nullptr;
}

*/
