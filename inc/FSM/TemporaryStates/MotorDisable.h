#ifndef MOTORDISABLE_H
#define MOTORDISABLE_H
#pragma once

#include "State.h"
#include "MotorEnable.h"

class MotorDisable : public State {
public: //============================================ constructors & destructors ============================================
    MotorDisable(ContextData* data) ;
    virtual ~MotorDisable();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* button_reset_pressed() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
