#ifndef Stop_H
#define Stop_H
#pragma once

#include "State.h"
#include "Slow.h"
#include "Idle.h"
#include "Fast.h"

class Stop : public State {
public: //============================================ constructors & destructors ============================================
    Stop(ContextData* data) ;
    virtual ~Stop();
	

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
