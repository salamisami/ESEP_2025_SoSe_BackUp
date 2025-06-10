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
    State::entry();
}

void CalibratePieces::exit(){
    State::exit();
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}