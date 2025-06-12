#include "IdleCDS.h"

//================================================= contructors & destructors =================================================
IdleCDS::IdleCDS(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

IdleCDS::~IdleCDS() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void IdleCDS::entry(){
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void IdleCDS::exit(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

I_State* IdleCDS::laser_front_unblocked(){
	return new StartCDS(data);
}