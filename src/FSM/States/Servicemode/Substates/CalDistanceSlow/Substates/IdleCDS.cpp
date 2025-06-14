#include "IdleCDS.h"

//================================================= constructors & destructors =================================================
IdleCDS::IdleCDS(ContextData* data) : HState(data) {
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

State* IdleCDS::laser_front_unblocked(){
	return new StartCDS(data);
}