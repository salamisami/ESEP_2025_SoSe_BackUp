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
    State* current_state;
    while(!stateStack->empty()) {
        current_state = stateStack->top();  // For stack, use top() instead of iterating
        delete current_state;
        stateStack->pop();
    }
    delete stateStack;
}

//===================================================== private functions =====================================================

//void ContextData::privateFunction(){}

//===================================================== public functions =====================================================

//void ContextData::publicFunction(){}