#include "IdleSTR.h"

//================================================= constructors & destructors =================================================
IdleSTR::IdleSTR(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

IdleSTR::~IdleSTR() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void IdleSTR::entry(){
	PRINT_STATE;
}

void IdleSTR::exit(){
    PRINT_STATE;
}

State* IdleSTR::laser_sorting_gate_blocked(){
    if(!data->is_switch){
        return new PushRampSTR(data);
    }
    return nullptr;
}

State* IdleSTR::clone() {
    return new IdleSTR(data);
}