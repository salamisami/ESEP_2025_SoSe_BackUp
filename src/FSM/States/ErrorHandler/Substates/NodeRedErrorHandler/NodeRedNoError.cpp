#include "NodeRedNoError.h"


//================================================= constructors & destructors =================================================
NodeRedNoError::NodeRedNoError(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

NodeRedNoError::~NodeRedNoError() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void NodeRedNoError::entry(){
	PRINT_STATE;
    //TODO CODE
}

void NodeRedNoError::exit(){
    //TODO CODE
	PRINT_STATE;
}

State* NodeRedNoError::error_c_lost_nr()
{
    return new NodeRedFehlerUnquittiert(data);
}