#include "Idle.h"

//================================================= constructors & destructors =================================================
Idle::Idle(ContextData* data) : HState(data, new Traffic_Green_On_Slow(data)) {
    
}

Idle::~Idle() {
}

//===================================================== private functions =====================================================




//===================================================== public functions =====================================================

void Idle::entry() {
    PRINT_STATE;
    HState::entry();
}

void Idle::exit() {
    HState::exit();
    PRINT_STATE;
}

State* Idle::button_start_released(){
    State* newSubstate = substate->button_start_released();
    if(newSubstate != nullptr){
        //there is a super_substate change, explicit exit
        return newSubstate;
    }
    return nullptr;
}
