#ifndef MQTTFEHLERQUITTIERT_H
#define MQTTFEHLERQUITTIERT_H
#pragma once

#include "State.h"
#include "MQTTNoError.h"

class MQTTFehlerQuittiert : public State {
public: //============================================ constructors & destructors ============================================
    MQTTFehlerQuittiert(ContextData* data) ;
    virtual ~MQTTFehlerQuittiert();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* clone() override;

	State* mqtt_connected() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif