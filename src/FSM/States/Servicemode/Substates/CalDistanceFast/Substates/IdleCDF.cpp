#include "IdleCDF.h"

//================================================= constructors & destructors =================================================
IdleCDF::IdleCDF(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

IdleCDF::~IdleCDF() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void IdleCDF::entry(){
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void IdleCDF::exit(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

State* IdleCDF::laser_front_unblocked(){
    return new StartCDF(data);
}