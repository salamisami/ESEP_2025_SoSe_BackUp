#include "StartCDS.h"

//================================================= constructors & destructors =================================================
StartCDS::StartCDS(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

StartCDS::~StartCDS() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void StartCDS::entry(){
	PRINT_STATE;
	data->stopwatch.start();
}

void StartCDS::exit(){
    PRINT_STATE;
}

State* StartCDS::laser_back_blocked(){
	return new StopCDS(data);
}