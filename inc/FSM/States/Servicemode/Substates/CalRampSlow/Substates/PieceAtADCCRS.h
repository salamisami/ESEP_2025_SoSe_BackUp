#ifndef PIECEATADCCRS_H
#define PIECEATADCCRS_H
#pragma once

#include "State.h"
#include "GateToRampCRS.h"

class PieceAtADCCRS : public State {
public: //============================================ constructors & destructors ============================================
    PieceAtADCCRS(ContextData* data) ;
    virtual ~PieceAtADCCRS();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* clone() override;
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
