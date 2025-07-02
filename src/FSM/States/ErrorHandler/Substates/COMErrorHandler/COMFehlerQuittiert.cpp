#include "COMFehlerQuittiert.h"



//================================================= constructors & destructors =================================================
COMFehlerQuittiert::COMFehlerQuittiert(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

COMFehlerQuittiert::~COMFehlerQuittiert() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void COMFehlerQuittiert::entry(){
	PRINT_STATE;
    //TODO CODE
}

void COMFehlerQuittiert::exit(){
    //TODO CODE
	PRINT_STATE;
}

State* button_reset_released()
{
    return new COMNoError(data);
}