#ifndef PIECEATADC_H
#define PIECEATADC_H
#pragma once

#include "State.h"
#include "PieceGoingToSG.h"

class PieceAtADC : public State {
public: //============================================ constructors & destructors ============================================
    PieceAtADC(ContextData* data) ;
    virtual ~PieceAtADC();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* adc_top_area_unblocked() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
