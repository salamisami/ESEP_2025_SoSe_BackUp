#ifndef MODEHANDLER_H
#define MODEHANDLER_H
#pragma once

#include "State.h"
#include "Idle.h"
#include "Error.h"

class ModeHandler : public State{
public: //============================================ contructors & destructors ============================================
    ModeHandler(ContextData* data, State* previousState = nullptr);
    virtual ~ModeHandler();
	

public: //================================================ public functions ================================================
	//void publicFunction();
	void entry() override;
	void exit() override;

	State* button_start_pressed() override;
	State* button_start_released() override;
	State* button_stop_pressed() override;
	State* button_estop_pressed() override;
	State* timer(int id) override;

    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	State* substate;
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif