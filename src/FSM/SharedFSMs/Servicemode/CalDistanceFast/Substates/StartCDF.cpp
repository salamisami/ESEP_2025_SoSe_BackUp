#include "StartCDF.h"

//================================================= constructors & destructors =================================================
StartCDF::StartCDF(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

StartCDF::~StartCDF() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void StartCDF::entry(){
	PRINT_STATE;
    data->stopwatch.start();
}

void StartCDF::exit(){
    PRINT_STATE;
}

State* StartCDF::adc_top_area_blocked(){
    return new PieceAtADCCDF(data);
}