#ifndef RAMPNOTFULL_H
#define RAMPNOTFULL_H
#pragma once

#include "State.h"


class RampNotFull : public State {
public: //============================================ constructors & destructors ============================================
    RampNotFull(ContextData* data) ;
    virtual ~RampNotFull();
	

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
