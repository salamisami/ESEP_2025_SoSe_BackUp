#include "NodeRedFehlerQuittiert.h"
#include "NodeRedNoError.h"


//================================================= constructors & destructors =================================================
NodeRedFehlerQuittiert::NodeRedFehlerQuittiert(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

NodeRedFehlerQuittiert::~NodeRedFehlerQuittiert() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void NodeRedFehlerQuittiert::entry(){
	PRINT_STATE;
    //TODO CODE
}

void NodeRedFehlerQuittiert::exit(){
    //TODO CODE
	PRINT_STATE;
}

State* button_reset_released()
{
    return new NodeRedNoError(data);
}