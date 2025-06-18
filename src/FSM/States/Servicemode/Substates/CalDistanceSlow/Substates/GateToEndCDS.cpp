#include "GateToEndCDS.h"

//================================================= constructors & destructors =================================================
GateToEndCDS::GateToEndCDS(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

GateToEndCDS::~GateToEndCDS() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void GateToEndCDS::entry(){
	PRINT_STATE;
    data->timeprofile_slow.timestamp[(int) Timestamp::LASER_GATE_UNBLOCKED] = data->stopwatch.peek_time();
}

void GateToEndCDS::exit(){
    PRINT_STATE;
    data->timeprofile_slow.timestamp[(int) Timestamp::END] = data->stopwatch.peek_time();
}

State* GateToEndCDS::laser_back_blocked(){
    return new CalRampSlow(data);
}