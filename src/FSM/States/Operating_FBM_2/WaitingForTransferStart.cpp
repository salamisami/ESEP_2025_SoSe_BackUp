#include "WaitingForTransferStart.h"
 
//================================================= constructors & destructors =================================================
WaitingForTransferStart::WaitingForTransferStart(ContextData* data) : State(data) {}
 
//HState
//WaitingForTransferStart::WaitingForTransferStart(ContextData* data) : HState(data, new SubState(data), <default_next_state> ) {}
//WaitingForTransferStart::WaitingForTransferStart(ContextData* data, State* initial_substate) : HState(data, initial_substate, <default_next_state>) {}
 
//OrthState
//WaitingForTransferStart::WaitingForTransferStart(ContextData* data) : OrthState(data, {new State1(data), new State2(data)}, <default_next_state> ) {}
//WaitingForTransferStart::WaitingForTransferStart(ContextData* data, std::deque<State*> initial_substates) : OrthState(data, initial_substates, <default_next_state>) {}
 
WaitingForTransferStart::~WaitingForTransferStart() {}
 
//===================================================== private functions =====================================================
 
 
//===================================================== public functions =====================================================
void WaitingForTransferStart::entry(){
	PRINT_STATE;
	//Action here
	//HState::entry() //for HState
	//OrthState::entry() //for OrthState
}
 
void WaitingForTransferStart::exit(){
	//HState::entry() //for HState
	//OrthState::entry() //for OrthState
	//Action here
	PRINT_STATE;
}
 
State* WaitingForTransferStart::clone(){
	//return new WaitingForTransferStart(data, substate->clone()); //for HState
	//return new WaitingForTransferStart(data, substates_clone()); //for OrthState
	return new WaitingForTransferStart(data);
}