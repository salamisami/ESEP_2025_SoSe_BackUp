#include "TransferDone.h"

//================================================= constructors & destructors =================================================
TransferDone::TransferDone(ContextData* data) : State(data) {}

//HState
//TransferDone::TransferDone(ContextData* data) : HState(data, new SubState(data), <default_next_state> ) {}
//TransferDone::TransferDone(ContextData* data, State* initial_substate) : HState(data, initial_substate, <default_next_state>) {}

//OrthState
//TransferDone::TransferDone(ContextData* data) : OrthState(data, {new State1(data), new State2(data)}, <default_next_state> ) {}
//TransferDone::TransferDone(ContextData* data, std::deque<State*> initial_substates) : OrthState(data, initial_substates, <default_next_state>) {}

TransferDone::~TransferDone() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void TransferDone::entry() {
	PRINT_STATE;
	//Action here
	//HState::entry() //for HState
	//OrthState::entry() //for OrthState
}

void TransferDone::exit() {
	//HState::entry() //for HState
	//OrthState::entry() //for OrthState
	//Action here
	PRINT_STATE;
}

State* TransferDone::clone() {
	//return new TransferDone(data, substate->clone()); //for HState
	//return new TransferDone(data, substates_clone()); //for OrthState
	return new TransferDone(data);
}

State* TransferDone::request_transfer() {
	data->sender->send_event((int8_t) Topic::COM, (int) COM_Enum::FBM_2_BUSY);
	return nullptr;
}
State* TransferDone::laser_front_unblocked() {
	data->piece_FBM2_soll->piece_tracker->fast();
	if(data->piece_FBM2_soll->type == PieceEnum::FLAT_SORT_OUT ||
		data->piece_FBM2_soll->type == PieceEnum::TALL_SORT_OUT ||
		data->piece_FBM2_soll->type == PieceEnum::TALL_WITH_METAL_SORT_OUT ||
		data->piece_FBM2_soll->type == PieceEnum::UNKNOWN) {
		DEBUG("No Need to measure the piece. Piece muss raus!");
		return new Start_Gate(data);
	}
	
	if(data->piece_FBM2_soll->type == PieceEnum::FLAT ||
		data->piece_FBM2_soll->type == PieceEnum::TALL ||
		data->piece_FBM2_soll->type == PieceEnum::TALL_WITH_METAL) {
		return new Start_ADC(data);
	}
	return new Pieceappeared(data);
}
State* TransferDone::laser_sorting_gate_blocked() {
	return new Pieceappeared(data);
}
State* TransferDone::laser_ramp_blocked() {
	return new Pieceappeared(data);
}
State* TransferDone::laser_back_blocked() {
	return new Pieceappeared(data);
}
