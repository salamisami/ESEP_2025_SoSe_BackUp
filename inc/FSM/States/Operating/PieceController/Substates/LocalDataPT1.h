#ifndef LOCALDATAPT1_H
#define LOCALDATAPT1_H
#pragma once

#include "Event.h"

class LocalDataPT1{
public: 
	int id = -1;
	ScannedPiece ist_type = ScannedPiece::UNKNOWN;
	int is_metal = false;
	PieceEnum validated_type = PieceEnum::UNKNOWN;
};

#endif
