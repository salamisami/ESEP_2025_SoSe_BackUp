#ifndef CALRAMPSLOW_H
#define CALRAMPSLOW_H
#pragma once

#include "OrthState.h"
#include "EndToGateCRS.h"
#include "PusherIdleCRS.h"

class CalRampSlow : public OrthState {
public: //============================================ constructors & destructors ============================================
    CalRampSlow(ContextData* data);
	CalRampSlow(ContextData* data, std::deque<State*> initial_substates);
    virtual ~CalRampSlow();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* clone() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
