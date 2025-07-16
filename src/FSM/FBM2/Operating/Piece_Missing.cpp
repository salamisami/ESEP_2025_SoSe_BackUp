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
	//TODO move following commands to action on the previous states accordingly, in order to work with deep history
	data->sender->send_event((int8_t) Topic::ERROR, (int) Error_Enum::ERROR_W_LOST);
	if(data->piece_FBM2_soll == nullptr) {
		data->sender->send_event((int8_t) Topic::DELETE_W_MOTOR, (int) -1);
	} else {
		data->sender->send_event((int8_t) Topic::DELETE_W_MOTOR, (int) data->piece_FBM2_soll->id);
		delete data->piece_FBM2_soll;
		data->piece_FBM2_soll = nullptr;
	}
	printf("Piece Missing. Please press the Reset Button.\n");
	data->workpieceList.clean();	
	data->workpieces = false;
	data->motor_slowed = false;
	data->motor_stopped = false;
	delete data->piece_FBM2_soll;
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

