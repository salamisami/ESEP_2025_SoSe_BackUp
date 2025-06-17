#include "PieceGoingToEnd.h"

//================================================= constructors & destructors =================================================
PieceGoingToEnd::PieceGoingToEnd(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

PieceGoingToEnd::~PieceGoingToEnd() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void PieceGoingToEnd::entry(){
	PRINT_STATE
    data->timeprofile.timestamp[(int) Timestamp::LASER_GATE_UNBLOCKED] = data->stopwatch.peek_time();
}

void PieceGoingToEnd::exit(){
    PRINT_STATE
    data->timeprofile.timestamp[(int) Timestamp::END] = data->stopwatch.peek_time();
}

State* PieceGoingToEnd::laser_back_blocked(){
    return new CalGateRampFast(data);
}