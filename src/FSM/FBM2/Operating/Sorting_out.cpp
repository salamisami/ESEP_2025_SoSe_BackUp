#include "Sorting_out.h"
 
//================================================= constructors & destructors =================================================
Sorting_out::Sorting_out(ContextData* data) : State(data) {}
 
//HState
//Sorting_out::Sorting_out(ContextData* data) : HState(data, new SubState(data), <default_next_state> ) {}
//Sorting_out::Sorting_out(ContextData* data, State* initial_substate) : HState(data, initial_substate, <default_next_state>) {}
 
//OrthState
//Sorting_out::Sorting_out(ContextData* data) : OrthState(data, {new State1(data), new State2(data)}, <default_next_state> ) {}
//Sorting_out::Sorting_out(ContextData* data, std::deque<State*> initial_substates) : OrthState(data, initial_substates, <default_next_state>) {}
 
Sorting_out::~Sorting_out() {}
 
//===================================================== private functions =====================================================
 
 
//===================================================== public functions =====================================================
void Sorting_out::entry(){
	PRINT_STATE;
  data->timer->start_timer(100, TIMER_ID::SORTING_OUT);
  data->stopwatch.start();
  
	//Action here
	//HState::entry() //for HState
	//OrthState::entry() //for OrthState
}
 
void Sorting_out::exit(){
	//HState::entry() //for HState
	//OrthState::entry() //for OrthState
	//Action here
	data->sender->send_event((int8_t) Topic::DELETE_W_MOTOR, data->piece_FBM2->id);
  PRINT_STATE;
  data->sort_out_time = data->stopwatch.stop();
}
 
State* Sorting_out::clone(){
	//return new Sorting_out(data, substate->clone()); //for HState
	//return new Sorting_out(data, substates_clone()); //for OrthState
	return new Sorting_out(data);
}

State* Sorting_out::timer(TIMER_ID id) {
	if(id == TIMER_ID::SORTING_OUT){
    return new Piece_Missing(data);
  }
  return nullptr;
} 
State* Sorting_out::laser_ramp_blocked(){
  return new ReadyForPiece(data);
};
State* Sorting_out::laser_back_blocked(){
  return new Pieceappeared(data);
}
State* Sorting_out::laser_front_blocked(){
  return new Pieceappeared(data);
}
State* Sorting_out::laser_gate_blocked(){
  return new Pieceappeared(data);
}
State* Sorting_out::request_transfer(){
  data->sender->send_event((int8_t) Topic::COM, (int) COM_Enum::FBM_2_BUSY);
  return nullptr;
}

