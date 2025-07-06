#include "ValidMeasure.h"


//================================================= constructors & destructors =================================================
ValidMeasure::ValidMeasure(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

ValidMeasure::~ValidMeasure() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void ValidMeasure::entry(){
	PRINT_STATE;
    //TODO CODE
}

void ValidMeasure::exit(){
    //TODO CODE
	PRINT_STATE;
}

State* ValidMeasure::adc_invalid_measure()
{
    return new MeasureFehlerUnquittiert(data);
}