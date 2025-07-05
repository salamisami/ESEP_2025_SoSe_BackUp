#ifndef RAMPTIMER_H
#define RAMPTIMER_H
#pragma once

#include "State.h"
#include "RampNotFull.h"
#include "RampFull.h"


class RampTimer : public State {
public: //============================================ constructors & destructors ============================================
    RampTimer(ContextData* data) ;
    virtual ~RampTimer();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
    
	State* laser_ramp_unblocked() override;
	State* timer(TIMER_ID id) override;

private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
