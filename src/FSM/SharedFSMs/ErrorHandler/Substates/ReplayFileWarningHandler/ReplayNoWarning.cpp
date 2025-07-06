#include "ReplayNoWarning.h"


//================================================= constructors & destructors =================================================
ReplayNoWarning::ReplayNoWarning(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

ReplayNoWarning::~ReplayNoWarning() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void ReplayNoWarning::entry(){
	PRINT_STATE;
    //TODO CODE
}

void ReplayNoWarning::exit(){
    //TODO CODE
	PRINT_STATE;
}


State* ReplayNoWarning::cant_find_rep_conf() {
    return new ReplayWarning(data);
}

State* ReplayNoWarning::clone() {
    return new ReplayNoWarning(data);
}