#include "IdleGateCP.h"

//================================================= constructors & destructors =================================================
IdleGateCP::IdleGateCP(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

IdleGateCP::~IdleGateCP() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void IdleGateCP::entry(){
	PRINT_STATE;
}

void IdleGateCP::exit(){
    PRINT_STATE;
}

State* IdleGateCP::laser_sorting_gate_blocked(){
    if(!data->is_switch){
        return new OpenGateCP(data);
    }
    return nullptr;
}