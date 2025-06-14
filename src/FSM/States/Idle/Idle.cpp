#include "Idle.h"

//================================================= constructors & destructors =================================================
Idle::Idle(ContextData* data, HState* initial_substate) : HState(data) {
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
    HState::entry();
}

void Idle::exit() {
    HState::exit();
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