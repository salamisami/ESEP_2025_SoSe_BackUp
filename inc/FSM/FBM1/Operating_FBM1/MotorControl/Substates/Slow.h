#ifndef Slow_H
#define Slow_H
#pragma once

#include "State.h"
#include "Fast.h"
#include "Stop.h"
#include "Idle.h"

class Slow : public State {
public: //============================================ constructors & destructors ============================================
    Slow(ContextData* data) ;
    virtual ~Slow();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
    
    State* motor_fast() override;
    State* motor_stop_fsm() override;
    State* delete_w_motor() override;
    State* motor_slow() override;
    State* clone() override;
    void updateData(MotorPieceState motorPieceState);

private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
