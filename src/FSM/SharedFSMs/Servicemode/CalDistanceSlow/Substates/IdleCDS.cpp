#include "IdleCDS.h"

//================================================= constructors & destructors =================================================
IdleCDS::IdleCDS(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

IdleCDS::~IdleCDS() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void IdleCDS::entry(){
	PRINT_STATE;
}

void IdleCDS::exit(){
    PRINT_STATE;
}

State* IdleCDS::laser_front_unblocked(){
    return new StartCDS(data);
}

State* IdleCDS::clone() {
    return new IdleCDS(data);
}