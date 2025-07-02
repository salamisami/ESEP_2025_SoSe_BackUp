#include "ConfFehlerUnquittiert.h"


//================================================= constructors & destructors =================================================
ConfFehlerUnquittiert::ConfFehlerUnquittiert(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

ConfFehlerUnquittiert::~ConfFehlerUnquittiert() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void ConfFehlerUnquittiert::entry(){
	PRINT_STATE;
    //TODO CODE
}

void ConfFehlerUnquittiert::exit(){
    //TODO CODE
	PRINT_STATE;
}

State* ConfFehlerUnquittiert::button_reset_released()
{
    return new ConfFehlerQuittiert(data);
}