#include "IdleGateCDF.h"

//================================================= constructors & destructors =================================================
IdleGateCDF::IdleGateCDF(ContextData* data, int duration) : State(data), duration(duration) {
    //substate = new SubState(data);
}

IdleGateCDF::~IdleGateCDF() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void IdleGateCDF::entry(){
	PRINT_STATE;
}

void IdleGateCDF::exit(){
    PRINT_STATE;
}

State* IdleGateCDF::laser_sorting_gate_blocked(){
    if(data->is_switch){
        return new OpenGateCDF(data, duration);
    }
    return nullptr;
}