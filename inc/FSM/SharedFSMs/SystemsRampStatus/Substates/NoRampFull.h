#ifndef NORAMPFULL_H
#define NORAMPFULL_H
#pragma once

#include "State.h"
#include "LocalRampFull.h"
#include "ComRampFull.h"


class NoRampFull : public State {
public: //============================================ constructors & destructors ============================================
    NoRampFull(ContextData* data) ;
    virtual ~NoRampFull();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* clone() override;
    
	State* ramp_full() override;
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
