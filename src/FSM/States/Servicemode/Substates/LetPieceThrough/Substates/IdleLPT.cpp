#include "IdleLPT.h"

//================================================= constructors & destructors =================================================
IdleLPT::IdleLPT(ContextData* data, int duration) : State(data), duration(duration) {
    //substate = new SubState(data);
}

IdleLPT::~IdleLPT() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void IdleLPT::entry(){
	PRINT_STATE;
}

void IdleLPT::exit(){
    PRINT_STATE;
}

State* IdleLPT::laser_sorting_gate_blocked(){
    if(data->is_switch){
        return new OpenGateLPT(data, duration);
    }
    return nullptr;
}

State* IdleLPT::clone() {
    return new IdleLPT(data, duration);
}