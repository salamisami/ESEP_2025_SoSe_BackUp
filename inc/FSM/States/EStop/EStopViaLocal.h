#ifndef ESTOPVIALOCAL_H
#define ESTOPVIALOCAL_H
#pragma once

#include "State.h"
#include "BothEstopPressed.h"
#include "EStopReleased.h"

class EStopViaLocal: public State {
public: //============================================ constructors & destructors ============================================
    EStopViaLocal(ContextData* data);
    virtual ~EStopViaLocal();
	

public: //================================================ public functions ================================================
	void entry() override;
	void exit() override;

	State* com_button_estop_pressed() override;
	State* button_estop_released() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif