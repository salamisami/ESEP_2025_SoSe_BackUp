#include "IdleGateCDF.h"

//================================================= contructors & destructors =================================================
IdleGateCDF::IdleGateCDF(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

IdleGateCDF::~IdleGateCDF() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void IdleGateCDF::entry(){
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void IdleGateCDF::exit(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

I_State* IdleGateCDF::laser_sorting_gate_blocked(){
    if(data->is_switch){
        return new OpenGateCDF(data);
    }
    return nullptr;
}