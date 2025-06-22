#ifndef YELLOW_H
#define YELLOW_H
#pragma once

#include "State.h"
#include "Red.h"

class Yellow : public State {
public: //============================================ constructors & destructors ============================================
    Yellow(ContextData* data) ;
    virtual ~Yellow();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

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
