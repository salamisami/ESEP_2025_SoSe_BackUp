#include "StartCDS.h"

//================================================= constructors & destructors =================================================
StartCDS::StartCDS(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

StartCDS::~StartCDS() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void StartCDS::entry(){
	PRINT_STATE;
    data->stopwatch.start();
}

void StartCDS::exit(){
    PRINT_STATE;
}

State* StartCDS::adc_top_area_blocked(){
    return new PieceAtADCCDS(data);
}

State* StartCDS::clone() {
    return new StartCDS(data);
}