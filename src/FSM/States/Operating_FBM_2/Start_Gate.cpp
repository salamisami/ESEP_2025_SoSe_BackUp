#include "Start_Gate.h"
 
//================================================= constructors & destructors =================================================
Start_Gate::Start_Gate(ContextData* data) : State(data) {}
 
//HState
//Start_Gate::Start_Gate(ContextData* data) : HState(data, new SubState(data), <default_next_state> ) {}
//Start_Gate::Start_Gate(ContextData* data, State* initial_substate) : HState(data, initial_substate, <default_next_state>) {}
 
//OrthState
//Start_Gate::Start_Gate(ContextData* data) : OrthState(data, {new State1(data), new State2(data)}, <default_next_state> ) {}
//Start_Gate::Start_Gate(ContextData* data, std::deque<State*> initial_substates) : OrthState(data, initial_substates, <default_next_state>) {}
 
Start_Gate::~Start_Gate() {}
 
//===================================================== private functions =====================================================
 
 
//===================================================== public functions =====================================================
void Start_Gate::entry(){
	PRINT_STATE;
	//Action here
	//HState::entry() //for HState
	//OrthState::entry() //for OrthState
}
 
void Start_Gate::exit(){
	//HState::entry() //for HState
	//OrthState::entry() //for OrthState
	//Action here
	PRINT_STATE;
}
 
State* Start_Gate::clone(){
	//return new Start_Gate(data, substate->clone()); //for HState
	//return new Start_Gate(data, substates_clone()); //for OrthState
	return new Start_Gate(data);
}