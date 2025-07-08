#include "ADC_State.h"
 
//================================================= constructors & destructors =================================================
ADC_State::ADC_State(ContextData* data) : State(data) {}
 
//HState
//ADC::ADC(ContextData* data) : HState(data, new SubState(data), <default_next_state> ) {}
//ADC::ADC(ContextData* data, State* initial_substate) : HState(data, initial_substate, <default_next_state>) {}
 
//OrthState
//ADC::ADC(ContextData* data) : OrthState(data, {new State1(data), new State2(data)}, <default_next_state> ) {}
//ADC::ADC(ContextData* data, std::deque<State*> initial_substates) : OrthState(data, initial_substates, <default_next_state>) {}
 
ADC_State::~ADC_State() {}
 
//===================================================== private functions =====================================================
 
 
//===================================================== public functions =====================================================
void ADC_State::entry(){
	PRINT_STATE;
	data->sender->send_event((int8_t) Topic::ADC, (int) ADC_Enum::ADC_MESURE);
	data->sender->send_event((int8_t) Topic::MOTOR_SLOW, (int) data->piece_FBM2->id);
	//Action here
	//HState::entry() //for HState
	//OrthState::entry() //for OrthState
}
 
void ADC_State::exit(){
	//HState::entry() //for HState
	//OrthState::entry() //for OrthState
	//Action here
	PRINT_STATE;
}
 
State* ADC_State::clone(){
	//return new ADC(data, substate->clone()); //for HState
	//return new ADC(data, substates_clone()); //for OrthState
	return new ADC_State(data);
}

State* ADC_State::request_transfer(){
	data->sender->send_event((int8_t)Topic::COM, (int)COM_Enum::FBM_2_BUSY);
	return new ADC_State(data);
}
State* ADC_State::laser_back_blocked(){
	return new Pieceappeared(data);
}
State* ADC_State::laser_front_blocked(){
	return new Pieceappeared(data);
}
State* ADC_State::laser_sorting_gate_blocked(){
	return new Pieceappeared(data);
}
State* ADC_State::laser_ramp_blocked(){
	return new Pieceappeared(data);
}

State* ADC_State::adc_timeout(){
	return new Piece_Missing(data);
}
State* ADC_State::adc_new_piece(){
	return new Measuring(data);
}
