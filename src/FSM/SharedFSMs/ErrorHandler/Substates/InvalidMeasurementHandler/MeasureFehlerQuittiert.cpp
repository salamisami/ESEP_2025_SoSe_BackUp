#include "MeasureFehlerQuittiert.h"


//================================================= constructors & destructors =================================================
MeasureFehlerQuittiert::MeasureFehlerQuittiert(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

MeasureFehlerQuittiert::~MeasureFehlerQuittiert() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void MeasureFehlerQuittiert::entry(){
	PRINT_STATE;
    
    data->sender->send_event((int8_t)Topic::ACTUATOR, (int)ActuatorEnum::TRAFFIC_RED_ON);
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::LED_RESET_ON);
}

void MeasureFehlerQuittiert::exit(){
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::LED_RESET_OFF);
	PRINT_STATE;
    
}

State* MeasureFehlerQuittiert::adc_top_area_unblocked() {
    return new ADCFrei(data);
}

State* MeasureFehlerQuittiert::clone() {
    return new MeasureFehlerQuittiert(data);
}