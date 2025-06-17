#ifndef CALGATERAMPFAST_H
#define CALGATERAMPFAST_H
#pragma once

#include "OrthState.h"
#include "SendToRamp.h"
#include "PieceGoingGate.h"

class CalGateRampFast : public OrthState {
public: //============================================ constructors & destructors ============================================
    CalGateRampFast(ContextData* data) ;
    virtual ~CalGateRampFast();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* laser_ramp_blocked() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
