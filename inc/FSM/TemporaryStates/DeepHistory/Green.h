#ifndef GREEN_H
#define GREEN_H
#pragma once

#include "State.h"
#include "Yellow.h"

class Green : public State {
public: //============================================ constructors & destructors ============================================
    Green(ContextData* data) ;
    virtual ~Green();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
    
	State* button_start_pressed() override;
	State* clone() override;


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
