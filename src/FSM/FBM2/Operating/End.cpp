#include "End.h"
 
//================================================= constructors & destructors =================================================
End::End(ContextData* data) : State(data) {} 
 
End::~End() {}
 
//===================================================== private functions =====================================================
 
 
//===================================================== public functions =====================================================
void End::entry(){
	PRINT_STATE;
  data->piece_tracker->stop();
  data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_STOP);

	//Action here
	//HState::entry() //for HState
	//OrthState::entry() //for OrthState
}
 
void End::exit(){
	//HState::entry() //for HState
	//OrthState::entry() //for OrthState
	//Action here
	PRINT_STATE;
}
 
State* End::clone(){
	//return new Gate_End(data, substate->clone()); //for HState
	//return new Gate_End(data, substates_clone()); //for OrthState
	return new End(data);
} 
State* End::request_transfer(){
  data->sender->send_event((int8_t) Topic::COM, (int) COM_Enum::FBM_2_BUSY);
  return new End(data);
}

State* End::laser_front_blocked(){
  return new Pieceappeared(data);
}

State* End::laser_sorting_gate_blocked(){
  return new Pieceappeared(data);
}

State* End::laser_ramp_blocked(){
  return new Pieceappeared(data);
}

State* End::laser_back_unblocked(){
  data->sender->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::SORTED);
	
  return new ReadyForPiece(data);
}

