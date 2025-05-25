#include "ContextData.h"
#include "State.h"

//================================================= contructors & destructors =================================================
ContextData::ContextData(){}
ContextData::ContextData(I_Sender* sender, I_Receiver* receiver) {
    this->sender = sender;
    this->receiver = receiver;
    stateStack = new std::stack<State*>();
    #ifdef MOCK
    timer_sender = new ChannelManager()
    timer_sender = new PulseMsg::Sender(receiver->getchid());
    timer = new Timer(timer_sender);


}

ContextData::~ContextData() {
    delete timer;
    delete timer_sender;
    delete stateStack;
}

//===================================================== private functions =====================================================

//void ContextData::privateFunction(){}

//===================================================== public functions =====================================================

//void ContextData::publicFunction(){}