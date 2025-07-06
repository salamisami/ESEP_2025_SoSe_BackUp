#ifndef GATETORAMPCRF_H
#define GATETORAMPCRF_H
#pragma once

#include "State.h"
#include "ReadyForCDS.h"

class GateToRampCRF : public State {
public: //============================================ constructors & destructors ============================================
    GateToRampCRF(ContextData* data) ;
    virtual ~GateToRampCRF();
	

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
