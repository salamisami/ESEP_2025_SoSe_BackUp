#include "MeasureFehlerUnquittiert.h"


//================================================= constructors & destructors =================================================
MeasureFehlerUnquittiert::MeasureFehlerUnquittiert(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

MeasureFehlerUnquittiert::~MeasureFehlerUnquittiert() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void MeasureFehlerUnquittiert::entry(){
	PRINT_STATE;
    //TODO CODE
    data->sender->send_event((int8_t)Topic::ACTUATOR, (int)ActuatorEnum::TRAFFIC_RED_ON_SLOW);
    data->sender->send_event((int8_t)Topic::MOTOR_STOP_FSM, data->event_payload);
}

void MeasureFehlerUnquittiert::exit(){
    //TODO CODE
	PRINT_STATE;
}

State* MeasureFehlerUnquittiert::adc_top_area_unblocked() {
    return new ADCFreiUnquittiert(data);
}

State* MeasureFehlerUnquittiert::button_reset_released() {
    return new ValidMeasure(data);
}

State* MeasureFehlerUnquittiert::clone() {
    return new MeasureFehlerUnquittiert(data);
}