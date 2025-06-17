#include "PieceGoingToSG.h"

//================================================= constructors & destructors =================================================
PieceGoingToSG::PieceGoingToSG(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

PieceGoingToSG::~PieceGoingToSG() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void PieceGoingToSG::entry(){
	PRINT_STATE
	data->timeprofile.timestamp[(int)Timestamp::ADC_UNBLOCKED] = data->stopwatch.peek_time();

}

void PieceGoingToSG::exit(){
	PRINT_STATE
}

State* PieceGoingToSG::laser_sorting_gate_blocked(){
	return new PieceAtSortingGate(data);
}