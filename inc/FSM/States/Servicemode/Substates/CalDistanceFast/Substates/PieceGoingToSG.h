#ifndef PIECEGOINGTOSG_H
#define PIECEGOINGTOSG_H
#pragma once

#include "State.h"
#include "PieceAtSortingGate.h"

class PieceGoingToSG : public State {
public: //============================================ constructors & destructors ============================================
    PieceGoingToSG(ContextData* data) ;
    virtual ~PieceGoingToSG();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
    
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
