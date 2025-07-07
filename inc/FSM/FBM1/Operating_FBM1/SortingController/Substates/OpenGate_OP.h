#ifndef OPENGATE_OP_H
#define OPENGATE_OP_H
#pragma once

#include "State.h"
#include "IdleSorting.h"
class OpenGate_OP : public State {
public: //============================================ constructors & destructors ============================================
    OpenGate_OP(ContextData* data) ;
    virtual ~OpenGate_OP();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

    State* clone() override;
    State* timer(TIMER_ID id) override;
private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
