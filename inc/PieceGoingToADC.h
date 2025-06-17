#ifndef PIECEGOINGTOADC_H
#define PIECEGOINGTOADC_H
#pragma once

#include "State.h"
#include "PieceGoingToGate.h"

class PieceGoingToADCBackward : public State {
public: //============================================ constructors & destructors ============================================
    PieceGoingToADCBackward(ContextData* data) ;
    virtual ~PieceGoingToADCBackward();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* adc_top_area_blocked() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
