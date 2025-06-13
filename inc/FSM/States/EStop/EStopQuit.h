#ifndef ESTOPQUIT_H
#define ESTOPQUIT_H
#pragma once

#include "State.h"
#include "EStopViaLocal.h"
#include "EStopViaNeigbor.h"
#include "ModeHandler.h"

class EStopQuit: public State{
public: //============================================ contructors & destructors ============================================
    EStopQuit(ContextData* data);
    virtual ~EStopQuit();
	

public: //================================================ public functions ================================================
	void entry() override;
	void exit() override;

	I_State* button_estop_pressed() override;
	I_State* com_button_estop_pressed() override;
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