#include "Sorting_out.h"
 
//================================================= constructors & destructors =================================================
Sorting_out::Sorting_out(ContextData* data) : State(data) {}
 
//HState
//Sorting_out::Sorting_out(ContextData* data) : HState(data, new SubState(data), <default_next_state> ) {}
//Sorting_out::Sorting_out(ContextData* data, State* initial_substate) : HState(data, initial_substate, <default_next_state>) {}
 
//OrthState
//Sorting_out::Sorting_out(ContextData* data) : OrthState(data, {new State1(data), new State2(data)}, <default_next_state> ) {}
//Sorting_out::Sorting_out(ContextData* data, std::deque<State*> initial_substates) : OrthState(data, initial_substates, <default_next_state>) {}
 
Sorting_out::~Sorting_out() {}
 
//===================================================== private functions =====================================================
 
 
//===================================================== public functions =====================================================
void Sorting_out::entry(){
	PRINT_STATE;
	//Action here
	//HState::entry() //for HState
	//OrthState::entry() //for OrthState
}
 
void Sorting_out::exit(){
	//HState::entry() //for HState
	//OrthState::entry() //for OrthState
	//Action here
	PRINT_STATE;
}
 
State* Sorting_out::clone(){
	//return new Sorting_out(data, substate->clone()); //for HState
	//return new Sorting_out(data, substates_clone()); //for OrthState
	return new Sorting_out(data);
}