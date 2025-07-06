#ifndef IDLETEST_H
#define IDLETEST_H
#pragma once

#include "State.h"
#include "RunMotor.h"

class IdleTest : public State {
public: //============================================ constructors & destructors ============================================
    IdleTest(ContextData* data) ;
    virtual ~IdleTest();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* clone() override;

	State* laser_front_blocked() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
