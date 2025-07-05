#include "GateToEndCDF.h"

//================================================= constructors & destructors =================================================
GateToEndCDF::GateToEndCDF(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

GateToEndCDF::~GateToEndCDF() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void GateToEndCDF::entry(){
	PRINT_STATE;
    data->timeprofile.fast_timestamps[(int) Timestamp::LASER_GATE_UNBLOCKED] = data->stopwatch.peek_time();
}

void GateToEndCDF::exit(){
    PRINT_STATE;
    data->timeprofile.fast_timestamps[(int) Timestamp::END] = data->stopwatch.peek_time();
}

State* GateToEndCDF::clone() {
    return new GateToEndCDF(data);
}

State* GateToEndCDF::laser_back_blocked(){
    //return new CalRampFast(data);
    return State::EXIT_STATE;
}