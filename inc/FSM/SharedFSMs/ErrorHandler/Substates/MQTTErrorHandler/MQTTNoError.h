#ifndef MQTTNOERROR_H
#define MQTTNOERROR_H
#pragma once

#include "State.h"
#include "MQTTFehlerUnquittiert.h"

class MQTTNoError : public State {
public: //============================================ constructors & destructors ============================================
    MQTTNoError(ContextData* data) ;
    virtual ~MQTTNoError();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* clone() override;

	State* error_c_lost_mqtt() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
