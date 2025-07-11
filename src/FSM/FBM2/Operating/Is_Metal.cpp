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
void Is_Metal::entry() {
  PRINT_STATE;
  data->scanned_piece_has_metal_fbm2 = true;
  //Action here
  //HState::entry() //for HState
  //OrthState::entry() //for OrthState
}

void Is_Metal::exit() {
  //HState::entry() //for HState
  //OrthState::entry() //for OrthState
  //Action here
  PRINT_STATE;
}

State* Is_Metal::clone() {
  //return new Is_Metal(data, substate->clone()); //for HState
  //return new Is_Metal(data, substates_clone()); //for OrthState
  return new Is_Metal(data);
}

State* Is_Metal::request_transfer() {
  data->sender->send_event((int8_t) Topic::COM, (int) COM_Enum::FBM_2_BUSY);
  return nullptr;
}

State* Is_Metal::laser_sorting_gate_blocked() {
  auto distance = data->piece_FBM2_soll->piece_tracker->get_distance();
  Area current_area = distance.first;
  auto current_pos = distance.second;
 
  if(current_area == Area::GATE) {
    return new LeavingGate_PT2(data);
  }

  return new Pieceappeared(data);
}

State* Is_Metal::timer(TIMER_ID id) {
	if(id != TIMER_ID::IS_METAL) {
		return nullptr;
	}
	auto distance = data->piece_FBM2_soll->piece_tracker->get_distance();
	Area current_area = distance.first;
	auto current_pos = distance.second;


	if(current_area == Area::ADC_GATE && current_pos < PIECE_TRANSITION_TOLERANCE){
		return new Is_Metal(data);
	}

	if(current_area == Area::ADC_GATE && current_pos >= PIECE_TRANSITION_TOLERANCE){
		return new Is_Metal(data);
	}

	if(current_area == Area::GATE && current_pos < PIECE_TRANSITION_TOLERANCE){
		return new Is_Metal(data);
	}
	return new Piece_Missing(data);
}


State* Is_Metal::laser_ramp_blocked() {
  return new Pieceappeared(data);
}

State* Is_Metal::laser_back_blocked() {
  return new Pieceappeared(data);
}

State* Is_Metal::laser_front_blocked() {
  return new Pieceappeared(data);
}
