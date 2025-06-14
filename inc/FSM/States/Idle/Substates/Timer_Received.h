#ifndef TIMER_RECEIVED_H
#define TIMER_RECEIVED_H
#pragma once

#include "State.h"
#include "Timer.h"
#include "Servicemode.h"

class Timer_Received: public State{
public: //============================================ constructors & destructors ============================================
    Timer_Received(ContextData* data);
    virtual ~Timer_Received();
	

public: //================================================ public functions ================================================
	//void publicFunction();
	void entry() override;
	void exit() override;

	I_State* button_start_released() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif