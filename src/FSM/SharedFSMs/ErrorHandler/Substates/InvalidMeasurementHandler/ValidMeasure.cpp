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
    
}

void ValidMeasure::exit(){
    
	PRINT_STATE;
}

State* ValidMeasure::adc_invalid_measure()
{
    return new MeasureFehlerUnquittiert(data);
}

State* ValidMeasure::clone() {
    return new ValidMeasure(data);
}