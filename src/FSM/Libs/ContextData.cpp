#include "ContextData.h"
#include "HState.h"

//================================================= constructors & destructors =================================================
ContextData::ContextData() {}
ContextData::ContextData(I_Sender* sender) {
    this->sender = sender;
    modehandler_history = new std::stack<State*>();
    estop_history = new std::stack<State*>();
    timer = new Timer(sender);
    //piece_tracker = new PieceTracker(SAVE_LOCATION_TIMEPROFILE, true);
    pieces_map = new std::unordered_map<int, Piece*>;
}


ContextData::~ContextData() {
    delete pieces_map;
   // delete piece_tracker;
    delete timer;
    State* current_state;
    while(!modehandler_history->empty()) {
        current_state = modehandler_history->top();  // For stack, use top() instead of iterating
        delete current_state;
        modehandler_history->pop();
    }
    delete modehandler_history;

    while(!estop_history->empty()) {
        current_state = estop_history->top();  // For stack, use top() instead of iterating
        delete current_state;
        estop_history->pop();
    }
    delete estop_history;
}

//===================================================== private functions =====================================================

//void ContextData::privateFunction(){}

//===================================================== public functions =====================================================

//void ContextData::publicFunction(){}