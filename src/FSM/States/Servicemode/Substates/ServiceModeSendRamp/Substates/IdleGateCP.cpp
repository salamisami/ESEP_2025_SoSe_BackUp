#include "IdleGateCP.h"

//================================================= contructors & destructors =================================================
IdleGateCP::IdleGateCP(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

IdleGateCP::~IdleGateCP() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void IdleGateCP::entry(){
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void IdleGateCP::exit(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

I_State* IdleGateCP::laser_sorting_gate_blocked(){
    if(!data->is_switch){
        return new OpenGateCP(data);
    }
    return nullptr;
}