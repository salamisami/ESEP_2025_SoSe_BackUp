#ifndef PIECEATADCCRF_H
#define PIECEATADCCRF_H
#pragma once

#include "State.h"
#include "GateToRamp.h"

class PieceAtADCCRF : public State {
public: //============================================ constructors & destructors ============================================
    PieceAtADCCRF(ContextData* data) ;
    virtual ~PieceAtADCCRF();
	

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
