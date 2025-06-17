#ifndef PIECEGOINGGATEBACKWARD_H
#define PIECEGOINGGATEBACKWARD_H
#pragma once

#include "State.h"
#include "PieceGoingToADC.h"

class PieceGoingGateBackward : public State {
public: //============================================ constructors & destructors ============================================
    PieceGoingGateBackward(ContextData* data) ;
    virtual ~PieceGoingGateBackward();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* timer(TIMER_ID id) override;
	State* laser_sorting_gate_blocked() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
