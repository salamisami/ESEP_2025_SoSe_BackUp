#include "IdleMode.h"

//================================================= constructors & destructors =================================================
IdleMode::IdleMode(ContextData* data) : HState(data, new IdleIM(data)) {
    
}

IdleMode::~IdleMode() {
}

//===================================================== private functions =====================================================




//===================================================== public functions =====================================================

void IdleMode::entry() {
    PRINT_STATE;
    HState::entry();
}

void IdleMode::exit() {
    HState::exit();
    PRINT_STATE;
}

State* IdleMode::button_start_released(){
    State* newSubstate = substate->button_start_released();
    if(newSubstate != nullptr){
        //there is a super_substate change, explicit exit
        return newSubstate;
    }
    return nullptr;
}