#ifndef NODEREDFEHLERUNQUITTIERT_H
#define NODEREDFEHLERUNQUITTIERT_H
#pragma once

#include "State.h"
#include "NodeRedFehlerQuittiert.h"


class NodeRedFehlerUnquittiert : public State {
public: //============================================ constructors & destructors ============================================
    NodeRedFehlerUnquittiert(ContextData* data) ;
    virtual ~NodeRedFehlerUnquittiert();
	

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