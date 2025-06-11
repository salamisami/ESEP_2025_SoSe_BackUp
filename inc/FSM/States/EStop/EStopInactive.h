#ifndef ESTOPINACTIVE_H
#define ESTOPINACTIVE_H
#pragma once

#include "State.h"
#include "ModeHandler.h"
#include "EStopReleased.h"

class EStopInactive : public State {
public: //============================================ contructors & destructors ============================================
    EStopInactive(ContextData* data);
    virtual ~EStopInactive();
	

public: //================================================ public functions ================================================
	void entry() override;
	void exit() override;

	I_State* com_button_estop_pressed() override;
	I_State* button_estop_pressed() override;
	I_State* button_reset_released() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif