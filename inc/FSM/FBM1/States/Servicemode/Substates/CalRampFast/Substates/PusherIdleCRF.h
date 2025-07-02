#ifndef PUSHERIDLECRF_H
#define PUSHERIDLECRF_H
#pragma once

#include "State.h"
#include "SendToRamp.h"

class PusherIdleCRF : public State {
public: //============================================ constructors & destructors ============================================
    PusherIdleCRF(ContextData* data) ;
    virtual ~PusherIdleCRF();
	

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
