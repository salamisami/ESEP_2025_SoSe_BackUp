#include "Idle.h"

//================================================= contructors & destructors =================================================
Idle::Idle(ContextData* data, State* initial_substate) : State(data) {
    if(initial_substate == nullptr) {
        substate = new Traffic_Green_On_Slow(data);
    } else {
        substate = initial_substate;
    }
}

Idle::~Idle() {
}

//===================================================== private functions =====================================================




//===================================================== public functions =====================================================

void Idle::entry() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    substate->entry();
}

void Idle::exit() {
    substate->exit();
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

State* Idle::button_start_released(){
    State* newSubstate = substate->button_start_released();
    if(newSubstate != nullptr){
        //there is a super_substate change, explicit exit
        return newSubstate;
    }
    return nullptr;
}