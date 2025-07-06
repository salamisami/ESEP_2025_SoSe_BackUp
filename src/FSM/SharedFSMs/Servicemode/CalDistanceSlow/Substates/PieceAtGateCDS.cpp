#include "PieceAtGateCDS.h"

//================================================= constructors & destructors =================================================
PieceAtGateCDS::PieceAtGateCDS(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

PieceAtGateCDS::~PieceAtGateCDS() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void PieceAtGateCDS::entry(){
	PRINT_STATE;
	data->timeprofile.slow_timestamps[(int)Timestamp::LASER_GATE_BLOCKED] = data->stopwatch.peek_time();

}

void PieceAtGateCDS::exit(){
	PRINT_STATE;
}

State* PieceAtGateCDS::laser_sorting_gate_unblocked(){
	return new GateToEndCDS(data);
}

State* PieceAtGateCDS::clone() {
	return new PieceAtGateCDS(data);
}