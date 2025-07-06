#include "ReadyForCDS.h"

//================================================= constructors & destructors =================================================
ReadyForCDS::ReadyForCDS(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

ReadyForCDS::~ReadyForCDS() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void ReadyForCDS::entry(){
	PRINT_STATE;
    std::cout << "Please put a piece to calibrate distance timer (slow mode)" << std::endl;
}

void ReadyForCDS::exit(){
    PRINT_STATE;
}

State* ReadyForCDS::laser_front_blocked(){
    return new CalDistanceSlow(data);
}

State* ReadyForCDS::clone() {
    return new ReadyForCDS(data);
}