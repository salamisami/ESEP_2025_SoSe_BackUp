#ifndef WAITINGIM_H
#define WAITINGIM_H
#pragma once

#include "State.h"
#include "Timer.h"
#include "TimerReceivedIM.h"
#include "Operating.h"
#include "OperatingMock.h"


class WaitingIM : public State {
public: //============================================ constructors & destructors ============================================
    WaitingIM(ContextData* data);
    virtual ~WaitingIM();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* button_start_released() override;
	State* timer(TIMER_ID id) override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif