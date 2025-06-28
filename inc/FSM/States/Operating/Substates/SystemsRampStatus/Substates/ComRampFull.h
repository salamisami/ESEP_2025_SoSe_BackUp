#ifndef COMRAMPFULL_H
#define COMRAMPFULL_H
#pragma once

#include "State.h"
#include "NoRampFull.h"
#include "BothRampsFull.h"


class ComRampFull : public State {
public: //============================================ constructors & destructors ============================================
    ComRampFull(ContextData* data) ;
    virtual ~ComRampFull();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
    
	State* com_ramp_not_full() override;
	State* ramp_full() override;

private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
