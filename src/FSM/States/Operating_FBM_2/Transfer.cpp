#include "Transfer.h"
 
//================================================= constructors & destructors =================================================
Transfer::Transfer(ContextData* data) : State(data) {}
 
//HState
//Transfer::Transfer(ContextData* data) : HState(data, new SubState(data), <default_next_state> ) {}
//Transfer::Transfer(ContextData* data, State* initial_substate) : HState(data, initial_substate, <default_next_state>) {}
 
//OrthState
//Transfer::Transfer(ContextData* data) : OrthState(data, {new State1(data), new State2(data)}, <default_next_state> ) {}
//Transfer::Transfer(ContextData* data, std::deque<State*> initial_substates) : OrthState(data, initial_substates, <default_next_state>) {}
 
Transfer::~Transfer() {}
 
//===================================================== private functions =====================================================
 
 
//===================================================== public functions =====================================================
void Transfer::entry(){
	PRINT_STATE;
	//Action here
	//HState::entry() //for HState
	//OrthState::entry() //for OrthState
}
 
void Transfer::exit(){
	//HState::entry() //for HState
	//OrthState::entry() //for OrthState
	//Action here
	PRINT_STATE;
}
 
State* Transfer::clone(){
	//return new Transfer(data, substate->clone()); //for HState
	//return new Transfer(data, substates_clone()); //for OrthState
	return new Transfer(data);
}