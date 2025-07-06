#ifndef REPLAYWARNING_H
#define REPLAYWARNING_H
#pragma once

#include "State.h"
#include "ReplayNoWarning.h"

class ReplayWarning : public State {
public: //============================================ constructors & destructors ============================================
    ReplayWarning(ContextData* data) ;
    virtual ~ReplayWarning();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

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