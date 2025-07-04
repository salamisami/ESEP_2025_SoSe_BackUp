#ifndef IDLESTR_H
#define IDLESTR_H
#pragma once

#include "State.h"
#include "PushRampSTR.h"

class IdleSTR : public State {
public: //============================================ constructors & destructors ============================================
    IdleSTR(ContextData* data) ;
    virtual ~IdleSTR();
	

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
