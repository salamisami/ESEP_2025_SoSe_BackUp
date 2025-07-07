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
//TODO: Über motorcontrol ansteuern
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_SLOW_OFF);
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_RIGHT_START);
	data->piece_FBM2->piece_tracker.fast();
	data->timer->start_timer(100,TIMER_ID::ADC_GATE);
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

State* ADC_Gate::request_transfer() {
	data->sender->send_event((int8_t)Topic::COM, (int)COM_Enum::FBM_2_BUSY);
	return new ADC_Gate(data);
}
State* ADC_Gate::laser_back_blocked() {
	return new Pieceappeared(data);
}
State* ADC_Gate::laser_front_blocked() {
	return new Pieceappeared(data);
}
State* ADC_Gate::laser_ramp_blocked() {
	return new Pieceappeared(data);
}
State* ADC_Gate::laser_sorting_gate_blocked() {
	if 	((data->piece_FBM2->piece_tracker.get_distance().second >= WAY_TO_AREA && data->piece_FBM2->piece_tracker.get_distance().first == Area::ADC_GATE) ||
		(data->piece_FBM2->piece_tracker.get_distance().second <= OVER_AREA && data->piece_FBM2->piece_tracker.get_distance().first == Area::GATE)) {
		return new Gate(data);
	} else {
		return new Pieceappeared(data);
	}
}

State* ADC_Gate::timer(TIMER_ID id) {
	if(id == TIMER_ID::ADC_GATE) {
		if (data->piece_FBM2->piece_tracker.get_distance().second >= OVER_AREA && data->piece_FBM2->piece_tracker.get_distance().first == Area::GATE) {
			return new Piece_Missing(data);
		} else {
			return new ADC_Gate(data);
		}
	}
  return nullptr;
}

State *ADC_Gate::metal_detected(){
	return new Is_Metal(data);
}
