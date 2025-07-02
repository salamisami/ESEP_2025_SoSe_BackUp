#ifndef NODEREDFEHLERQUITTIERT_H
#define NODEREDFEHLERQUITTIERT_H
#pragma once

#include "State.h"
#include "NodeRedNoError.h"

class NodeRedFehlerQuittiert : public State {
public: //============================================ constructors & destructors ============================================
    NodeRedFehlerQuittiert(ContextData* data) ;
    virtual ~NodeRedFehlerQuittiert();
	

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