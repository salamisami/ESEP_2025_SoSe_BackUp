#ifndef LOCALRAMPFULL_H
#define LOCALRAMPFULL_H
#pragma once

#include "State.h"
#include "NoRampFull.h"
#include "BothRampsFull.h"


class LocalRampFull : public State {
public: //============================================ constructors & destructors ============================================
    LocalRampFull(ContextData* data) ;
    virtual ~LocalRampFull();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* clone() override;
    
	State* ramp_not_full() override;
	State* com_ramp_full() override;

private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
