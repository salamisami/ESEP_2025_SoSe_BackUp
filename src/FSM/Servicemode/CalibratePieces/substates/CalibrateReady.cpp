#include "CalibrateReady.h"

//================================================= contructors & destructors =================================================
CalibrateReady::CalibrateReady(ContextData* data) : State(data){

}

CalibrateReady::~CalibrateReady() {}

//===================================================== private functions =====================================================

//void CalibrateReady::privateFunction(){}

//===================================================== public functions =====================================================

void CalibrateReady::entry(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void CalibrateReady::exit(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

State* CalibrateReady::laser_front_blocked(){
    return new Calibrating(data);
}