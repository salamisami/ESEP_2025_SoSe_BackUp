#include "PieceLostFehlerUnquittiert.h"
#include "PieceLostFehlerQuittiert.h"


//================================================= constructors & destructors =================================================
PieceLostFehlerUnquittiert::PieceLostFehlerUnquittiert(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

PieceLostFehlerUnquittiert::~PieceLostFehlerUnquittiert() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void PieceLostFehlerUnquittiert::entry(){
	PRINT_STATE;
    //TODO CODE
}

void PieceLostFehlerUnquittiert::exit(){
    //TODO CODE
	PRINT_STATE;
}

State* button_reset_released()
{
    return new PieceLostFehlerQuittiert(data);
}