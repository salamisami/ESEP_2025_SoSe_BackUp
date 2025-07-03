#ifndef MOVINGTOEND_PT1_H
#define MOVINGTOEND_PT1_H
#pragma once

#include "State.h"
#include "LocalDataPT1.h"
#include "Transfer_PT1.h"
class MovingToEnd_PT1 : public State {
public: //============================================ constructors & destructors ============================================
    MovingToEnd_PT1(ContextData* data) ;
    virtual ~MovingToEnd_PT1();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
	State* clone() override;
  State* laser_back_blocked() override;
    


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
