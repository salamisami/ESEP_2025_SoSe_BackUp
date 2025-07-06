#ifndef GATETORAMPCRS_H
#define GATETORAMPCRS_H
#pragma once

#include "State.h"
#include "CalibrationFinished.h"

class GateToRampCRS : public State {
public: //============================================ constructors & destructors ============================================
    GateToRampCRS(ContextData* data) ;
    virtual ~GateToRampCRS();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* clone() override;

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
