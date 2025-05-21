#ifndef CONTEXTDATA_H
#define CONTEXTDATA_H
#pragma once


#include "Timer.h"
#include <vector>
#include <stack>
#include <queue>

//forward declaration
class State;

class ContextData {
    //============================================ contructors & destructors ============================================
public:
    ContextData(int fsm_connectionID = -1);
    virtual ~ContextData();

    //================================================ public functions ================================================
public:
    //void publicFunction();


//================================================ private variables ================================================
public:
    std::stack<State*>* stateStack;
    Timer* timer;

};

#endif