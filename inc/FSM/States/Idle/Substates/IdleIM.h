#ifndef IDLEIM_H
#define IDLEIM_H
#pragma once

#include "State.h"
#include "WaitingIM.h"

class IdleIM : public State {
public: //============================================ constructors & destructors ============================================
	IdleIM(ContextData* data);
	virtual ~IdleIM();


public: //================================================ public functions ================================================
	void entry() override;
	void exit() override;

	State* clone() override;

	State* button_start_pressed() override;



private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char



private: //================================================ private functions ================================================
	//void privateFunction();

};

#endif