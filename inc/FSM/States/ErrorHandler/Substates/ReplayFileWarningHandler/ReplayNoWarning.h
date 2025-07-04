#ifndef REPLAYNOWARNING_H
#define REPLAYNOWARNING_H
#pragma once

#include "State.h"
#include "ReplayWarning.h"

class ReplayNoWarning : public State {
public: //============================================ constructors & destructors ============================================
    ReplayNoWarning(ContextData* data) ;
    virtual ~ReplayNoWarning();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* cant_find_rep_conf() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif