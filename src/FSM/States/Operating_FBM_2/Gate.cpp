#include "Gate.h"
 
//================================================= constructors & destructors =================================================
Gate::Gate(ContextData* data) : State(data) {}
 
//HState
//Gate::Gate(ContextData* data) : HState(data, new SubState(data), <default_next_state> ) {}
//Gate::Gate(ContextData* data, State* initial_substate) : HState(data, initial_substate, <default_next_state>) {}
 
//OrthState
//Gate::Gate(ContextData* data) : OrthState(data, {new State1(data), new State2(data)}, <default_next_state> ) {}
//Gate::Gate(ContextData* data, std::deque<State*> initial_substates) : OrthState(data, initial_substates, <default_next_state>) {}
 
Gate::~Gate() {}
 
//===================================================== private functions =====================================================
 
 
//===================================================== public functions =====================================================
void Gate::entry(){
	PRINT_STATE;
	//Action here
	//HState::entry() //for HState
	//OrthState::entry() //for OrthState
}
 
void Gate::exit(){
	//HState::entry() //for HState
	//OrthState::entry() //for OrthState
	//Action here
	PRINT_STATE;
}
 
State* Gate::clone(){
	//return new Gate(data, substate->clone()); //for HState
	//return new Gate(data, substates_clone()); //for OrthState
	return new Gate(data);
}