#ifndef BOTHESTOPPRESSED_H
#define BOTHESTOPPRESSED_H
#pragma once

#include "State.h"
#include "EStopViaLocal.h"
#include "EStopViaNeighbor.h"

//#include

class BothEstopPressed : public State{
public: //============================================ constructors & destructors ============================================
    BothEstopPressed(ContextData* data);
    virtual ~BothEstopPressed();
	

public: //================================================ public functions ================================================
	//void publicFunction();
	void entry() override;
	void exit() override;

	State* button_estop_released() override;
	State* com_button_estop_released() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif