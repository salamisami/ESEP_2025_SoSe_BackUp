#include "COMReconnected.h"



//================================================= constructors & destructors =================================================
COMReconnected::COMReconnected(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

COMReconnected::~COMReconnected() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void COMReconnected::entry(){
	PRINT_STATE;
    //TODO CODE
}

void COMReconnected::exit(){
    //TODO CODE
	PRINT_STATE;
}

State* COMReconnected::button_reset_released()
{
    return new COMNoError(data);
}