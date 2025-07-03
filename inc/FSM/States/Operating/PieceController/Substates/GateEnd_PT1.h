#ifndef GATEEND_PT1_H
#define GATEEND_PT1_H
#pragma once

#include "State.h"
#include "LocalDataPT1.h"

class GateEnd_PT1 : public State {
public: //============================================ constructors & destructors ============================================
    GateEnd_PT1(ContextData* data, LocalDataPT1 localdata);
    virtual ~GateEnd_PT1();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
	State* clone() override;
    


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
