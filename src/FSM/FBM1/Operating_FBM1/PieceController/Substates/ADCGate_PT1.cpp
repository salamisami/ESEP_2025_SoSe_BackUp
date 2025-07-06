#include "ADCGate_PT1.h"



//================================================= constructors & destructors =================================================
ADCGate_PT1::ADCGate_PT1(ContextData* data, LocalDataPT1 localdata) : State(data), localdata_(localdata) {
	//substate = new SubState(data);
}

ADCGate_PT1::~ADCGate_PT1() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void ADCGate_PT1::entry() {
	PRINT_STATE;
	data->timer->start_timer(UPDATE_PIECE_INTERVAL, TIMER_ID::ADCGATE_PT1);
}

void ADCGate_PT1::exit() {
	PRINT_STATE;
}

State* ADCGate_PT1::clone() {
	return new ADCGate_PT1(data, localdata_);
}

State* ADCGate_PT1::timer(TIMER_ID id) {
	if(id != TIMER_ID::ADCGATE_PT1) {
		return nullptr;
	}
	auto piece = data->pieces_map->at(localdata_.id);
	auto distance = piece->piece_tracker.get_distance();
	Area current_area = distance.first;
	auto current_pos = distance.second;

	piece->piece_tracker.print_distance();

	switch(current_area) {
		case Area::ADC_GATE:
			return new ADCGate_PT1(data, localdata_);
			break;
		case Area::GATE:
			if(current_pos < PIECE_TRANSITION_TOLERANCE) {
				return new ADCGate_PT1(data, localdata_);
			}
		default:
			break;
	}
	DEBUG("PieceMissing!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
	std::cout << std::string(__PRETTY_FUNCTION__) << std::endl;
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

State* ADCGate_PT1::laser_sorting_gate_blocked() {
	auto piece = data->pieces_map->at(localdata_.id);
	auto distance = piece->piece_tracker.get_distance();
	Area current_area = distance.first;
	auto current_pos = distance.second;

	if(current_area == Area::ADC_GATE && current_pos > (100 - PIECE_TRANSITION_TOLERANCE_GATE)) {
		return new Gate_PT1(data, localdata_);
	}

	if(current_area == Area::GATE) {
		return new Gate_PT1(data, localdata_);
	}
	return nullptr;
}

State* ADCGate_PT1::metal_detected() {
	auto piece = data->pieces_map->at(localdata_.id);
	auto distance = piece->piece_tracker.get_distance();
	Area current_area = distance.first;
	auto current_pos = distance.second;

	if(current_area == Area::ADC_GATE && current_pos > (100 - PIECE_TRANSITION_TOLERANCE_GATE)) {
		return new IsMetal_PT1(data, localdata_);
	}

	if(current_area == Area::GATE) {
		return new IsMetal_PT1(data, localdata_);
	}
	return nullptr;
}