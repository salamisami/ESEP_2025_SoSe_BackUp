#include "RampStatus.h"



//================================================= constructors & destructors =================================================
RampStatus::RampStatus(ContextData* data) : HState(data, new RampNotFull(data)) {
    //substate = new SubState(data);
}

RampStatus::~RampStatus() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void RampStatus::entry(){
	PRINT_STATE;
    //TODO CODE
}

void RampStatus::exit(){
    //TODO CODE
	PRINT_STATE;
}