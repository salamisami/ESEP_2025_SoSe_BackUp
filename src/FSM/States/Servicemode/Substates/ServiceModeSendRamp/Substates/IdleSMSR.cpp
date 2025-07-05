#include "IdleSMSR.h"

//================================================= constructors & destructors =================================================
IdleSMSR::IdleSMSR(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

IdleSMSR::~IdleSMSR() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void IdleSMSR::entry(){
	PRINT_STATE;
}

void IdleSMSR::exit(){
    PRINT_STATE;
}

State* IdleSMSR::adc_calibration_done(){
    return new CalibrationDoneSMSR(data);
}

State* IdleSMSR::clone() {
    return new IdleSMSR(data);
}