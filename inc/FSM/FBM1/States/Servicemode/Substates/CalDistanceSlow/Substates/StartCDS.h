#ifndef STARTCDS_H
#define STARTCDS_H
#pragma once

#include "State.h"
#include "PieceAtADCCDS.h"

class StartCDS : public State {
public: //============================================ constructors & destructors ============================================
    StartCDS(ContextData* data) ;
    virtual ~StartCDS();
	

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
