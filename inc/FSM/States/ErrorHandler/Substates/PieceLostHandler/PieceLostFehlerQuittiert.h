#ifndef PIECELOSTFEHLERQUITTIERT_H
#define PIECELOSTFEHLERQUITTIERT_H
#pragma once

#include "State.h"

class PieceLostFehlerQuittiert : public State {
public: //============================================ constructors & destructors ============================================
    PieceLostFehlerQuittiert(ContextData* data) ;
    virtual ~PieceLostFehlerQuittiert();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* button_reset_released() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif