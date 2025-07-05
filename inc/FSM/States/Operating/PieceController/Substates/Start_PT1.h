#ifndef START_PT1_H
#define START_PT1_H
#pragma once

#include "State.h"
#include "StartADC_PT1.h"
#include "LocalDataPT1.h"

class Start_PT1 : public State {
public: //============================================ constructors & destructors ============================================
    Start_PT1(ContextData* data, LocalDataPT1 localdata) ;
    virtual ~Start_PT1();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
	State* clone() override;

	State* laser_front_unblocked() override;
    


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
