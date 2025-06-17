#ifndef CALDISTANCEFAST_H
#define CALDISTANCEFAST_H
#pragma once

#include "OrthState.h"
#include "IdleCDF.h"
#include "LetPieceThrough.h"
#include "CalGateRampFast.h"

class CalDistanceFast : public OrthState{
public: //============================================ constructors & destructors ============================================
    CalDistanceFast(ContextData* data) ;
    virtual ~CalDistanceFast();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* laser_back_blocked() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
