#ifndef ESTOPRELEASED_H
#define ESTOPRELEASED_H
#pragma once

#include "State.h"
#include "WaitingForComReset.h"
#include "WaitingForLocalReset.h"
#include "EStopViaLocal.h"
#include "EStopViaNeighbor.h"

class EStopReleased : public State {
public: //============================================ constructors & destructors ============================================
    EStopReleased(ContextData* data);
    virtual ~EStopReleased();
	

public: //================================================ public functions ================================================
	void entry() override;
	void exit() override;

	State* button_reset_pressed() override;
	State* com_button_reset_pressed() override;
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
