#ifndef FBM2_BOOT_H
#define FBM2_BOOT_H

#pragma once

#include "../../Libs/State.h"
#include "ContextData.h"
#include "Modehandler.h"
#include "TimeProfileManager.h"

class Boot : public State {
public: //============================================ constructors & destructors ============================================
    Boot(ContextData* data);
    virtual ~Boot();
	

public: //================================================ public functions ================================================
	void entry() override;
	void exit() override;

	State* is_switch() override;
	State* is_pusher() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
