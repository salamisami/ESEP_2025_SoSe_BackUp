#include "PieceAppearedFehlerUnquittiert.h"

//================================================= constructors & destructors =================================================
PieceAppearedFehlerUnquittiert::PieceAppearedFehlerUnquittiert(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

PieceAppearedFehlerUnquittiert::~PieceAppearedFehlerUnquittiert() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void PieceAppearedFehlerUnquittiert::entry(){
	PRINT_STATE;
    //TODO CODE
}

void PieceAppearedFehlerUnquittiert::exit(){
    //TODO CODE
	PRINT_STATE;
}

State* button_reset_released()
{
    return new PieceAppearedFehlerQuittiert(data);
}