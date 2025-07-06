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

State* Measuring::request_transfer(){
	data->sender->send_event((int8_t)Topic::COM, (int)COM_Enum::FBM_2_BUSY);
	return new Measuring(data);
}
State* Measuring::laser_back_blocked(){
	return new piece_appeared(data);
}
State* Measuring::laser_front_blocked(){
	return new piece_appeared(data);
}
State* Measuring::laser_sorting_gate_blocked(){
	return new piece_appeared(data);
}
State* Measuring::laser_ramp_blocked(){
	return new piece_appeared(data);
}

State* Measuring::adc_wh_detect(){
	data->piece_FBM2_measured = new Piece();
	data->piece_FBM2_measured->type = PieceEnum::UNKNOWN;
	return new ADC_Gate(data);
}
State* Measuring::adc_wf_detect(){
	ata->piece_FBM2_measured = new Piece();
	data->piece_FBM2_measured->type = PieceEnum::FLAT;
	return new ADC_Gate(data);
}
State* Measuring::adc_wb_detect(){
	ata->piece_FBM2_measured = new Piece();
	data->piece_FBM2_measured->type = PieceEnum::TALL;
	return new ADC_Gate(data);
}
State* Measuring::adc_w_not_detect(){
	ata->piece_FBM2_measured = new Piece();
	data->piece_FBM2_measured->type = PieceEnum::UNKNOWN;
	return new ADC_Gate(data);
}