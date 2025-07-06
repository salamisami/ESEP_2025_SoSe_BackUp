#ifndef MQTTFEHLERUNQUITTIERT_H
#define MQTTFEHLERUNQUITTIERT_H
#pragma once

#include "State.h"
#include "MQTTFehlerQuittiert.h"
#include "MQTTReconnectedUnquittiert.h"


class MQTTFehlerUnquittiert : public State {
public: //============================================ constructors & destructors ============================================
    MQTTFehlerUnquittiert(ContextData* data) ;
    virtual ~MQTTFehlerUnquittiert();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* clone() override;

	State* mqtt_connected() override;
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