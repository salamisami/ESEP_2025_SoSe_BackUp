#ifndef Idle_H
#define Idle_H
#pragma once

#include "State.h"
#include "Fast.h"
#include "MotorControl.h"

class Idle : public State {
public: //============================================ constructors & destructors ============================================
    Idle(ContextData* data) ;
    virtual ~Idle();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
    
    State* motor_fast() override;
    State* clone() override;
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
