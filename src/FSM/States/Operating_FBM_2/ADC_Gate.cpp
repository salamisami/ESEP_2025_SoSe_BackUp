#include "ADC_Gate.h"
 
//================================================= constructors & destructors =================================================
ADC_Gate::ADC_Gate(ContextData* data) : State(data) {}
 
//HState
//ADC_Gate::ADC_Gate(ContextData* data) : HState(data, new SubState(data), <default_next_state> ) {}
//ADC_Gate::ADC_Gate(ContextData* data, State* initial_substate) : HState(data, initial_substate, <default_next_state>) {}
 
//OrthState
//ADC_Gate::ADC_Gate(ContextData* data) : OrthState(data, {new State1(data), new State2(data)}, <default_next_state> ) {}
//ADC_Gate::ADC_Gate(ContextData* data, std::deque<State*> initial_substates) : OrthState(data, initial_substates, <default_next_state>) {}
 
ADC_Gate::~ADC_Gate() {}
 
//===================================================== private functions =====================================================
 
 
//===================================================== public functions =====================================================
void ADC_Gate::entry(){
	PRINT_STATE;
	//Action here
	//HState::entry() //for HState
	//OrthState::entry() //for OrthState
}
 
void ADC_Gate::exit(){
	//HState::entry() //for HState
	//OrthState::entry() //for OrthState
	//Action here
	PRINT_STATE;
}
 
State* ADC_Gate::clone(){
	//return new ADC_Gate(data, substate->clone()); //for HState
	//return new ADC_Gate(data, substates_clone()); //for OrthState
	return new ADC_Gate(data);
}