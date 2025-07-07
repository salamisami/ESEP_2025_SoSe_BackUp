#ifndef PIECE_H
#define PIECE_H
#pragma once

#include "Event.h"
#include "Macros.h"
#include "DistanceTracker.h"


class Piece {
public: //================================================ public functions ================================================
    Piece(TimeProfile* time_profile)
        : id(-1)
        , time_profile_(time_profile)
        {
        piece_tracker = new DistanceTracker(time_profile_, true);
    }
    Piece(int id, TimeProfile* time_profile)
        : id(id)
        , time_profile_(time_profile)
        {
        piece_tracker = new DistanceTracker(time_profile_, true);
    }
    virtual ~Piece() {
        delete piece_tracker;
    }

    int id = 0;
    PieceEnum type = PieceEnum::UNKNOWN;
    long sorting_time = 0;
    DistanceTracker* piece_tracker;
    TimeProfile* time_profile_;
};


#endif
