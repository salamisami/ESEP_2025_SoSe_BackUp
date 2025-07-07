#ifndef STARTINGAREATRACKER_H
#define STARTINGAREATRACKER_H
#pragma once

#include "HState.h"
#include "StartingAreaUnblocked.h"

class StartingAreaTracker : public HState {
public: //============================================ constructors & destructors ============================================
    StartingAreaTracker(ContextData* data) ;
	StartingAreaTracker(ContextData* data, State* initial_substate);
    virtual ~StartingAreaTracker();
	

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
