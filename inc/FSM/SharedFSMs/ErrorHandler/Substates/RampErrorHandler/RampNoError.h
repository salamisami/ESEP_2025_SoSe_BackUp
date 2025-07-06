#ifndef RAMPNOERROR_H
#define RAMPNOERROR_H
#pragma once

#include "State.h"
#include "RampErrorUnquittiert.h"

class RampNoError : public State {
public: //============================================ constructors & destructors ============================================
    RampNoError(ContextData* data) ;
    virtual ~RampNoError();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* clone() override;

	State* error_both_r_full() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif