#include "ConfFehlerQuittiert.h"


//================================================= constructors & destructors =================================================
ConfFehlerQuittiert::ConfFehlerQuittiert(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

ConfFehlerQuittiert::~ConfFehlerQuittiert() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void ConfFehlerQuittiert::entry(){
	PRINT_STATE;
    //TODO CODE
}

void ConfFehlerQuittiert::exit(){
    //TODO CODE
	PRINT_STATE;
}

State* ConfFehlerQuittiert::button_reset_released()
{
    return new CalibNoError(data);
}