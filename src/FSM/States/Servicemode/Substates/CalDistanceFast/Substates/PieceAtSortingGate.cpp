#include "PieceAtSortingGate.h"

//================================================= constructors & destructors =================================================
PieceAtSortingGate::PieceAtSortingGate(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

PieceAtSortingGate::~PieceAtSortingGate() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void PieceAtSortingGate::entry(){
	PRINT_STATE
	data->timeprofile.timestamp[(int)Timestamp::LASER_GATE_BLOCKED] = data->stopwatch.peek_time();

}

void PieceAtSortingGate::exit(){
	PRINT_STATE
}

State* PieceAtSortingGate::laser_sorting_gate_unblocked(){
	return new PieceGoingToEnd(data);
}