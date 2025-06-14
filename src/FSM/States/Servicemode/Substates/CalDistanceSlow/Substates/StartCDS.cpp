#include "StartCDS.h"

//================================================= constructors & destructors =================================================
StartCDS::StartCDS(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

StartCDS::~StartCDS() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void StartCDS::entry(){
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	data->stopwatch.start();
}

void StartCDS::exit(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

State* StartCDS::laser_back_blocked(){
	return new StopCDS(data);
}