#ifndef WAITING_H
#define WAITING_H
#pragma once

#include "State.h"
#include "Timer.h"

class Waiting : public State {
public: //============================================ contructors & destructors ============================================
    Waiting(ContextData* data) ;
    virtual ~Waiting();
	

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