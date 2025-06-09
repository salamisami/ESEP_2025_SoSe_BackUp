#ifndef CONTEXTDATA_H
#define CONTEXTDATA_H
#pragma once


#include "Timer.h"
#include "QNet.h"
#include "I_State.h"
#include <vector>
#include <stack>
#include <queue>

//forward declaration
//class I_State;

class ContextData {
    //============================================ contructors & destructors ============================================
public:
    ContextData(I_Sender* sender, I_Sender* timer_sender);
    ContextData();
    virtual ~ContextData();

    //================================================ public functions ================================================
public:
    //void publicFunction();



//================================================ private variables ================================================
public:
    //TODO implement a safe stack here, that returns nullptr if no elements left in the stack
    std::stack<I_State*>* stateStack;
    I_Sender* timer_sender;
    Timer* timer;
    I_Sender* sender;

};

#endif