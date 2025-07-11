#include "WaitingForTransferStart.h"
 
//================================================= constructors & destructors =================================================
WaitingForTransferStart::WaitingForTransferStart(ContextData* data) : State(data) {}
 
//HState
//WaitingForTransferStart::WaitingForTransferStart(ContextData* data) : HState(data, new SubState(data), <default_next_state> ) {}
//WaitingForTransferStart::WaitingForTransferStart(ContextData* data, State* initial_substate) : HState(data, initial_substate, <default_next_state>) {}
 
//OrthState
//WaitingForTransferStart::WaitingForTransferStart(ContextData* data) : OrthState(data, {new State1(data), new State2(data)}, <default_next_state> ) {}
//WaitingForTransferStart::WaitingForTransferStart(ContextData* data, std::deque<State*> initial_substates) : OrthState(data, initial_substates, <default_next_state>) {}
 
WaitingForTransferStart::~WaitingForTransferStart() {}
 
//===================================================== private functions =====================================================
 
 
//===================================================== public functions =====================================================
void WaitingForTransferStart::entry(){
	PRINT_STATE;
	//Action here
	//HState::entry() //for HState
	//OrthState::entry() //for OrthState
}
 
void WaitingForTransferStart::exit(){
	//HState::entry() //for HState
	//OrthState::entry() //for OrthState
	//Action here
	PRINT_STATE;
}
 
State* WaitingForTransferStart::clone(){
	//return new WaitingForTransferStart(data, substate->clone()); //for HState
	//return new WaitingForTransferStart(data, substates_clone()); //for OrthState
	return new WaitingForTransferStart(data);
}

State* WaitingForTransferStart::request_transfer() {
	data->sender->send_event((int8_t)Topic::COM, (int)COM_Enum::FBM_2_BUSY);
	return nullptr;
}

State* WaitingForTransferStart::laser_front_blocked() {
	return new Pieceappeared(data);
	
}
State* WaitingForTransferStart::laser_sorting_gate_blocked() {
	return new Pieceappeared(data);
	
}

State* WaitingForTransferStart::laser_ramp_blocked() {
	return new Pieceappeared(data);
	
}
State* WaitingForTransferStart::laser_back_blocked() {
	return new Pieceappeared(data);	
}

State* WaitingForTransferStart::id() {
	int piece_id = data->event_payload;
	data->piece_FBM2_soll->id = piece_id;
	if(data->piece_FBM2_soll == nullptr){
		THROW("Id comes before type!");
	}
	Piece* next_piece = data->piece_FBM2_soll;
	//data->pieces_map->insert({ piece_id, next_piece });
	return new Transfer(data);
}

State* WaitingForTransferStart::transfer_start_other(){
	data->piece_FBM2_soll = new Piece(&data->timeprofile);
	data->piece_FBM2_soll->type = PieceEnum::UNKNOWN;
	return new Transfer(data);
}
State* WaitingForTransferStart::transfer_start_tall(){
	data->piece_FBM2_soll = new Piece(&data->timeprofile);
	data->piece_FBM2_soll->type = PieceEnum::TALL;
	return new Transfer(data);
}
State* WaitingForTransferStart::transfer_start_flat(){
	data->piece_FBM2_soll = new Piece(&data->timeprofile);
	data->piece_FBM2_soll->type = PieceEnum::FLAT;
	return new Transfer(data);
}
State* WaitingForTransferStart::transfer_start_tall_w_metal(){
	data->piece_FBM2_soll = new Piece(&data->timeprofile);
	data->piece_FBM2_soll->type = PieceEnum::TALL_WITH_METAL;
	return new Transfer(data);
}
State* WaitingForTransferStart::transfer_start_tall_sort_out(){
	data->piece_FBM2_soll = new Piece(&data->timeprofile);
	data->piece_FBM2_soll->type = PieceEnum::TALL_SORT_OUT;
	return new Transfer(data);
}
State* WaitingForTransferStart::transfer_start_tall_w_metal_sort_out(){
	data->piece_FBM2_soll = new Piece(&data->timeprofile);
	data->piece_FBM2_soll->type = PieceEnum::TALL_WITH_METAL_SORT_OUT;
	return new Transfer(data);
}
State* WaitingForTransferStart::transfer_start_flat_sort_out(){
	data->piece_FBM2_soll = new Piece(&data->timeprofile);
	data->piece_FBM2_soll->type = PieceEnum::FLAT_SORT_OUT;
	return new Transfer(data);
}
