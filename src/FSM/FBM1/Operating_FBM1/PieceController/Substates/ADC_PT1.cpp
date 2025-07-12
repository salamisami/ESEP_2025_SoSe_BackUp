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
	data->sender->send_event((int8_t) Topic::MOTOR_SLOW, (int) localdata_.piece->id);
	localdata_.unblock_signal_has_been_sent = false;
	data->piece_near_adc++;
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
  MACRO_PIECE_MISSING_PT1
}
