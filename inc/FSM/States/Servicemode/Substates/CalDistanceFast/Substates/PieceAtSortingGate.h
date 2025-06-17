#ifndef PIECEATSORTINGGATE_H
#define PIECEATSORTINGGATE_H
#pragma once

#include "State.h"
#include "PieceGoingToEnd.h"

class PieceAtSortingGate : public State {
public: //============================================ constructors & destructors ============================================
    PieceAtSortingGate(ContextData* data) ;
    virtual ~PieceAtSortingGate();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
    
	State* laser_sorting_gate_unblocked();


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
