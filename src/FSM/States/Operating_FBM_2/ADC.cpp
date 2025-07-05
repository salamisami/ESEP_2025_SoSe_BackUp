#include "ADC.h"
 
//================================================= constructors & destructors =================================================
ADC::ADC(ContextData* data) : State(data) {}
 
//HState
//ADC::ADC(ContextData* data) : HState(data, new SubState(data), <default_next_state> ) {}
//ADC::ADC(ContextData* data, State* initial_substate) : HState(data, initial_substate, <default_next_state>) {}
 
//OrthState
//ADC::ADC(ContextData* data) : OrthState(data, {new State1(data), new State2(data)}, <default_next_state> ) {}
//ADC::ADC(ContextData* data, std::deque<State*> initial_substates) : OrthState(data, initial_substates, <default_next_state>) {}
 
ADC::~ADC() {}
 
//===================================================== private functions =====================================================
 
 
//===================================================== public functions =====================================================
void ADC::entry(){
	PRINT_STATE;
	//Action here
	//HState::entry() //for HState
	//OrthState::entry() //for OrthState
}
 
void ADC::exit(){
	//HState::entry() //for HState
	//OrthState::entry() //for OrthState
	//Action here
	PRINT_STATE;
}
 
State* ADC::clone(){
	//return new ADC(data, substate->clone()); //for HState
	//return new ADC(data, substates_clone()); //for OrthState
	return new ADC(data);
}