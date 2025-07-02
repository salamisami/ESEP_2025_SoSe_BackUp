#include "PieceAtGateCDF.h"

//================================================= constructors & destructors =================================================
PieceAtGateCDF::PieceAtGateCDF(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

PieceAtGateCDF::~PieceAtGateCDF() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void PieceAtGateCDF::entry(){
	PRINT_STATE;
	data->timeprofile_fast.timestamp[(int)Timestamp::LASER_GATE_BLOCKED] = data->stopwatch.peek_time();

}

void PieceAtGateCDF::exit(){
	PRINT_STATE;
}

State* PieceAtGateCDF::laser_sorting_gate_unblocked(){
	return new GateToEndCDF(data);
}