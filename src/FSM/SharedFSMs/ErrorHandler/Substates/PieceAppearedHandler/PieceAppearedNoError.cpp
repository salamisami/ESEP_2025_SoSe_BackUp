#include "PieceAppearedNoError.h"


//================================================= constructors & destructors =================================================
PieceAppearedNoError::PieceAppearedNoError(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

PieceAppearedNoError::~PieceAppearedNoError() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void PieceAppearedNoError::entry(){
	PRINT_STATE;
    
}

void PieceAppearedNoError::exit(){
    
	PRINT_STATE;
}

State* PieceAppearedNoError::error_w_appear()
{
    return new PieceAppearedFehlerUnquittiert(data);
}

State* PieceAppearedNoError::clone() {
    return new PieceAppearedNoError(data);
}