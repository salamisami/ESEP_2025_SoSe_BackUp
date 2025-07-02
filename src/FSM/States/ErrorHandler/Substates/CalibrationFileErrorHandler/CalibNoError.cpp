#include "CalibNoError.h"
#include "ConfFehlerUnquittiert.h"


//================================================= constructors & destructors =================================================
CalibNoError::CalibNoError(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

CalibNoError::~CalibNoError() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void CalibNoError::entry(){
	PRINT_STATE;
    //TODO CODE
}

void CalibNoError::exit(){
    //TODO CODE
	PRINT_STATE;
}

State* cant_find_rep_conf()
{
    return new ConfFehlerUnquittiert(data);
}