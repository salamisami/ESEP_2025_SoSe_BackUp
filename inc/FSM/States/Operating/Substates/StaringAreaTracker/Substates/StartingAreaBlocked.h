#ifndef STARTINGAREABLOCKED_H
#define STARTINGAREABLOCKED_H
#pragma once

#include "State.h"
#include "StartingAreaUnblocked.h"
#include "PiecesTooClose.h"


class StartingAreaBlocked : public State {
public: //============================================ constructors & destructors ============================================
    StartingAreaBlocked(ContextData* data) ;
    virtual ~StartingAreaBlocked();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
    
	State* laser_front_blocked() override;
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
