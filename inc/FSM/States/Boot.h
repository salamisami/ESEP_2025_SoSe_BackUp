#ifndef BOOT_H
#define BOOT_H
#pragma once

#include "State.h"
#include "ModeHandler.h"

class Boot : public State {
public: //============================================ constructors & destructors ============================================
    Boot(ContextData* data);
    virtual ~Boot();
	

public: //================================================ public functions ================================================
	void entry() override;
	void exit() override;

	I_State* is_switch() override;
	I_State* is_pusher() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif