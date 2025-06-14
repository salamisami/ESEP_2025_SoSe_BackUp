#ifndef IDLEGATECP_H
#define IDLEGATECP_H
#pragma once

#include "HState.h"
#include "OpenGateCP.h"

class IdleGateCP : public HState {
public: //============================================ constructors & destructors ============================================
    IdleGateCP(ContextData* data) ;
    virtual ~IdleGateCP();
	

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
