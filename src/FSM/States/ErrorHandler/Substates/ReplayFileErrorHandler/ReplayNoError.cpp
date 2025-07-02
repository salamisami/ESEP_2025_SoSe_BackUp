#include "ReplayNoError.h"


//================================================= constructors & destructors =================================================
ReplayNoError::ReplayNoError(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

ReplayNoError::~ReplayNoError() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void ReplayNoError::entry(){
	PRINT_STATE;
    //TODO CODE
}

void ReplayNoError::exit(){
    //TODO CODE
	PRINT_STATE;
}

State* cant_find_rep_conf()
{
    return new ReplayFehlerUnquittiert(data);
}