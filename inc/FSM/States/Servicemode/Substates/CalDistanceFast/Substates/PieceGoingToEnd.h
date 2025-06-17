#ifndef PIECEGOINGTOEND_H
#define PIECEGOINGTOEND_H
#pragma once

#include "State.h"
#include "CalGateRampFast.h"

class PieceGoingToEnd : public State {
public: //============================================ constructors & destructors ============================================
    PieceGoingToEnd(ContextData* data) ;
    virtual ~PieceGoingToEnd();
	

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
