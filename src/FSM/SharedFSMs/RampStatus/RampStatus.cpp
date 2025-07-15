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
    
}

void RampStatus::exit(){
    
	PRINT_STATE;
}