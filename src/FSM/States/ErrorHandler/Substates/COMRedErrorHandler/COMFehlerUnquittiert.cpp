#include "COMFehlerQuittiert.h"
#include "COMFehlerUnquittiert.h"


//================================================= constructors & destructors =================================================
COMFehlerUnquittiert::COMFehlerUnquittiert(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

COMFehlerUnquittiert::~COMFehlerUnquittiert() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void COMFehlerUnquittiert::entry(){
	PRINT_STATE;
    //TODO CODE
}

void COMFehlerUnquittiert::exit(){
    //TODO CODE
	PRINT_STATE;
}

State* button_reset_released()
{
    return new COMFehlerQuittiert(data);
}