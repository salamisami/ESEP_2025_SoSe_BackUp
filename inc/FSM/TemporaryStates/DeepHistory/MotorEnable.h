#ifndef MOTORENABLE_H
#define MOTORENABLE_H
#pragma once

#include "State.h"
#include "MotorDisable.h"

class MotorEnable : public State {
public: //============================================ constructors & destructors ============================================
    MotorEnable(ContextData* data) ;
    virtual ~MotorEnable();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
    
	State* button_reset_pressed() override;

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
