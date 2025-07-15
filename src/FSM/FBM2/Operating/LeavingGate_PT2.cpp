#include "LeavingGate_PT2.h"

//================================================= constructors & destructors =================================================
LeavingGate_PT2::LeavingGate_PT2(ContextData* data) : State(data) {
	//substate = new SubState(data);
}

LeavingGate_PT2::~LeavingGate_PT2() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void LeavingGate_PT2::entry() {
	PRINT_STATE;
	data->timer->start_timer(100, TIMER_ID::LEAVINGGATE_PT2);
}

void LeavingGate_PT2::exit() {
	PRINT_STATE;

}

State* LeavingGate_PT2::clone() {
	return new LeavingGate_PT2(data);
}

State* LeavingGate_PT2::laser_sorting_gate_unblocked() {
	data->piece_FBM2_soll->piece_tracker->update_distance_force(Area::GATE_END, 0);
	return new Gate_End(data);
}

State* LeavingGate_PT2::timer(TIMER_ID id) {
	if(id != TIMER_ID::LEAVINGGATE_PT2) {
		return nullptr;
	}
	auto distance = data->piece_FBM2_soll->piece_tracker->get_distance();
	auto current_area = distance.first;
	auto current_pos = distance.second;

	switch(current_area) {
		case Area::GATE:
			return new LeavingGate_PT2(data);
		case Area::GATE_END:
			if(current_pos < PIECE_TRANSITION_TOLERANCE) {
				return new LeavingGate_PT2(data);
			}
			break;
		default:
			break;
	}

	DEBUG("PieceMissing! Cause: piece is too long in leaving the Gate.");
	printf("Error: Piece takes too long to leave the Gate.\n");
	return new Piece_Missing(data);
}


State* LeavingGate_PT2::request_transfer() {
	data->sender->send_event((int8_t) Topic::COM, (int) COM_Enum::FBM_2_BUSY);
	return nullptr;
}

State* LeavingGate_PT2::laser_front_blocked() {
	return new Pieceappeared(data);
}

State* LeavingGate_PT2::laser_back_blocked() {
	return new Pieceappeared(data);
}

State* LeavingGate_PT2::laser_ramp_blocked() {
	return new Pieceappeared(data);
}