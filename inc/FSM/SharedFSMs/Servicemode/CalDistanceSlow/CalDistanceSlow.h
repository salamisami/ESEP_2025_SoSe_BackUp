#ifndef CALDISTANCESLOW_H
#define CALDISTANCESLOW_H
#pragma once

#include "OrthState.h"
#include "IdleCDS.h"
#include "LetPieceThrough.h"
#include "CalRampSlow.h"

class CalDistanceSlow : public OrthState{
public: //============================================ constructors & destructors ============================================
    CalDistanceSlow(ContextData* data) ;
	CalDistanceSlow(ContextData* data, std::deque<State*> initial_substates);
    virtual ~CalDistanceSlow();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* clone() override;

	//State* laser_back_blocked() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
