#include "LeavingGate_PT1.h"

//================================================= constructors & destructors =================================================
LeavingGate_PT1::LeavingGate_PT1(ContextData* data, LocalDataPT1 localdata) : State(data), localdata_(localdata) {
    //substate = new SubState(data);
}

LeavingGate_PT1::~LeavingGate_PT1() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void LeavingGate_PT1::entry(){
	PRINT_STATE;
	data->timer->start_timer(100, TIMER_ID::LEAVINGGATE_PT1);
}

void LeavingGate_PT1::exit(){
	PRINT_STATE;
	
}

State* LeavingGate_PT1::clone(){
	return new LeavingGate_PT1(data, localdata_);
}

State* LeavingGate_PT1::laser_sorting_gate_unblocked() {
	Piece* piece = localdata_.piece;
	piece->piece_tracker->update_distance_force(Area::GATE_END, 0);
	return new GateEnd_PT1(data, localdata_);
}

State* LeavingGate_PT1::timer(TIMER_ID id) {
	if(id != TIMER_ID::LEAVINGGATE_PT1){
		return nullptr;
	}

	Piece* piece = localdata_.piece;
	Area current_area = piece->piece_tracker->get_distance().first;
	if(current_area == Area::GATE){
		return new LeavingGate_PT1(data, localdata_);
	}

	if(current_area == Area::GATE_END){
		return new GateEnd_PT1(data, localdata_);
	}

	DEBUG("PieceMissing! Cause: piece is too long in leaving the Gate.");
MACRO_PIECE_MISSING_PT1
}
