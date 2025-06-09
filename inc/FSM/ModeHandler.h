#ifndef MODEHANDLER_H
#define MODEHANDLER_H
#pragma once

#include "State.h"
#include "Idle.h"
#include "Error.h"

class ModeHandler : public State{
public: //============================================ contructors & destructors ============================================
    ModeHandler(ContextData* data, State* initial_substate = nullptr);
    virtual ~ModeHandler();
	

public: //================================================ public functions ================================================
	//void publicFunction();
	void entry() override;
	void exit() override;

	I_State* button_estop_pressed() override;


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif