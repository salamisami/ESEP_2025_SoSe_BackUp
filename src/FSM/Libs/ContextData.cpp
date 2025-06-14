#include "ContextData.h"
#include "State.h"

//================================================= constructors & destructors =================================================
ContextData::ContextData(){}
ContextData::ContextData(I_Sender* sender, I_Sender* to_self_sender) {
    this->sender = sender;
    stateStack = new std::stack<I_State*>();
    timer = new Timer(to_self_sender);
}


ContextData::~ContextData() {
    delete timer;
    delete stateStack;
}

//===================================================== private functions =====================================================

//void ContextData::privateFunction(){}

//===================================================== public functions =====================================================

//void ContextData::publicFunction(){}