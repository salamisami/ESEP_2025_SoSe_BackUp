#ifndef CONTEXTDATA_H
#define CONTEXTDATA_H
#pragma once


#include "Timer.h"
#include "QNet.h"
#include "PulseMsg.h"
#include <vector>
#include <stack>
#include <queue>

//forward declaration
class State;

class ContextData {
    //============================================ contructors & destructors ============================================
public:
    ContextData(I_Sender* sender, I_Receiver* receiver);
    virtual ~ContextData();

    //================================================ public functions ================================================
public:
    //void publicFunction();



//================================================ private variables ================================================
public:
    std::stack<State*>* stateStack;
    I_Sender* timer_sender;
    Timer* timer;
    I_Receiver* receiver;
    I_Sender* sender;

};

#endif