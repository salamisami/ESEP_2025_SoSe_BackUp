#ifndef IDLELPT_H
#define IDLELPT_H
#pragma once

#include "State.h"
#include "OpenGateLPT.h"

class IdleLPT : public State {
public: //============================================ constructors & destructors ============================================
    IdleLPT(ContextData* data, int duration) ;
    virtual ~IdleLPT();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* clone() override;

	State* laser_sorting_gate_blocked() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	int duration;
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
