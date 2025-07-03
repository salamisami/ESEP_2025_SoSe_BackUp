#ifndef ISMETAL_PT1_H
#define ISMETAL_PT1_H
#pragma once

#include "State.h"
#include "LocalDataPT1.h"
#include "Gate_PT1.h"

class IsMetal_PT1 : public State {
public: //============================================ constructors & destructors ============================================
    IsMetal_PT1(ContextData* data, LocalDataPT1 localdata);
    virtual ~IsMetal_PT1();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
	State* clone() override;

	State* laser_sorting_gate_blocked() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	LocalDataPT1 localdata_;
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
