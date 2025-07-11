#include "Piece_Missing.h"

//================================================= constructors & destructors =================================================
Piece_Missing::Piece_Missing(ContextData* data) : State(data) {}

//HState
//Piece_Missing::Piece_Missing(ContextData* data) : HState(data, new SubState(data), <default_next_state> ) {}
//Piece_Missing::Piece_Missing(ContextData* data, State* initial_substate) : HState(data, initial_substate, <default_next_state>) {}

//OrthState
//Piece_Missing::Piece_Missing(ContextData* data) : OrthState(data, {new State1(data), new State2(data)}, <default_next_state> ) {}
//Piece_Missing::Piece_Missing(ContextData* data, std::deque<State*> initial_substates) : OrthState(data, initial_substates, <default_next_state>) {}

Piece_Missing::~Piece_Missing() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void Piece_Missing::entry() {
	PRINT_STATE;
	//TODO move following commands to action on the previous states accordingly
	data->sender->send_event((int8_t) Topic::ERROR, (int) Error_Enum::ERROR_W_LOST);
	if(data->piece_FBM2_soll == nullptr) {
		data->sender->send_event((int8_t) Topic::MOTOR_STOP_FSM, (int) -1);
	} else {
		int id_to_delete = data->piece_FBM2_soll->id;
		data->sender->send_event((int8_t) Topic::MOTOR_STOP_FSM, (int) id_to_delete);
		data->pieces_map->erase(id_to_delete);
		delete data->piece_FBM2_soll;
		data->piece_FBM2_soll = nullptr;
	}
	//Action here
	//HState::entry() //for HState
	//OrthState::entry() //for OrthState
}

void Piece_Missing::exit() {
	//HState::entry() //for HState
	//OrthState::entry() //for OrthState
	//Action here
	PRINT_STATE;
}

State* Piece_Missing::clone() {
	//return new Piece_Missing(data, substate->clone()); //for HState
	//return new Piece_Missing(data, substates_clone()); //for OrthState
	return new Piece_Missing(data);
}
State* Piece_Missing::request_transfer() {
	data->sender->send_event((int8_t) Topic::COM, (int) COM_Enum::FBM_2_BUSY);
	return nullptr;
}

State* Piece_Missing::piece_lost_resolved() {

	return new ReadyForPiece(data);
}

