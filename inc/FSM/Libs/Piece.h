#ifndef PIECE_H
#define PIECE_H
#pragma once

#include "Event.h"
#include "Macros.h"
#include "PieceTracker.h"


class Piece{
public: //================================================ public functions ================================================
    Piece():piece_tracker(new PieceTracker(SAVE_LOCATION_TIMEPROFILE)){}
    virtual ~Piece(){
        delete piece_tracker;
    }
    int id = 0;
    CheckPiece_Enum type = CheckPiece_Enum::UNKNOWN;
    long sorting_time = 0;
    PieceTracker* piece_tracker;
};


#endif
