#ifndef GATE_PT1_H
#define GATE_PT1_H
#pragma once

#include "State.h"
#include "LocalDataPT1.h"
#include "SortingOut_PT1.h"
#include "GateEnd_PT1.h"

class Gate_PT1 : public State {
public: //============================================ constructors & destructors ============================================
    Gate_PT1(ContextData* data, LocalDataPT1 localdata) ;
    virtual ~Gate_PT1();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
	State* clone() override;

	State* sort_out() override;
	State* sort_out_fbm2() override;
	State* let_through() override;
    


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
