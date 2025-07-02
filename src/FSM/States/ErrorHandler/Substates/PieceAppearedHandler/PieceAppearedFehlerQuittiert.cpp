#include "PieceAppearedNoError.h"
#include "PieceAppearedFehlerQuittiert.h"


//================================================= constructors & destructors =================================================
PieceAppearedFehlerQuittiert::PieceAppearedFehlerQuittiert(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

PieceAppearedFehlerQuittiert::~PieceAppearedFehlerQuittiert() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void PieceAppearedFehlerQuittiert::entry(){
	PRINT_STATE;
    //TODO CODE
}

void PieceAppearedFehlerQuittiert::exit(){
    //TODO CODE
	PRINT_STATE;
}

State* button_reset_released()
{
    return new PieceAppearedNoError(data);
}