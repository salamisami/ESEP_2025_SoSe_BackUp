#ifndef PUSHRAMP_OP_H
#define PUSHRAMP_OP_H
#pragma once

#include "State.h"
#include "IdleSorting.h"
class PushRamp_OP : public State {
public: //============================================ constructors & destructors ============================================
    PushRamp_OP(ContextData* data) ;
    virtual ~PushRamp_OP();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

    State* clone() override;
    State* sort_out() override;
    State* let_trough() override;
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
