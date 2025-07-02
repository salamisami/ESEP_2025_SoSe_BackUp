#ifndef REPLAYNOERROR_H
#define REPLAYNOERROR_H
#pragma once

#include "State.h"
#include "ReplayFehlerUnquittiert.h"

class ReplayNoError : public State {
public: //============================================ constructors & destructors ============================================
    ReplayNoError(ContextData* data) ;
    virtual ~ReplayNoError();
	

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