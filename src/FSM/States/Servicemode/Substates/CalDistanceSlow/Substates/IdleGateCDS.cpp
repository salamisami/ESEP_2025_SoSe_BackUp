#include "IdleGateCDS.h"

//================================================= constructors & destructors =================================================
IdleGateCDS::IdleGateCDS(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

IdleGateCDS::~IdleGateCDS() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void IdleGateCDS::entry(){
	PRINT_STATE;
}

void IdleGateCDS::exit(){
    PRINT_STATE;
}

State* IdleGateCDS::laser_sorting_gate_blocked(){
	if(data->is_switch){
		return new OpenGateCDS(data);
	}
	return nullptr;
}