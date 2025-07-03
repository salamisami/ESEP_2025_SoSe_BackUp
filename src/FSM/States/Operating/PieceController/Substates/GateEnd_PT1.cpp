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
	data->timer->start_timer(100, TIMER_ID::GATEEND_PT1);
}

void GateEnd_PT1::exit() {
	PRINT_STATE;
}

State* GateEnd_PT1::clone() {
	return new GateEnd_PT1(data, localdata_);
}

State* GateEnd_PT1::timer(TIMER_ID id) {
	auto piece = data->pieces_map->at(localdata_.id);
	Area current_area = piece->piece_tracker.getArea();
	int current_position = piece->piece_tracker.getPosition();

	if(current_area != Area::GATE_END) {
		//PieceMissing
		data->sender->send_event((int8_t) Topic::ERROR, (int) Error_Enum::ERROR_W_LOST);
		data->sender->send_event((int8_t) Topic::DELETE_W_MOTOR, (int) localdata_.id);
		PieceEnum validated_piece = localdata_.validated_type;
		switch(validated_piece) {
			case PieceEnum::FLAT:
				data->sender->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::RESET_TO_FLAT);
				break;
			case PieceEnum::TALL:
				data->sender->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::RESET_TO_TALL);
				break;
			case PieceEnum::TALL_WITH_METAL:
				data->sender->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::RESET_TO_TALL_W_METAL);
				break;
			default:
				break;
		}
		return State::EXIT_STATE;
	}

	if(data->piece_near_adc) {
		data->sender->send_event((int8_t) Topic::MOTOR_STOP_FSM, (int) localdata_.id);
		return new 	PendingTransferRequestNotAtEnd(data, localdata_);
	}
	return new GateEnd_PT1(data, localdata_);
}

State* GateEnd_PT1::laser_back_blocked() {
	auto piece = data->pieces_map->at(localdata_.id);
	Area current_area = piece->piece_tracker.getArea();
	int current_position = piece->piece_tracker.getPosition();

	if(current_area == Area::GATE_END) {
		data->sender->send_event((int8_t) Topic::MOTOR_STOP_FSM, (int) localdata_.id);
		return new PendingTransferRequest_PT1(data, localdata_);
	}

	return nullptr;
}

State* GateEnd_PT1::let_through() {
	return new GateEnd_PT1(data, localdata_);
}

State* GateEnd_PT1::sort_out_fbm2() {
	return new GateEnd_PT1(data, localdata_);
