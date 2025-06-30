#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H
#pragma once

#include "OrthState.h"
#include "Idle.h"

class MotorControl : public OrthState{
public: //============================================ constructors & destructors ============================================
    MotorControl(ContextData* data) ;
    virtual ~MotorControl();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
