#include "Waiting.h"

//================================================= contructors & destructors =================================================
Waiting::Waiting(ContextData* data):State(data){
    
}

Waiting::~Waiting() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void Waiting::entry(){
	std::cout << __PRETTY_FUNCTION__ << std::endl;
    data->timer->setTimer(2000, IDLE_TIMER);
}

void Waiting::exit(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

State* Waiting::button_start_released(){
    return new Operating(data);
}

State* Waiting::timer(int id){
    if(id == IDLE_TIMER){
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
        substate->exit();
        delete substate;
        substate = newSubstate;
        substate->entry();
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
