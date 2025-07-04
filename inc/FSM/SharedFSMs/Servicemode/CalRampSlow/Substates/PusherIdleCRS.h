#ifndef PUSHERIDLECRS_H
#define PUSHERIDLECRS_H
#pragma once

#include "State.h"
#include "SendToRamp.h"

class PusherIdleCRS : public State {
public: //============================================ constructors & destructors ============================================
    PusherIdleCRS(ContextData* data) ;
    virtual ~PusherIdleCRS();
	

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
