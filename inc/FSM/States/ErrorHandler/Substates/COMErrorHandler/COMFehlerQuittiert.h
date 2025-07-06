#ifndef COMFEHLERQUITTIERT_H
#define COMFEHLERQUITTIERT_H
#pragma once

#include "State.h"
#include "COMReconnected.h"

class COMFehlerQuittiert : public State {
public: //============================================ constructors & destructors ============================================
    COMFehlerQuittiert(ContextData* data) ;
    virtual ~COMFehlerQuittiert();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* com_connected() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif