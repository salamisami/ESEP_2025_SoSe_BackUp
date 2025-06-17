#include "PieceAtGate.h"

//================================================= constructors & destructors =================================================
PieceAtGate::PieceAtGate(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

PieceAtGate::~PieceAtGate() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void PieceAtGate::entry(){
	PRINT_STATE
	
}

void PieceAtGate::exit(){
	PRINT_STATE
	data->timeprofile.timestamp[(int)Timestamp::LASER_RAMP_BLOCKED] = data->stopwatch.peek_time();
}

State* PieceAtGate::laser_ramp_blocked(){
	return new ReadyForCDS(data);
}