#ifndef COMFEHLERUNQUITTIERT_H
#define COMFEHLERUNQUITTIERT_H
#pragma once

#include "State.h"
#include "COMFehlerQuittiert.h"
#include "COMReconnectedUnquittiert.h"

class COMFehlerUnquittiert : public State {
public: //============================================ constructors & destructors ============================================
    COMFehlerUnquittiert(ContextData* data) ;
    virtual ~COMFehlerUnquittiert();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* clone() override;

	State* com_connected() override;
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