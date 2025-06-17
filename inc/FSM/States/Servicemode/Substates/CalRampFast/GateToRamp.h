#ifndef GATETORAMMP_H
#define GATETORAMMP_H
#pragma once

#include "State.h"
#include "ReadyForCDS.h"

class GateToRamp : public State {
public: //============================================ constructors & destructors ============================================
    GateToRamp(ContextData* data) ;
    virtual ~GateToRamp();
	

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
