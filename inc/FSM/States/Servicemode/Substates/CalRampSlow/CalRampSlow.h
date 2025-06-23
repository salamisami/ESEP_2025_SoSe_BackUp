#ifndef CALRAMPSLOW_H
#define CALRAMPSLOW_H
#pragma once

#include "OrthState.h"
#include "EndToGateCRS.h"
#include "PusherIdleCRS.h"

class CalRampSlow : public OrthState {
public: //============================================ constructors & destructors ============================================
    CalRampSlow(ContextData* data) ;
    virtual ~CalRampSlow();
	

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
