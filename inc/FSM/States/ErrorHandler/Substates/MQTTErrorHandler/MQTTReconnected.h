#ifndef COMRECONNECTED_H
#define COMRECONNECTED_H
#pragma once

#include "State.h"

class MQTTReconnected : public State {
public: //============================================ constructors & destructors ============================================
    MQTTReconnected(ContextData* data) ;
    virtual ~MQTTReconnected();
	

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