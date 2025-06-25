#ifndef STOPTEST_H
#define STOPTEST_H
#pragma once

#include "State.h"

class StopTest : public State {
public: //============================================ constructors & destructors ============================================
    StopTest(ContextData* data) ;
    virtual ~StopTest();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
