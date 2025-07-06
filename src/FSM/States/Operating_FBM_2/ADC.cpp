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
	data->sender->send_event((int8_t) Topic::ADC, (int) ADC_Enum::ADC_MESURE);
	data->piece_FBM2->piece_tracker.slow();

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

State* ADC::request_transfer(){
	data->sender->send_event((int8_t)Topic::COM, (int)COM_Enum::FBM_2_BUSY);
	return new ADC(data);
}
State* ADC::laser_back_blocked(){
	return new piece_appeared(data);
}
State* ADC::laser_front_blocked(){
	return new piece_appeared(data);
}
State* ADC::laser_sorting_gate_blocked(){
	return new piece_appeared(data);
}
State* ADC::laser_ramp_blocked(){
	return new piece_appeared(data);
}

State* ADC::ADC_Timeout(){
	return new Piece_Missing(data);
}
State* ADC::ADC_new_piece(){
	return new Measuring(data);
}