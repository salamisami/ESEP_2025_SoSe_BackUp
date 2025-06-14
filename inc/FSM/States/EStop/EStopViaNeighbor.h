#ifndef ESTOPVIANEIGHBOR_H
#define ESTOPVIANEIGHBOR_H
#pragma once

#include "HState.h"
#include "BothEstopPressed.h"
#include "EStopReleased.h"

class EStopViaNeighbor : public HState{
public: //============================================ constructors & destructors ============================================
    EStopViaNeighbor(ContextData* data);
    virtual ~EStopViaNeighbor();
	

public: //================================================ public functions ================================================
	void entry() override;
	void exit() override;

	State* button_estop_pressed() override;
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