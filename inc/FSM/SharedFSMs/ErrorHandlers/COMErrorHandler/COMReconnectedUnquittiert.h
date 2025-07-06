#ifndef COMRECONNECTEDUNQUITTIERT_H
#define COMRECONNECTEDUNQUITTIERT_H
#pragma once

#include "State.h"
#include "COMNoError.h"

class COMReconnectedUnquittiert : public State {
public: //============================================ constructors & destructors ============================================
    COMReconnectedUnquittiert(ContextData* data) ;
    virtual ~COMReconnectedUnquittiert();
	

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