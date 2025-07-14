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
    
}

void COMNoError::exit(){
    
	PRINT_STATE;
}

State* COMNoError::clone() {
    return new COMNoError(data);
}

State* COMNoError::error_c_lost_com()
{
    return new COMFehlerUnquittiert(data);
}