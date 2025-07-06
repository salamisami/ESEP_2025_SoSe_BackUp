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
	return new ReadyForPiece(data);
}

tate* WaitingForTransferStart::laser_front_blocked() {
	return new Piece_appeared(data);
	
}
State* WaitingForTransferStart::laser_sorting_gate_blocked() {
	return new Piece_appeared(data);
	
}

State* WaitingForTransferStart::laser_ramp_blocked() {
	return new Piece_appeared(data);
	
}
State* WaitingForTransferStart::laser_back_blocked() {
	return new Piece_appeared(data);
	
}

State* WaitingForTransferStart::transfer_start_other(){
	data->Piece_FBM2 = new Piece();
	data->Piece_FBM2->type = PieceEnum::UNKNOWN;
	data->timer->start_timer(1000,TIMER_ID::TRANSFER_FAILED);
	return new Transfer(data);
}
State* WaitingForTransferStart::transfer_start_tall(){
	data->Piece_FBM2 = new Piece();
	data->Piece_FBM2->type = PieceEnum::TALL;
	data->timer->start_timer(1000,TIMER_ID::TRANSFER_FAILED);
	return new Transfer(data);
}
State* WaitingForTransferStart::transfer_start_flat(){
	ata->Piece_FBM2 = new Piece();
	data->Piece_FBM2->type = PieceEnum::FLAT;
	data->timer->start_timer(1000,TIMER_ID::TRANSFER_FAILED);
	return new Transfer(data);
}
State* WaitingForTransferStart::transfer_start_tall_w_metal(){
	data->Piece_FBM2 = new Piece();
	data->Piece_FBM2->type = PieceEnum::TALL_WITH_METAL;
	data->timer->start_timer(1000,TIMER_ID::TRANSFER_FAILED);
	return new Transfer(data);
}
State* WaitingForTransferStart::transfer_start_tall_sort_out(){
	data->Piece_FBM2 = new Piece();
	data->Piece_FBM2->type = PieceEnum::TALL_SORT_OUT;
	data->timer->start_timer(1000,TIMER_ID::TRANSFER_FAILED);
	return new Transfer(data);
}
State* WaitingForTransferStart::transfer_start_tall_w_metal_sort_out(){
	data->Piece_FBM2 = new Piece();
	data->Piece_FBM2->type = PieceEnum::TALL_WITH_METAL_SORT_OUT;
	data->timer->start_timer(1000,TIMER_ID::TRANSFER_FAILED);
	return new Transfer(data);
}
State* WaitingForTransferStart::transfer_start_flat_sort_out(){
	data->Piece_FBM2 = new Piece();
	data->Piece_FBM2->type = PieceEnum::FLAT_SORT_OUT;
	data->timer->start_timer(1000,TIMER_ID::TRANSFER_FAILED);
	return new Transfer(data);
}
