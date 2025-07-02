#ifndef PIECEATGATECRS_H
#define PIECEATGATECRS_H
#pragma once

#include "State.h"
#include "PieceAtADCCRS.h"

class PieceAtGateCRS : public State {
public: //============================================ constructors & destructors ============================================
    PieceAtGateCRS(ContextData* data) ;
    virtual ~PieceAtGateCRS();
	

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
