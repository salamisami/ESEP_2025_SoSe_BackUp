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
#include <unordered_map>

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
    PieceTracker piece_tracker = PieceTracker(true);
    std::stack<State*>* modehandler_history;
    std::stack<State*>* estop_history;
    std::unordered_map<int, Piece>* pieces_map;
    int available_id = 0;
    
    // int piece_id = 0;
    // CheckPiece_Enum ist_type = CheckPiece_Enum::UNKNOWN;
    // CheckPiece_Enum soll_type = CheckPiece_Enum::UNKNOWN;
    // long sorting_time = 0;
    // PieceTracker* piece_tracker;


    I_Sender* timer_sender;
    Timer* timer;
    I_Sender* sender;
    bool is_switch = false;
    bool is_ramp_full = false;

    bool workpieces = false;
    bool motor_slowed = false;
    bool motor_stopped = false;
    StateContainer workpieceList;
};

#endif
