#include "COMReconnectedUnquittiert.h"



//================================================= constructors & destructors =================================================
COMReconnectedUnquittiert::COMReconnectedUnquittiert(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

COMReconnectedUnquittiert::~COMReconnectedUnquittiert() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void COMReconnectedUnquittiert::entry(){
	PRINT_STATE;
    //TODO CODE
}

void COMReconnectedUnquittiert::exit(){
    //TODO CODE
	PRINT_STATE;
}

State* COMReconnectedUnquittiert::button_reset_released()
{
    return new COMNoError(data);
}