#include "StartCDF.h"

//================================================= constructors & destructors =================================================
StartCDF::StartCDF(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

StartCDF::~StartCDF() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void StartCDF::entry(){
	std::cout << __PRETTY_FUNCTION__ << std::endl;
    data->stopwatch.start();
}

void StartCDF::exit(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

I_State* StartCDF::laser_back_blocked(){
    return new StopCDF(data);
}