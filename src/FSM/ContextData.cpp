#include "ContextData.h"
#include "State.h"

//================================================= contructors & destructors =================================================
ContextData::ContextData(int fsm_connectionID) {
    stateStack = new std::stack<State*>();
    if(fsm_connectionID > -1) {
        timer = new Timer(fsm_connectionID);
    }

}

ContextData::~ContextData() {
    delete stateStack;
}

//===================================================== private functions =====================================================

//void ContextData::privateFunction(){}

//===================================================== public functions =====================================================

//void ContextData::publicFunction(){}