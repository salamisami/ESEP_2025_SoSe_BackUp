#ifndef LEAVINGGATE_PT1_H
#define LEAVINGGATE_PT1_H
#pragma once

#include "State.h"
#include "LocalDataPT1.h"
#include "GateEnd_PT1.h"

class LeavingGate_PT1 : public State {
public: //============================================ constructors & destructors ============================================
    LeavingGate_PT1(ContextData* data, LocalDataPT1 localdata) ;
    virtual ~LeavingGate_PT1();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
	State* clone() override;

	State* laser_sorting_gate_unblocked() override;
	State* timer(TIMER_ID ID) override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
	LocalDataPT1 localdata_;
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
