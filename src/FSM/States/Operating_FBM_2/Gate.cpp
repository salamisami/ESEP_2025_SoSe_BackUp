#include "Gate.h"
 
//================================================= constructors & destructors =================================================
Gate::Gate(ContextData* data) : State(data) {}
 
//HState
//Gate::Gate(ContextData* data) : HState(data, new SubState(data), <default_next_state> ) {}
//Gate::Gate(ContextData* data, State* initial_substate) : HState(data, initial_substate, <default_next_state>) {}
 
//OrthState
//Gate::Gate(ContextData* data) : OrthState(data, {new State1(data), new State2(data)}, <default_next_state> ) {}
//Gate::Gate(ContextData* data, std::deque<State*> initial_substates) : OrthState(data, initial_substates, <default_next_state>) {}
 
Gate::~Gate() {}
//===================================================== private functions =====================================================
 
 
//===================================================== public functions =====================================================
void Gate::entry(){
	PRINT_STATE;
  Gate::check_piece();
	//Action here
	//HState::entry() //for HState
	//OrthState::entry() //for OrthState
}
 
void Gate::exit(){
	//HState::entry() //for HState
	//OrthState::entry() //for OrthState
	//Action here
	PRINT_STATE;
}
 
State* Gate::clone(){
	//return new Gate(data, substate->clone()); //for HState
	//return new Gate(data, substates_clone()); //for OrthState
	return new Gate(data);
}

State* Gate::laser_front_blocked(){
  return new PieceAppeared(data);
}

  State* Gate::laser_back_blocked(){
  return new PieceAppeared(data);
}

State* Gate::laser_ramp_blocked(){
  return new PieceAppeared(data);
}


State* Gate::request_transfer(){
  data->sender->send_event((int8_t) Topic::COM, (int) COM_Enum::FBM_2_BUSY);
  return new Gate(data);
}

State* Gate::check_piece(){
  //data->timer->start_timer(100, TIMER_ID::GATE_END);
  //return new Gate_End(data)
  //TODO: check if to sort out or let trough if (let trough) then compare measured vs saved
  return new Sorting_out(data);
}
