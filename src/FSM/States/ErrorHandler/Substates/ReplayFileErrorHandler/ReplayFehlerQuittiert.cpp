#include "ReplayFehlerQuittiert.h"


//================================================= constructors & destructors =================================================
ReplayFehlerQuittiert::ReplayFehlerQuittiert(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

ReplayFehlerQuittiert::~ReplayFehlerQuittiert() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void ReplayFehlerQuittiert::entry(){
	PRINT_STATE;
    //TODO CODE
}

void ReplayFehlerQuittiert::exit(){
    //TODO CODE
	PRINT_STATE;
}

State* button_reset_released()
{
    return new ReplayNoError(data);
}