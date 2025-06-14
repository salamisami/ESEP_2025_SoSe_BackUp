#ifndef SERVICEMODE_H
#define SERVICEMODE_H
#pragma once

#include "State.h"
#include "Idle.h"
#include "IdleServiceMode.h"


class Servicemode : public State{
public: //============================================ constructors & destructors ============================================
    Servicemode(ContextData* data);
    virtual ~Servicemode();
	

public: //================================================ public functions ================================================
	void entry() override;
	void exit() override;

	State* button_stop_pressed() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif