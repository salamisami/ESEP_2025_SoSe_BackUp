#include "Pieceappeared.h"

 
//================================================= constructors & destructors =================================================
Piece_appeared::Piece_appeared(ContextData* data) : State(data) {}
 
//HState
//PieceAppeared::PieceAppeared(ContextData* data) : HState(data, new SubState(data), <default_next_state> ) {}
//PieceAppeared::PieceAppeared(ContextData* data, State* initial_substate) : HState(data, initial_substate, <default_next_state>) {}
 
//OrthState
//PieceAppeared::PieceAppeared(ContextData* data) : OrthState(data, {new State1(data), new State2(data)}, <default_next_state> ) {}
//PieceAppeared::PieceAppeared(ContextData* data, std::deque<State*> initial_substates) : OrthState(data, initial_substates, <default_next_state>) {}
 
Piece_appeared::~Piece_appeared() {}
 
//===================================================== private functions =====================================================
 
 
//===================================================== public functions =====================================================
void Piece_appeared::entry(){
	PRINT_STATE;
	data->sender->send_event((int8_t) Topic::ERROR, (int) Error_Enum::ERROR_W_APPEARED);
	//Action here
	//HState::entry() //for HState
	//OrthState::entry() //for OrthState
}
 
void Piece_appeared::exit(){
	//HState::entry() //for HState
	//OrthState::entry() //for OrthState
	//Action here
	PRINT_STATE;
}
 
State* Piece_appeared::clone(){
	//return new PieceAppeared(data, substate->clone()); //for HState
	//return new PieceAppeared(data, substates_clone()); //for OrthState
	return new Piece_appeared(data);
}

<<<<<<< Updated upstream:src/FSM/States/Operating_FBM_2/Pieceappeared.cpp
State*  Piece_appeared::piece_appeared_resolved(){
=======
State*  PieceAppeared::piece_appeared_resolved(){
>>>>>>> Stashed changes:src/FSM/States/Operating_FBM_2/PieceAppeared.cpp
	return new ReadyForPiece(data);
}
State*  Piece_appeared::request_transfer(){
	data->sender->send_event((int8_t)Topic::COM, (int)COM_Enum::FBM_2_BUSY);
	return new Piece_appeared(data);				
}
