#ifndef SORTINGCONTROLLER_H
#define SORTINGCONTROLLER_H
#pragma once

#include "HState.h"
#include "Idle.h"

class SortingController : public HState{
public: //============================================ constructors & destructors ============================================
    SortingController(ContextData* data) ;
    SortingController(ContextData* data, State* initial_substate);
    virtual ~SortingController();
	

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
