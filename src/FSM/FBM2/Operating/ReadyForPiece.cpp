#include "ReadyForPiece.h"
 
//================================================= constructors & destructors =================================================
ReadyForPiece::ReadyForPiece(ContextData* data) : State(data) {}
 
//HState
//ReadyForPiece::ReadyForPiece(ContextData* data) : HState(data, new SubState(data), <default_next_state> ) {}
//ReadyForPiece::ReadyForPiece(ContextData* data, State* initial_substate) : HState(data, initial_substate, <default_next_state>) {}
 
//OrthState
//ReadyForPiece::ReadyForPiece(ContextData* data) : OrthState(data, {new State1(data), new State2(data)}, <default_next_state> ) {}
//ReadyForPiece::ReadyForPiece(ContextData* data, std::deque<State*> initial_substates) : OrthState(data, initial_substates, <default_next_state>) {}
 
ReadyForPiece::~ReadyForPiece() {}
 
//===================================================== private functions =====================================================
 
 
//===================================================== public functions =====================================================
void ReadyForPiece::entry(){
	PRINT_STATE;
	//Action here
	//HState::entry() //for HState
	//OrthState::entry() //for OrthState
}
 
void ReadyForPiece::exit(){
	//HState::entry() //for HState
	//OrthState::entry() //for OrthState
	//Action here
	PRINT_STATE;
}
 
State* ReadyForPiece::clone(){
	//return new ReadyForPiece(data, substate->clone()); //for HState
	//return new ReadyForPiece(data, substates_clone()); //for OrthState
	return new ReadyForPiece(data);
}

State* ReadyForPiece::request_transfer() {
	DEBUG("Request_transfer");
	data->sender->send_event((int8_t)Topic::COM, (int)COM_Enum::FBM_2_READY);
	return nullptr;
}

State* ReadyForPiece::laser_front_blocked() {
	DEBUG("laser front blocked");
	return new Pieceappeared(data);
	
}
State* ReadyForPiece::laser_sorting_gate_blocked() {
	DEBUG("other");
	return new Pieceappeared(data);
	
}

State* ReadyForPiece::laser_ramp_blocked() {
	DEBUG("other");
	return new Pieceappeared(data);
	
}
State* ReadyForPiece::laser_back_blocked() {
	DEBUG("other");
	return new Pieceappeared(data);	
}

State* ReadyForPiece::id() {
	DEBUG("ID event comes in");
	int piece_id = data->event_payload;
	printf("Piece id is: %d\n", piece_id);
	data->piece_FBM2_soll->id = piece_id;
	data->sender->send_event((int8_t) Topic::MOTOR_FAST, data->piece_FBM2_soll->id);
	return new Transfer(data);
}


State* ReadyForPiece::transfer_start_other(){
	DEBUG("transfer start event comes in");
	data->piece_FBM2_soll = new Piece(&data->timeprofile);
	data->piece_FBM2_soll->type = PieceEnum::UNKNOWN;
	return nullptr;
}
State* ReadyForPiece::transfer_start_tall(){
	DEBUG("transfer start event comes in");
	data->piece_FBM2_soll = new Piece(&data->timeprofile);
	data->piece_FBM2_soll->type = PieceEnum::TALL;
	return nullptr;
}
State* ReadyForPiece::transfer_start_flat(){
	DEBUG("transfer start event comes in");
	data->piece_FBM2_soll = new Piece(&data->timeprofile);
	data->piece_FBM2_soll->type = PieceEnum::FLAT;
	return nullptr;
}
State* ReadyForPiece::transfer_start_tall_w_metal(){
	DEBUG("transfer start event comes in");
	data->piece_FBM2_soll = new Piece(&data->timeprofile);
	data->piece_FBM2_soll->type = PieceEnum::TALL_WITH_METAL;
	return nullptr;
}
State* ReadyForPiece::transfer_start_tall_sort_out(){
	DEBUG("transfer start event comes in");
	data->piece_FBM2_soll = new Piece(&data->timeprofile);
	data->piece_FBM2_soll->type = PieceEnum::TALL_SORT_OUT;
	return nullptr;
}
State* ReadyForPiece::transfer_start_tall_w_metal_sort_out(){
	DEBUG("transfer start event comes in");
	data->piece_FBM2_soll = new Piece(&data->timeprofile);
	data->piece_FBM2_soll->type = PieceEnum::TALL_WITH_METAL_SORT_OUT;
	return nullptr;
}
State* ReadyForPiece::transfer_start_flat_sort_out(){
	DEBUG("transfer start event comes in");
	data->piece_FBM2_soll = new Piece(&data->timeprofile);
	data->piece_FBM2_soll->type = PieceEnum::FLAT_SORT_OUT;
	return nullptr;
}
