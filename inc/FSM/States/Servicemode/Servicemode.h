#ifndef SERVICEMODE_H
#define SERVICEMODE_H
#pragma once

#include "HState.h"
#include "IdleMode.h"
#include "IdleServiceMode.h"


class Servicemode : public HState{
public: //============================================ constructors & destructors ============================================
    Servicemode(ContextData* data);
    virtual ~Servicemode();
	

public: //================================================ public functions ================================================
	void entry() override;
	void exit() override;

	HState* button_stop_pressed() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif