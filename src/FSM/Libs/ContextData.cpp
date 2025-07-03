#include "ContextData.h"
#include "HState.h"

//================================================= constructors & destructors =================================================
ContextData::ContextData(){}
ContextData::ContextData(I_Sender* sender, I_Sender* to_self_sender) {
    this->sender = sender;
    this->estop_history = new std::stack<State*>();
    this->modehandler_history = new std::stack<State*>();
    timer = new Timer(to_self_sender);
}


ContextData::~ContextData() {
    delete timer;
    State* current_state;
    while(!estop_history->empty()) {
        current_state = estop_history->top();  // For stack, use top() instead of iterating
        delete current_state;
        estop_history->pop();
    }
    while(!modehandler_history->empty()) {
            current_state = modehandler_history->top();  // For stack, use top() instead of iterating
            delete current_state;
            modehandler_history->pop();
    }
    delete estop_history;
    delete modehandler_history;
}

//===================================================== private functions =====================================================

//void ContextData::privateFunction(){}

//===================================================== public functions =====================================================

//void ContextData::publicFunction(){}
