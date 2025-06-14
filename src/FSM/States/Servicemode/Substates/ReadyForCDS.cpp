#include "ReadyForCDS.h"

//================================================= constructors & destructors =================================================
ReadyForCDS::ReadyForCDS(ContextData* data) : HState(data) {
    //substate = new SubState(data);
}

ReadyForCDS::~ReadyForCDS() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void ReadyForCDS::entry(){
	std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::cout << "Please put a piece to calibrate distance timer (slow mode)" << std::endl;
}

void ReadyForCDS::exit(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

State* ReadyForCDS::laser_front_blocked(){
    return new CalDistanceSlow(data);
}