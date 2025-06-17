#ifndef PIECEATGATE_H
#define PIECEATGATE_H
#pragma once

#include "State.h"
#include "ReadyForCDS.h"

class PieceAtGate : public State {
public: //============================================ constructors & destructors ============================================
    PieceAtGate(ContextData* data) ;
    virtual ~PieceAtGate();
	

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
