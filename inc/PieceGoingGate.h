#ifndef PIECEGOINGGATE_H
#define PIECEGOINGGATE_H
#pragma once

#include "State.h"
#include "PieceGoingGateBackward.h"

class PieceGoingGate : public State {
public: //============================================ constructors & destructors ============================================
    PieceGoingGate(ContextData* data) ;
    virtual ~PieceGoingGate();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* timer(TIMER_ID id) override;


    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
