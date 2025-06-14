#ifndef IDLEGATECDF_H
#define IDLEGATECDF_H
#pragma once

#include "HState.h"
#include "OpenGateCDF.h"

class IdleGateCDF : public HState {
public: //============================================ constructors & destructors ============================================
    IdleGateCDF(ContextData* data) ;
    virtual ~IdleGateCDF();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* laser_sorting_gate_blocked() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
