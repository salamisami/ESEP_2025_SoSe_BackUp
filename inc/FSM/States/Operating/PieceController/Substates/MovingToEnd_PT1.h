#ifndef MOVINGTOEND_PT1_H
#define MOVINGTOEND_PT1_H
#pragma once

#include "State.h"

class MovingToEnd_PT1 : public State {
public: //============================================ constructors & destructors ============================================
    MovingToEnd_PT1(ContextData* data) ;
    virtual ~MovingToEnd_PT1();
	

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
