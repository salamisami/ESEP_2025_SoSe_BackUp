#ifndef IDLESORTING_H
#define IDLESORTING_H
#pragma once

#include "State.h"
#include "PushRamp_OP.h"
#include "OpenGate_OP.h"
class IdleSorting : public State {
public: //============================================ constructors & destructors ============================================
    IdleSorting(ContextData* data) ;
    virtual ~IdleSorting();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

    State* clone() override;
    State* sort_out() override;
    State* let_through() override;
private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
