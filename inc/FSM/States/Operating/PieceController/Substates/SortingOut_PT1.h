#ifndef SORTINGOUT_PT1_H
#define SORTINGOUT_PT1_H
#pragma once

#include "State.h"
#include "LocalDataPT1.h"

class SortingOut_PT1 : public State {
public: //============================================ constructors & destructors ============================================
    SortingOut_PT1(ContextData* data, LocalDataPT1 localdata);
    virtual ~SortingOut_PT1();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
	State* clone() override;
  State* laser_ramp_blocked() override;
  State* timer(TIMER_ID id) override;
    


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
