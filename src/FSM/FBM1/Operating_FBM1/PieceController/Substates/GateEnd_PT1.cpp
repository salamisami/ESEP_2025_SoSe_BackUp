#include "GateEnd_PT1.h"

//================================================= constructors & destructors =================================================
GateEnd_PT1::GateEnd_PT1(ContextData* data, LocalDataPT1 localdata) : State(data), localdata_(localdata) {
	//substate = new SubState(data);
}

GateEnd_PT1::~GateEnd_PT1() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void GateEnd_PT1::entry() {
	PRINT_STATE;
	//TODO set sort status
	data->timer->start_timer(UPDATE_PIECE_INTERVAL, TIMER_ID::GATEEND_PT1);
}

void GateEnd_PT1::exit() {
	PRINT_STATE;
}

State* GateEnd_PT1::clone() {
	return new GateEnd_PT1(data, localdata_);
}

State* GateEnd_PT1::timer(TIMER_ID id) {
	auto piece = localdata_.piece;
	auto distance = piece->piece_tracker->get_distance();
	Area current_area = distance.first;
	
	if(current_area == Area::OUT_OF_RANGE) {
		DEBUG("PieceMissing! Cause: piece is too long to reach laser back.");
	  MACRO_PIECE_MISSING_PT1
  }

	if(data->piece_near_adc) {
		data->sender->send_event((int8_t) Topic::MOTOR_STOP_FSM, (int) localdata_.piece->id);
		return new 	PendingTransferRequestNotAtEnd(data, localdata_);
	}
	return new GateEnd_PT1(data, localdata_);
}

State* GateEnd_PT1::laser_back_blocked() {
	auto piece = localdata_.piece;
	auto distance = piece->piece_tracker->get_distance();
	Area current_area = distance.first;
	auto current_pos = distance.second;

	if(current_area == Area::GATE_END && current_pos > (100 - PIECE_TRANSITION_TOLERANCE)) {
		data->sender->send_event((int8_t) Topic::MOTOR_STOP_FSM, (int) localdata_.piece->id);
		return new PendingTransferRequest_PT1(data, localdata_);
	}

	return nullptr;
}