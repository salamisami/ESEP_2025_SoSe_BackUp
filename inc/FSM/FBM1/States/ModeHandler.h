#ifndef MODEHANDLER_H
#define MODEHANDLER_H
#pragma once

#include "HState.h"
#include "IdleMode.h"
#include "EStopViaLocal.h"
#include "EStopViaNeighbor.h"

class ModeHandler : public HState{
public: //============================================ constructors & destructors ============================================
    ModeHandler(ContextData* data);
    virtual ~ModeHandler();
	

public: //================================================ public functions ================================================
	//void publicFunction();
	void entry() override;
	void exit() override;

	State* button_estop_pressed() override;
	State* com_button_estop_pressed() override;


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif