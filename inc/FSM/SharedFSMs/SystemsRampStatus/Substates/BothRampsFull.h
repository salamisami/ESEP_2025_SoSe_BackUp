#ifndef BOTHRAMPSFULL_H
#define BOTHRAMPSFULL_H
#pragma once

#include "State.h"
#include "ComRampFull.h"
#include "LocalRampFull.h"

class BothRampsFull : public State {
public: //============================================ constructors & destructors ============================================
    BothRampsFull(ContextData* data) ;
    virtual ~BothRampsFull();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* clone() override;
    
	State* com_ramp_not_full() override;
	State* ramp_not_full() override;
	State* sort_out() override;
	//State* error_both_r_full() override;

private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
