#include "ReplayFehlerUnquittiert.h"
#include "ReplayFehlerQuittiert.h"


//================================================= constructors & destructors =================================================
ReplayFehlerUnquittiert::ReplayFehlerUnquittiert(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

ReplayFehlerUnquittiert::~ReplayFehlerUnquittiert() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void ReplayFehlerUnquittiert::entry(){
	PRINT_STATE;
    //TODO CODE
}

void ReplayFehlerUnquittiert::exit(){
    //TODO CODE
	PRINT_STATE;
}

State* button_reset_released()
{
    return new ReplayFehlerQuittiert(data);
}