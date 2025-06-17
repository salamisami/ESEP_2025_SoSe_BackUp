#ifndef CALRAMPFAST_H
#define CALRAMPFAST_H
#pragma once

#include "OrthState.h"
#include "SendToRamp.h"
#include "EndToGateCRF.h"

class CalRampFast : public OrthState {
public: //============================================ constructors & destructors ============================================
    CalRampFast(ContextData* data) ;
    virtual ~CalRampFast();
	

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
