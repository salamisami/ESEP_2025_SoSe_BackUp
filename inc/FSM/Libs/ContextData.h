#ifndef CONTEXTDATA_H
#define CONTEXTDATA_H
#pragma once


#include "Timer.h"
#include "QNet.h"
#include "StateContainer.h"
//#include "State.h"
#include "Stopwatch.h"
#include "PieceTracker.h"
#include "Piece.h"
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
    int event_payload;
    Stopwatch stopwatch;
    TimeProfile timeprofile;
    CheckPiece_Enum actual_piece = CheckPiece_Enum::UNKNOWN;
    //TODO implement a safe stack here, that returns nullptr if no elements left in the stack
    std::stack<State*>* modehandler_history;
    std::stack<State*>* estop_history;

    //Piece piece;


    I_Sender* timer_sender;
    Timer* timer;
    I_Sender* sender;
    PieceTracker* piece_tracker;
    bool is_switch = false;
    bool is_ramp_full = false;

    bool workpieces = false;
    bool motor_slowed = false;
    bool motor_stopped = false;
    StateContainer workpieceList;
};

#endif
