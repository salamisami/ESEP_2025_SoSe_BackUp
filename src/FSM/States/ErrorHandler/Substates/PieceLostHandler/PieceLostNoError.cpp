#include "PieceLostNoError.h"


//================================================= constructors & destructors =================================================
PieceLostNoError::PieceLostNoError(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

PieceLostNoError::~PieceLostNoError() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void PieceLostNoError::entry(){
	PRINT_STATE;
    //TODO CODE
}

void PieceLostNoError::exit(){
    //TODO CODE
	PRINT_STATE;
}

State* error_w_lost()
{
    return new PieceLostFehlerUnquittiert(data);
}