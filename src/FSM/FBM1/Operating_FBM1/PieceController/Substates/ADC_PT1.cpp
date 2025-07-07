#include "ADC_PT1.h"

//================================================= constructors & destructors =================================================
ADC_PT1::ADC_PT1(ContextData* data, LocalDataPT1 localdata) : State(data), localdata_(localdata) {
	//substate = new SubState(data);
}

ADC_PT1::~ADC_PT1() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void ADC_PT1::entry() {
	PRINT_STATE;
	data->sender->send_event((int8_t) Topic::ADC, (int) ADC_Enum::ADC_MESURE);
	data->sender->send_event((int8_t) Topic::MOTOR_SLOW, (int) localdata_.id);
}

void ADC_PT1::exit() {
	PRINT_STATE;
}

State* ADC_PT1::clone() {
	return new ADC_PT1(data, localdata_);
}

State* ADC_PT1::adc_new_piece() {
	return new Measuring_PT1(data, localdata_);
}

State* ADC_PT1::adc_timeout() {
	DEBUG("PieceMissing! Cause: piece is too long in ADC.");
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
	Piece* piece_to_delete = data->pieces_map->at(localdata_.id);
	data->pieces_map->erase(localdata_.id);
	delete piece_to_delete;
	return State::EXIT_STATE;
}