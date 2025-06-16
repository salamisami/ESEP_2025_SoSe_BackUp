#include "ReadyForCDF.h"

//================================================= constructors & destructors =================================================
ReadyForCDF::ReadyForCDF(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

ReadyForCDF::~ReadyForCDF() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void ReadyForCDF::entry(){
	PRINT_STATE;
    std::cout << "Please put a piece to calibrate distance timer (fast mode)" << std::endl;
}

void ReadyForCDF::exit(){
    PRINT_STATE;
}

State* ReadyForCDF::laser_front_blocked(){
    return new CalDistanceFast(data);
}