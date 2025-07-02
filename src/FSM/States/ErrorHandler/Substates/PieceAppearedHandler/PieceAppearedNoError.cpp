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
    //TODO CODE
}

void PieceAppearedNoError::exit(){
    //TODO CODE
	PRINT_STATE;
}

State* error_w_appeared()
{
    return new PieceAppearedFehlerUnquittiert(data);
}