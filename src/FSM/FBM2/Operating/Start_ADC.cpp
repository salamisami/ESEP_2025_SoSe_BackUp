#include "Start_ADC.h"

//================================================= constructors & destructors =================================================
Start_ADC::Start_ADC(ContextData* data) : State(data) {}

//HState
//Start_ADC::Start_ADC(ContextData* data) : HState(data, new SubState(data), <default_next_state> ) {}
//Start_ADC::Start_ADC(ContextData* data, State* initial_substate) : HState(data, initial_substate, <default_next_state>) {}

//OrthState
//Start_ADC::Start_ADC(ContextData* data) : OrthState(data, {new State1(data), new State2(data)}, <default_next_state> ) {}
//Start_ADC::Start_ADC(ContextData* data, std::deque<State*> initial_substates) : OrthState(data, initial_substates, <default_next_state>) {}

Start_ADC::~Start_ADC() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void Start_ADC::entry() {
	PRINT_STATE;
	data->timer->start_timer(100, TIMER_ID::START_ADC);
	//Action here
	//HState::entry() //for HState
	//OrthState::entry() //for OrthState
}

void Start_ADC::exit() {
	//HState::entry() //for HState
	//OrthState::entry() //for OrthState
	//Action here
	PRINT_STATE;
}

State* Start_ADC::clone() {
	//return new Start_ADC(data, substate->clone()); //for HState
	//return new Start_ADC(data, substates_clone()); //for OrthState
	return new Start_ADC(data);
}

State* Start_ADC::timer(TIMER_ID id)  {
	if(id != TIMER_ID::START_ADC) {
		return nullptr;
	}

	auto distance = data->piece_tracker->get_distance();
	Area current_area = distance.first;
	auto current_position = distance.second;

	//TODO calibrate here
	if(current_area == Area::START_ADC && current_position > DISTANCE_BETWEEN_PIECES && current_position <= (100 - PIECE_TRANSITION_TOLERANCE)) {
		return new Start_ADC(data);
	}

	if(current_area == Area::START_ADC && current_position > (100 - 20)) {
		return new ADC_State(data);
	}

	if(current_area != Area::START_ADC){
		return new ADC_State(data);
	}

	return new Start_ADC(data);
}

State* Start_ADC::request_transfer() {
	data->sender->send_event((int8_t) Topic::COM, (int) COM_Enum::FBM_2_BUSY);
	return nullptr;
}

State* Start_ADC::laser_back_blocked() {
	return new Pieceappeared(data);
}
State* Start_ADC::laser_front_blocked() {
	return new Pieceappeared(data);
}
State* Start_ADC::laser_sorting_gate_blocked() {
	return new Pieceappeared(data);
}
State* Start_ADC::laser_ramp_blocked() {
	return new Pieceappeared(data);
}
