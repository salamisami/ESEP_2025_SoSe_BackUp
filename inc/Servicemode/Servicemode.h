#ifndef SERVICEMODE_H
#define SERVICEMODE_H
#pragma once

#include "State.h"
#include "Idle.h"

class Servicemode : public State{
public: //============================================ contructors & destructors ============================================
    Servicemode(ContextData* data, State* previousState = nullptr);
    virtual ~Servicemode();
	

public: //================================================ public functions ================================================
	void entry() override;
	void exit() override;

	State* button_stop_pressed() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	State* subState;
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif