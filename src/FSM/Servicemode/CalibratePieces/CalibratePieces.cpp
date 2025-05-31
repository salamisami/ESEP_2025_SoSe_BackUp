#include "CalibratePieces.h"

//================================================= contructors & destructors =================================================
CalibratePieces::CalibratePieces(ContextData* data, State* initial_substate) :State(data){
    if(initial_substate == nullptr) {
        substate = new CalibrateReady(data);
    } else {
        substate = initial_substate;
    }
}

CalibratePieces::~CalibratePieces() {}

void CalibratePieces::entry(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    substate->entry();
}

void CalibratePieces::exit(){
    substate->exit();
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

State* CalibratePieces::laser_front_blocked(){
    State* newSubstate = substate->laser_front_blocked();
    if(newSubstate != nullptr){
        //there is substate change, change only the substate
        substate->exit();
        delete substate;
        substate = newSubstate;
        substate->entry();
    }
    return nullptr;
}


State* CalibratePieces::adc_calibration_done(){
    State* newSubstate = substate->adc_calibration_done();
    if(newSubstate != nullptr){
        //there is substate change, change only the substate
        substate->exit();
        delete substate;
        substate = newSubstate;
        substate->entry();
    }
    return nullptr;
}