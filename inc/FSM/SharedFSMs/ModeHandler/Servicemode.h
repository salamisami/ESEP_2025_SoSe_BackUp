#ifndef SERVICEMODE_H
#define SERVICEMODE_H
#pragma once

#include "HState.h"
#include "IdleIM.h"
#include "IdleSM.h"
#include "ReadyForCDS.h"


class Servicemode : public HState{
public: //============================================ constructors & destructors ============================================
    Servicemode(ContextData* data);
    Servicemode(ContextData* data, State* initial_substate);
    virtual ~Servicemode();
	

public: //================================================ public functions ================================================
	void entry() override;
	void exit() override;

	State* clone() override;

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
