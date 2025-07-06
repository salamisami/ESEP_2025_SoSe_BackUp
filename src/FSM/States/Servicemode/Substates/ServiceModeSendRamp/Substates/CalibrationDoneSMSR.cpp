#include "CalibrationDoneSMSR.h"

//================================================= constructors & destructors =================================================
CalibrationDoneSMSR::CalibrationDoneSMSR(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

CalibrationDoneSMSR::~CalibrationDoneSMSR() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void CalibrationDoneSMSR::entry(){
	PRINT_STATE;
}

void CalibrationDoneSMSR::exit(){
    PRINT_STATE;
}

//explicit exit 
State* CalibrationDoneSMSR::laser_ramp_blocked(){
    return State::EXIT_STATE;
}
 
State* CalibrationDoneSMSR::clone() {
    return new CalibrationDoneSMSR(data);
}