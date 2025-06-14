#ifndef IDLEGATECDF_H
#define IDLEGATECDF_H
#pragma once

#include "State.h"
#include "OpenGateCDF.h"

class IdleGateCDF : public State {
public: //============================================ constructors & destructors ============================================
    IdleGateCDF(ContextData* data) ;
    virtual ~IdleGateCDF();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	I_State* laser_sorting_gate_blocked() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
