#ifndef BOTHESTOPPRESSED_H
#define BOTHESTOPPRESSED_H
#pragma once

#include "State.h"
#include "EStopViaLocal.h"
#include "EStopViaNeigbor.h"

//#include

class BothEstopPressed : public State{
public: //============================================ contructors & destructors ============================================
    BothEstopPressed(ContextData* data);
    virtual ~BothEstopPressed();
	

public: //================================================ public functions ================================================
	//void publicFunction();
	void entry() override;
	void exit() override;

	I_State* button_estop_released() override;
	I_State* com_button_estop_released() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif