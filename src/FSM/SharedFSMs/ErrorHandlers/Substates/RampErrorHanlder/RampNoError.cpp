#include "RampNoError.h"

//================================================= constructors & destructors =================================================
RampNoError::RampNoError(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

RampNoError::~RampNoError() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void RampNoError::entry(){
	PRINT_STATE;
    //TODO CODE
}

void RampNoError::exit(){
    //TODO CODE
	PRINT_STATE;
}

State* RampNoError::error_both_r_full()
{
    return new RampErrorUnquittiert(data);
}