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
    
    data->sender->send_event((int8_t)Topic::ACTUATOR, (int)ActuatorEnum::TRAFFIC_RED_ON_SLOW);
    data->sender->send_event((int8_t)Topic::MOTOR_STOP_FSM, (int) Error_Enum::ERROR_INVALID_MESURE);
    data->error_warning_counter->error_or_warning_occured();
}

void MeasureFehlerUnquittiert::exit(){
    
	PRINT_STATE;
}

State* MeasureFehlerUnquittiert::adc_top_area_unblocked() {
    return new ADCFreiUnquittiert(data);
}

State* MeasureFehlerUnquittiert::button_reset_released() {
    return new MeasureFehlerQuittiert(data);
}

State* MeasureFehlerUnquittiert::clone() {
    return new MeasureFehlerUnquittiert(data);
}
