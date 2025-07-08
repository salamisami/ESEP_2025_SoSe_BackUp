#ifndef LEAVINGGATE_PT2_H
#define LEAVINGGATE_PT2_H
#pragma once

#include "State.h"
//#include "LocalDataPT1.h"
#include "GateEnd.h"

class LeavingGate_PT2 : public State {
public: //============================================ constructors & destructors ============================================
    LeavingGate_PT2(ContextData* data) ;
    virtual ~LeavingGate_PT2();
	

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
	//LocalDataPT1 localdata_;
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
