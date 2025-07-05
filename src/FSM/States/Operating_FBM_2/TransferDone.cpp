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
void TransferDone::entry(){
	PRINT_STATE;
	//Action here
	//HState::entry() //for HState
	//OrthState::entry() //for OrthState
}
 
void TransferDone::exit(){
	//HState::entry() //for HState
	//OrthState::entry() //for OrthState
	//Action here
	PRINT_STATE;
}
 
State* TransferDone::clone(){
	//return new TransferDone(data, substate->clone()); //for HState
	//return new TransferDone(data, substates_clone()); //for OrthState
	return new TransferDone(data);
}