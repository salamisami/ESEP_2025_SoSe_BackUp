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
    
}

void PieceLostNoError::exit(){
    
	PRINT_STATE;
}

State* PieceLostNoError::error_w_lost()
{
    return new PieceLostFehlerUnquittiert(data);
}

State* PieceLostNoError::clone() {
    return new PieceLostNoError(data);
}