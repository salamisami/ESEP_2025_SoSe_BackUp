#ifndef IDLESM_H
#define IDLESM_H
#pragma once

#include "State.h"
#include "ServiceModeSendRamp.h"
#include "CalDistanceFast.h"
#include "CalDistanceSlow.h"

class IdleSM : public State {
public: //============================================ constructors & destructors ============================================
    IdleSM(ContextData* data) ;
    virtual ~IdleSM();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* laser_front_blocked() override;

private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
