#ifndef ESTOPQUIT_H
#define ESTOPQUIT_H
#pragma once

#include "State.h"
#include "EStopViaLocal.h"
#include "EStopViaNeighbor.h"
#include "ModeHandler.h"

class EStopQuit: public State{
public: //============================================ constructors & destructors ============================================
    EStopQuit(ContextData* data);
    virtual ~EStopQuit();
	

public: //================================================ public functions ================================================
	void entry() override;
	void exit() override;

	State* clone() override;

	State* button_estop_pressed() override;
	State* com_button_estop_pressed() override;
	State* button_reset_released() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif