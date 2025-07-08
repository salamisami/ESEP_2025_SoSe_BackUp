#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H
#pragma once

#include "HState.h"
#include "Idle.h"

class MotorControl : public HState{
public: //============================================ constructors & destructors ============================================
    MotorControl(ContextData* data) ;
    MotorControl(ContextData* data, State* initial_substate);
    virtual ~MotorControl();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
    State* clone() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
