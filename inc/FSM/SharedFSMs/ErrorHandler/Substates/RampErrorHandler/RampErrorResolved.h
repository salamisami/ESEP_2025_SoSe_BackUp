#ifndef RAMPERRORRESOLVED_H
#define RAMPERRORRESOLVED_H
#pragma once

#include "State.h"
#include "RampNoError.h"

class RampErrorResolved : public State {
public: //============================================ constructors & destructors ============================================
    RampErrorResolved(ContextData* data) ;
    virtual ~RampErrorResolved();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* clone() override;

	State* button_reset_released() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif