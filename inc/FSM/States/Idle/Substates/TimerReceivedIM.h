#ifndef TIMERRECEIVEDIM_H
#define TIMERRECEIVEDIM_H
#pragma once

#include "State.h"
#include "Timer.h"
#include "Servicemode.h"

class TimerReceivedIM: public State{
public: //============================================ constructors & destructors ============================================
    TimerReceivedIM(ContextData* data);
    virtual ~TimerReceivedIM();
	

public: //================================================ public functions ================================================
	//void publicFunction();
	void entry() override;
	void exit() override;

	State* button_start_released() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif