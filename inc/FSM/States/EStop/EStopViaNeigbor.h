#ifndef ESTOPVIANEIGBOR_H
#define ESTOPVIANEIGBOR_H
#pragma once

#include "State.h"
#include "BothEstopPressed.h"
#include "EStopReleased.h"

class EStopViaNeighbor : public State{
public: //============================================ contructors & destructors ============================================
    EStopViaNeighbor(ContextData* data);
    virtual ~EStopViaNeighbor();
	

public: //================================================ public functions ================================================
	void entry() override;
	void exit() override;

	I_State* button_estop_pressed() override;
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