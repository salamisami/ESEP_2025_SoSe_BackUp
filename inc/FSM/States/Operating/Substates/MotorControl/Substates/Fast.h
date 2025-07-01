#ifndef Fast_H
#define Fast_H
#pragma once

#include "State.h"
#include "Slow.h"
#include "Stop.h"
#include "Idle.h"

class Fast : public State {
public: //============================================ constructors & destructors ============================================
    Fast(ContextData* data) ;
    virtual ~Fast();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
    
	State* delete_w_motor() override;
    State* motor_slow() override;
    State* motor_fast() override;
    State* motor_stop_fsm() override;

private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
