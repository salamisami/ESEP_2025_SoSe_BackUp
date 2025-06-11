#include "ContextData.h"
#include "State.h"

//================================================= contructors & destructors =================================================
ContextData::ContextData(){}
ContextData::ContextData(I_Sender* sender, I_Sender* timer_sender) {
    this->sender = sender;
    stateStack = new std::stack<I_State*>();
    timer = new Timer(timer_sender);


}

ContextData::~ContextData() {
    delete timer;
    delete stateStack;
}

//===================================================== private functions =====================================================

//void ContextData::privateFunction(){}

//===================================================== public functions =====================================================

//void ContextData::publicFunction(){}