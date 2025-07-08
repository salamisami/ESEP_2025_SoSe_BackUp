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
    //TODO CODE
    data->sender->send_event((int8_t)Topic::ACTUATOR, (int)ActuatorEnum::TRAFFIC_RED_ON);
}

void MeasureFehlerQuittiert::exit(){
    //TODO CODE
	PRINT_STATE;
}

State* MeasureFehlerQuittiert::adc_top_area_unblocked() {
    return new ADCFrei(data);
}

State* MeasureFehlerQuittiert::clone() {
    return new MeasureFehlerQuittiert(data);
}