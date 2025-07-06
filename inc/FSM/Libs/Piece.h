#ifndef PIECE_H
#define PIECE_H
#pragma once

#include "Event.h"
#include "Macros.h"
#include "PieceTracker.h"


class Piece{
public: //================================================ public functions ================================================
    Piece(int id = -1): id(id){};
    virtual ~Piece() = default;

    int id = 0;
    PieceEnum type = PieceEnum::UNKNOWN;
    long sorting_time = 0;
    PieceTracker piece_tracker;
};


#endif
