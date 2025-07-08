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
  //Gate::check_piece();
	//Action here
  /* alte Lösung 
  data->timer->start_timer(1, TIMER_ID::GATE_FBM_2); 
  */
  check_piece();
  piece_data = data->piece_FBM2_measured;
  data->piece_tracker->update_distance_force(Area::GATE, 0);
  data->sender->send_event((int8_t)Topic::CHECK_PIECE, (int) piece_data);
	printf("PT1 -> Sorting Order: %d\n", (int) piece_data);
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
  return new Pieceappeared(data);
}

  State* Gate::laser_back_blocked(){
  return new Pieceappeared(data);
}

State* Gate::laser_ramp_blocked(){
  return new Pieceappeared(data);
}


State* Gate::request_transfer(){
  data->sender->send_event((int8_t) Topic::COM, (int) COM_Enum::FBM_2_BUSY);
  return new Gate(data);
}

State* Gate::let_through()
{
  return new LeavingGate_PT2(data);
}

State* Gate::sorting_out_fbm2()
{
  return new Sorting_out(out);
}


State* Gate::check_piece(){
	//soll: data->piece_FBM2
	//ist: data->piece_FBM2_measured
  
  //if (data->piece_FBM2_measured != data->piece_FBM2){
  switch (data->piece_FBM2->type)
  {
    case PieceEnum::TALL_WITH_METAL:
      if (PieceEnum::TALL != data->piece_FBM2_measured->type){
        printf("_____________piece_measured (%d) != piece (%d)___________________\n");
        data->sender->send_event((int8_t) Topic::Internal, (int) Internal_Enum::SORTING_OUT_FBM2);
      }
      else data->sender->send_event((int8_t) Topic::Internal, (int) Internal_Enum::LET_THROUGH);
      break;
    case PieceEnum::TALL_SORT_OUT:
      data->sender->send_event((int8_t) Topic::Internal, (int) Internal_Enum::SORTING_OUT_FBM2);
      break;
    case PieceEnum::TALL_WITH_METAL_SORT_OUT:
      data->sender->send_event((int8_t) Topic::Internal, (int) Internal_Enum::SORTING_OUT_FBM2);
      break;
    case PieceEnum::FLAT_SORT_OUT:
      data->sender->send_event((int8_t) Topic::Internal, (int) Internal_Enum::SORTING_OUT_FBM2);
      break;
    case PieceEnum::UNKNOWN:
      data->sender->send_event((int8_t) Topic::Internal, (int) Internal_Enum::SORTING_OUT_FBM2);
      break;
    default:
      if (data->piece_FBM2->type != data->piece_FBM2_measured->type){
        printf("_____________piece_measured (%d) != piece (%d)___________________\n");
        data->sender->send_event((int8_t) Topic::Internal, (int) Internal_Enum::SORTING_OUT_FBM2);
      }
      else data->sender->send_event((int8_t) Topic::Internal, (int) Internal_Enum::LET_THROUGH);
      break;
  }
  
  /* if(data->piece_FBM2_measured->type >= PieceEnum::TALL_SORT_OUT
      && data->piece_FBM2_measured->type <= PieceEnum::FLAT_SORT_OUT){
    printf("_____________sort out___________________\n");
    data->sender->send_event((int8_t) Topic::Internal, (int) Internal_Enum::SORTING_OUT_FBM2);
  } */
  /* data->timer->start_timer(100, TIMER_ID::GATE_END);
  printf("_____________return Gate End___________________\n");
  data->sender->send_event((int8_t) Topic::Internal, (int) Internal_Enum::LET_THROUGH); */
}

