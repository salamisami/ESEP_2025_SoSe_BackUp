#include "Is_Metal.h"
 
//================================================= constructors & destructors =================================================
Is_Metal::Is_Metal(ContextData* data) : State(data) {}
 
//HState
//Is_Metal::Is_Metal(ContextData* data) : HState(data, new SubState(data), <default_next_state> ) {}
//Is_Metal::Is_Metal(ContextData* data, State* initial_substate) : HState(data, initial_substate, <default_next_state>) {}
 
//OrthState
//Is_Metal::Is_Metal(ContextData* data) : OrthState(data, {new State1(data), new State2(data)}, <default_next_state> ) {}
//Is_Metal::Is_Metal(ContextData* data, std::deque<State*> initial_substates) : OrthState(data, initial_substates, <default_next_state>) {}
 
Is_Metal::~Is_Metal() {}
 
//===================================================== private functions =====================================================
 
 
//===================================================== public functions =====================================================
void Is_Metal::entry(){
	PRINT_STATE;
	//Action here
	//HState::entry() //for HState
	//OrthState::entry() //for OrthState
}
 
void Is_Metal::exit(){
	//HState::entry() //for HState
	//OrthState::entry() //for OrthState
	//Action here
	PRINT_STATE;
}
 
State* Is_Metal::clone(){
	//return new Is_Metal(data, substate->clone()); //for HState
	//return new Is_Metal(data, substates_clone()); //for OrthState
	return new Is_Metal(data);
}

State* Is_Metal::request_transfer() {

  };

  State* Is_Metal::laser_sorting_gate_blocked() {

  };

  State* Is_Metal::timer() {

  };

  State* Is_Metal::laser_ramp_blocked() {

  };

  State* Is_Metal::laser_back_blocked() {

  };

  State* Is_Metal::laser_front_blocked() {

  };

/
