#include "ReadyForCDF.h"

//================================================= constructors & destructors =================================================
ReadyForCDF::ReadyForCDF(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

ReadyForCDF::~ReadyForCDF() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void ReadyForCDF::entry(){
	std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::cout << "Please put a piece to calibrate distance timer (fast mode)" << std::endl;
}

void ReadyForCDF::exit(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

I_State* ReadyForCDF::laser_front_blocked(){
    return new CalDistanceFast(data);
}