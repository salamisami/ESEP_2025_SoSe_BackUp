#include "GateEnd_PT1.h"

//================================================= constructors & destructors =================================================
GateEnd_PT1::GateEnd_PT1(ContextData* data, LocalDataPT1 localdata) : State(data), localdata_(localdata) {
    //substate = new SubState(data);
}

GateEnd_PT1::~GateEnd_PT1() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void GateEnd_PT1::entry(){
	PRINT_STATE;
	data->timer->start_timer(100,TIMER_ID::GATEEND_PT1);
}

void GateEnd_PT1::exit(){
	PRINT_STATE;
}

State* GateEnd_PT1::clone(){
	return new GateEnd_PT1(data, localdata_);
}

State* GateEnd_PT1::timer(TIMER_ID id) {
	auto piece = data->pieces_map->at(localdata_.id);
	Area current_area = piece->piece_tracker.getArea();
	int current_position = piece->piece_tracker.getPosition();

	if(current_area == Area::GATE_END){
		data->sender->send_event((int8_t) Topic::MOTOR_STOP_FSM, (int) localdata_.id);
		return new 	PendingTransferRequestNotAtEnd(data, localdata_);
	}
	return nullptr;
}

State* GateEnd_PT1::laser_back_blocked() {
	auto piece = data->pieces_map->at(localdata_.id);
	Area current_area = piece->piece_tracker.getArea();
	int current_position = piece->piece_tracker.getPosition();

	if(current_area == Area::GATE_END){
		data->sender->send_event((int8_t) Topic::MOTOR_STOP_FSM, (int) localdata_.id);
		return new PendingTransferRequest_PT1(data, localdata_);
	}

	return nullptr;
}