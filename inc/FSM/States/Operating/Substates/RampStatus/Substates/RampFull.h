#ifndef RAMPFULL_H
#define RAMPFULL_H
#pragma once

#include "State.h"


class RampFull : public State {
public: //============================================ constructors & destructors ============================================
    RampFull(ContextData* data) ;
    virtual ~RampFull();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
    
	State* laser_ramp_unblocked() override;

private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
