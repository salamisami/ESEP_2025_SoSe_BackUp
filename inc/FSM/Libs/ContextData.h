#ifndef CONTEXTDATA_H
#define CONTEXTDATA_H
#pragma once


#include "Timer.h"
#include "QNet.h"
//#include "State.h"
#include "Stopwatch.h"
#include "PieceTracker.h"
#include <vector>
#include <stack>
#include <queue>

//forward declaration
class State;

class ContextData {
    //============================================ constructors & destructors ============================================
public:
    /**
     * @brief Creates a context data by injecting the sender interface
     * @param sender to send events out
     * @param to_self_sender to send events to self
     */
    ContextData(I_Sender* sender, I_Sender* to_self_sender);
    ContextData();
    virtual ~ContextData();

    //================================================ public functions ================================================
public:



//================================================ private variables ================================================
public:
    Stopwatch stopwatch;
    TimeProfile timeprofile_fast;
    TimeProfile timeprofile_slow;
    //TODO implement a safe stack here, that returns nullptr if no elements left in the stack
    std::stack<State*>* stateStack;
    I_Sender* timer_sender;
    Timer* timer;
    I_Sender* sender;
    PieceTracker* piece_tracker;
    bool is_switch = false;

};

#endif