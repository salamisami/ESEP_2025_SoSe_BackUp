#include "CalibNoWarning.h"


//================================================= constructors & destructors =================================================
CalibNoWarning::CalibNoWarning(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

CalibNoWarning::~CalibNoWarning() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void CalibNoWarning::entry(){
	PRINT_STATE;
    //TODO CODE
}

void CalibNoWarning::exit(){
    //TODO CODE
	PRINT_STATE;
}

State* CalibNoWarning::cant_find_calb_conf()
{
    return new CalibWarning(data);
}