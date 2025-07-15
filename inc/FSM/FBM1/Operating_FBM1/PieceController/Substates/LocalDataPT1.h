#ifndef LOCALDATAPT1_H
#define LOCALDATAPT1_H
#pragma once

#include "Event.h"
#include "Piece.h"
class LocalDataPT1 {
public:
  Piece *piece = nullptr;
  ScannedPiece ist_type = ScannedPiece::UNKNOWN;
  int is_metal = false;
  PieceEnum validated_type = PieceEnum::UNKNOWN;
  bool unblock_signal_has_been_sent = false;
  bool sort_out_fbm2 = true;
};

#endif
