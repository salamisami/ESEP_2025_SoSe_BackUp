#ifndef WAITING_H
#define WAITING_H
#pragma once

#include "State.h"
#include "Timer.h"
#include "Timer_Received.h"
#include "Operating.h"

#define IDLE_TIMER 1

class Waiting : public State {
public: //============================================ contructors & destructors ============================================
    Waiting(ContextData* data);
    virtual ~Waiting();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* button_start_released() override;
	State* timer(int id) override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif