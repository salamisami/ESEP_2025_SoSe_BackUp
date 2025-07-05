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
void Gate_End::entry(){
	PRINT_STATE;
	//Action here
	//HState::entry() //for HState
	//OrthState::entry() //for OrthState
}
 
void Gate_End::exit(){
	//HState::entry() //for HState
	//OrthState::entry() //for OrthState
	//Action here
	PRINT_STATE;
}
 
State* Gate_End::clone(){
	//return new Gate_End(data, substate->clone()); //for HState
	//return new Gate_End(data, substates_clone()); //for OrthState
	return new Gate_End(data);
}