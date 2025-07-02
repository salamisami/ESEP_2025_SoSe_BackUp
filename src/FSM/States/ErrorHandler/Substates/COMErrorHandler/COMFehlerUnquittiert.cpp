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

State* COMFehlerUnquittiert::button_reset_released()
{
    return new COMFehlerQuittiert(data);
}

State* COMFehlerUnquittiert::com_connected()
{
    return new COMReconnectedUnquittiert(data);
}