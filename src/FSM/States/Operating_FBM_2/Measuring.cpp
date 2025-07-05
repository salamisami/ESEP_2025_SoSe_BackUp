#include "Measuring.h"
 
//================================================= constructors & destructors =================================================
Measuring::Measuring(ContextData* data) : State(data) {}
 
//HState
//Measuring::Measuring(ContextData* data) : HState(data, new SubState(data), <default_next_state> ) {}
//Measuring::Measuring(ContextData* data, State* initial_substate) : HState(data, initial_substate, <default_next_state>) {}
 
//OrthState
//Measuring::Measuring(ContextData* data) : OrthState(data, {new State1(data), new State2(data)}, <default_next_state> ) {}
//Measuring::Measuring(ContextData* data, std::deque<State*> initial_substates) : OrthState(data, initial_substates, <default_next_state>) {}
 
Measuring::~Measuring() {}
 
//===================================================== private functions =====================================================
 
 
//===================================================== public functions =====================================================
void Measuring::entry(){
	PRINT_STATE;
	//Action here
	//HState::entry() //for HState
	//OrthState::entry() //for OrthState
}
 
void Measuring::exit(){
	//HState::entry() //for HState
	//OrthState::entry() //for OrthState
	//Action here
	PRINT_STATE;
}
 
State* Measuring::clone(){
	//return new Measuring(data, substate->clone()); //for HState
	//return new Measuring(data, substates_clone()); //for OrthState
	return new Measuring(data);
}