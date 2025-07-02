#include "COMNoError.h"


//================================================= constructors & destructors =================================================
COMNoError::COMNoError(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

COMNoError::~COMNoError() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void COMNoError::entry(){
	PRINT_STATE;
    //TODO CODE
}

void COMNoError::exit(){
    //TODO CODE
	PRINT_STATE;
}

State* error_c_lost_com()
{
    return new COMFehlerUnquittiert(data);
}