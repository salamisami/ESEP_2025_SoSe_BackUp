#ifndef PIECEATGATECRF_H
#define PIECEATGATECRF_H
#pragma once

#include "State.h"
#include "PieceAtADCCRF.h"

class PieceAtGateCRF : public State {
public: //============================================ constructors & destructors ============================================
    PieceAtGateCRF(ContextData* data) ;
    virtual ~PieceAtGateCRF();
	

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
