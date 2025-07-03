#include "ADC_PT1.h"

//================================================= constructors & destructors =================================================
ADC_PT1::ADC_PT1(ContextData* data, LocalDataPT1 localdata) : State(data), localdata_(localdata) {
    //substate = new SubState(data);
}

ADC_PT1::~ADC_PT1() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void ADC_PT1::entry(){
	PRINT_STATE;
	data->sender->send_event((int8_t) Topic::ADC, (int) ADC_Enum::ADC_MESURE);
	data->sender->send_event((int8_t) Topic::MOTOR_SLOW, (int) localdata_.id);
}

void ADC_PT1::exit(){
	PRINT_STATE;
}

State* ADC_PT1::clone(){
	return new ADC_PT1(data, localdata_);
}

State* ADC_PT1::adc_new_piece() {
	return new Measuring_PT1(data, localdata_);
}

State* ADC_PT1::adc_timeout() {
	return new PieceMissing_PT1(data, localdata_);
}