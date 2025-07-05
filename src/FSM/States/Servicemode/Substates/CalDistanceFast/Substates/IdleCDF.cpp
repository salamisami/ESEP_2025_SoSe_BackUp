#include "IdleCDF.h"

//================================================= constructors & destructors =================================================
IdleCDF::IdleCDF(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

IdleCDF::~IdleCDF() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void IdleCDF::entry(){
	PRINT_STATE;
}

void IdleCDF::exit(){
    PRINT_STATE;
}

State* IdleCDF::laser_front_unblocked(){
    return new StartCDF(data);
}

State* IdleCDF::clone() {
    return new IdleCDF(data);
}