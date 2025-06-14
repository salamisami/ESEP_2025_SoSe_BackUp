#include "ContextData.h"
#include "HState.h"

//================================================= constructors & destructors =================================================
ContextData::ContextData(){}
ContextData::ContextData(I_Sender* sender, I_Sender* to_self_sender) {
    this->sender = sender;
    stateStack = new std::stack<State*>();
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