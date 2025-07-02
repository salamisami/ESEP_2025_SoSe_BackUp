#include "PieceLostFehlerQuittiert.h"


//================================================= constructors & destructors =================================================
PieceLostFehlerQuittiert::PieceLostFehlerQuittiert(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

PieceLostFehlerQuittiert::~PieceLostFehlerQuittiert() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void PieceLostFehlerQuittiert::entry(){
	PRINT_STATE;
    //TODO CODE
}

void PieceLostFehlerQuittiert::exit(){
    //TODO CODE
	PRINT_STATE;
}

State* PieceLostFehlerQuittiert::button_reset_released()
{
    return new PieceLostNoError(data);
}