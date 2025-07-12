#include "ReadyForPiece.h"

//================================================= constructors & destructors =================================================
ReadyForPiece::ReadyForPiece(ContextData* data) : State(data) {}

//HState
//ReadyForPiece::ReadyForPiece(ContextData* data) : HState(data, new SubState(data), <default_next_state> ) {}
//ReadyForPiece::ReadyForPiece(ContextData* data, State* initial_substate) : HState(data, initial_substate, <default_next_state>) {}

//OrthState
//ReadyForPiece::ReadyForPiece(ContextData* data) : OrthState(data, {new State1(data), new State2(data)}, <default_next_state> ) {}
//ReadyForPiece::ReadyForPiece(ContextData* data, std::deque<State*> initial_substates) : OrthState(data, initial_substates, <default_next_state>) {}

ReadyForPiece::~ReadyForPiece() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void ReadyForPiece::entry() {
	PRINT_STATE;
	//Action here
	//HState::entry() //for HState
	//OrthState::entry() //for OrthState
}

void ReadyForPiece::exit() {
	//HState::entry() //for HState
	//OrthState::entry() //for OrthState
	//Action here
	PRINT_STATE;
}

State* ReadyForPiece::clone() {
	//return new ReadyForPiece(data, substate->clone()); //for HState
	//return new ReadyForPiece(data, substates_clone()); //for OrthState
	return new ReadyForPiece(data);
}

State* ReadyForPiece::laser_front_blocked() {
	return new Pieceappeared(data);

}
State* ReadyForPiece::laser_sorting_gate_blocked() {
	return new Pieceappeared(data);

}

State* ReadyForPiece::laser_ramp_blocked() {
	return new Pieceappeared(data);

}
State* ReadyForPiece::laser_back_blocked() {
	return new Pieceappeared(data);

}
State* ReadyForPiece::request_transfer() {
	data->sender->send_event((int8_t) Topic::COM, (int) COM_Enum::FBM_2_READY);
	return new WaitingForTransferStart(data);

}
