#ifndef MQTTRECONNECTEDUNQUITTIERT_H
#define MQTTRECONNECTEDUNQUITTIERT_H
#pragma once

#include "State.h"
#include "MQTTNoError.h"

class MQTTReconnectedUnquittiert : public State {
public: //============================================ constructors & destructors ============================================
    MQTTReconnectedUnquittiert(ContextData* data) ;
    virtual ~MQTTReconnectedUnquittiert();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* clone() override;

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