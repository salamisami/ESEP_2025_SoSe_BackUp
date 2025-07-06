#include "Pieceappeared.h"

 
//================================================= constructors & destructors =================================================
Pieceappeared::Pieceappeared(ContextData* data) : State(data) {}
 
//HState
//PieceAppeared::PieceAppeared(ContextData* data) : HState(data, new SubState(data), <default_next_state> ) {}
//PieceAppeared::PieceAppeared(ContextData* data, State* initial_substate) : HState(data, initial_substate, <default_next_state>) {}
 
//OrthState
//PieceAppeared::PieceAppeared(ContextData* data) : OrthState(data, {new State1(data), new State2(data)}, <default_next_state> ) {}
//PieceAppeared::PieceAppeared(ContextData* data, std::deque<State*> initial_substates) : OrthState(data, initial_substates, <default_next_state>) {}
 
Pieceappeared::~Pieceappeared() {}
 
//===================================================== private functions =====================================================
 
 
//===================================================== public functions =====================================================
void Pieceappeared::entry(){
	PRINT_STATE;
	data->sender->send_event((int8_t) Topic::ERROR, (int) Error_Enum::ERROR_W_APPEARED);
	//Action here
	//HState::entry() //for HState
	//OrthState::entry() //for OrthState
}
 
void Pieceappeared::exit(){
	//HState::entry() //for HState
	//OrthState::entry() //for OrthState
	//Action here
	PRINT_STATE;
}
 
State* Pieceappeared::clone(){
	//return new PieceAppeared(data, substate->clone()); //for HState
	//return new PieceAppeared(data, substates_clone()); //for OrthState
	return new Pieceappeared(data);
}

State* Pieceappeared::piece_appeared_resolved(){
	return new ReadyForPiece(data);
}
State* Pieceappeared::request_transfer(){
	data->sender->send_event((int8_t)Topic::COM, (int)COM_Enum::FBM_2_BUSY);
	return new Pieceappeared(data);				
}
