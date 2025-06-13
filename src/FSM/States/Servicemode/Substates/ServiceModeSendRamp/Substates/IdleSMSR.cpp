#include "IdleSMSR.h"

//================================================= contructors & destructors =================================================
IdleSMSR::IdleSMSR(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

IdleSMSR::~IdleSMSR() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void IdleSMSR::entry(){
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void IdleSMSR::exit(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

I_State* IdleSMSR::adc_calibration_done(){
    return new CalibrationDoneSMSR(data);
}