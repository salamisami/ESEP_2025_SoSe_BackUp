#include "IdleGateCDS.h"

//================================================= contructors & destructors =================================================
IdleGateCDS::IdleGateCDS(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

IdleGateCDS::~IdleGateCDS() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void IdleGateCDS::entry(){
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void IdleGateCDS::exit(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

I_State* IdleGateCDS::laser_sorting_gate_blocked(){
	if(data->is_switch){
		return new OpenGateCDS(data);
	}
	return nullptr;
}