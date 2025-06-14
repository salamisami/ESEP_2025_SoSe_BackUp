#include "CalibrationDoneSMSR.h"

//================================================= constructors & destructors =================================================
CalibrationDoneSMSR::CalibrationDoneSMSR(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

CalibrationDoneSMSR::~CalibrationDoneSMSR() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void CalibrationDoneSMSR::entry(){
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void CalibrationDoneSMSR::exit(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

//explicit exit 
State* CalibrationDoneSMSR::laser_ramp_blocked(){
    return new ReadyForCDF(data);
}