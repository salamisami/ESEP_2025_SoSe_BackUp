#include "Gate_End.h"

//================================================= constructors & destructors =================================================
Gate_End::Gate_End(ContextData* data) : State(data) {}

//HState
//Gate_End::Gate_End(ContextData* data) : HState(data, new SubState(data), <default_next_state> ) {}
//Gate_End::Gate_End(ContextData* data, State* initial_substate) : HState(data, initial_substate, <default_next_state>) {}

//OrthState
//Gate_End::Gate_End(ContextData* data) : OrthState(data, {new State1(data), new State2(data)}, <default_next_state> ) {}
//Gate_End::Gate_End(ContextData* data, std::deque<State*> initial_substates) : OrthState(data, initial_substates, <default_next_state>) {}

Gate_End::~Gate_End() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void Gate_End::entry() {
	PRINT_STATE;
	data->timer->start_timer(100, TIMER_ID::GATE_END);
}

void Gate_End::exit() {
	//HState::entry() //for HState
	//OrthState::entry() //for OrthState
	//Action here
	PRINT_STATE;
}

State* Gate_End::clone() {
	//return new Gate_End(data, substate->clone()); //for HState
	//return new Gate_End(data, substates_clone()); //for OrthState
	return new Gate_End(data);
}
State* Gate_End::request_transfer() {
	data->sender->send_event((int8_t) Topic::COM, (int) COM_Enum::FBM_2_BUSY);
	return nullptr;
}
State* Gate_End::timer(TIMER_ID id) {
	if(id != TIMER_ID::GATE_END) {
		return nullptr;
	}
	auto distance = data->piece_FBM2_soll->piece_tracker->get_distance();
	Area current_area = distance.first;

	if(current_area == Area::OUT_OF_RANGE) {
		DEBUG("PieceMissing! Cause: piece is too long to reach laser back.");
		return new Piece_Missing(data);
	}

	return new Gate_End(data);
}

State* Gate_End::laser_front_blocked() {
	return new Pieceappeared(data);
}

State* Gate_End::laser_sorting_gate_blocked() {
	return new Pieceappeared(data);
}

State* Gate_End::laser_ramp_blocked() {
	return new Pieceappeared(data);
}



State* Gate_End::laser_back_blocked() {
	auto distance = data->piece_FBM2_soll->piece_tracker->get_distance();
	Area current_area = distance.first;
	auto current_pos = distance.second;

	
	if(current_area == Area::GATE_END && current_pos > (100 - PIECE_TRANSITION_TOLERANCE)) {
		data->sender->send_event((int8_t) Topic::MOTOR_STOP_FSM, (int) data->piece_FBM2_soll->id);
		data->piece_FBM2_soll->piece_tracker->stop();
		return new End(data);
	}
	return new Pieceappeared(data);
}