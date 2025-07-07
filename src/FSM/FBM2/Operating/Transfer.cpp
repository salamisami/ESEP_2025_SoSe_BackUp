#include "Transfer.h"
 
//================================================= constructors & destructors =================================================
Transfer::Transfer(ContextData* data) : State(data) {}
 
//HState
//Transfer::Transfer(ContextData* data) : HState(data, new SubState(data), <default_next_state> ) {}
//Transfer::Transfer(ContextData* data, State* initial_substate) : HState(data, initial_substate, <default_next_state>) {}
 
//OrthState
//Transfer::Transfer(ContextData* data) : OrthState(data, {new State1(data), new State2(data)}, <default_next_state> ) {}
//Transfer::Transfer(ContextData* data, std::deque<State*> initial_substates) : OrthState(data, initial_substates, <default_next_state>) {}
 
Transfer::~Transfer() {}
 
//===================================================== private functions =====================================================
 
 
//===================================================== public functions =====================================================
void Transfer::entry(){
	PRINT_STATE;
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_SLOW_OFF);
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_RIGHT_START);
	data->piece_FBM2->piece_tracker->fast();
	
	//Action here
	//HState::entry() //for HState
	//OrthState::entry() //for OrthState
}
 
void Transfer::exit(){
	//HState::entry() //for HState
	//OrthState::entry() //for OrthState
	//Action here
	PRINT_STATE;
}
 
State* Transfer::clone(){
	//return new Transfer(data, substate->clone()); //for HState
	//return new Transfer(data, substates_clone()); //for OrthState
	return new Transfer(data);
}


State* Transfer::timer(TIMER_ID id) {
    if(id == TIMER_ID::TRANSFER_FAILED) {
		data->sender->send_event((int8_t) Topic::COM, (int) COM_Enum::TRANSFER_FAILED);
        return new Piece_Missing(data);
    }
    return nullptr;
}
State* Transfer::request_transfer(){
	data->sender->send_event((int8_t)Topic::COM, (int)COM_Enum::FBM_2_BUSY);
	return new Transfer(data);
}

State* Transfer::laser_back_unblocked(){
	return new Pieceappeared(data);
}
State* Transfer::laser_sorting_gate_blocked(){
	return new Pieceappeared(data);
}
State* Transfer::laser_ramp_blocked(){
	return new Pieceappeared(data);	
}
State* Transfer::laser_front_blocked(){
	data->sender->send_event((int8_t) Topic::COM, (int) COM_Enum::TRANSFER_DONE);
	return new TransferDone(data);
}
