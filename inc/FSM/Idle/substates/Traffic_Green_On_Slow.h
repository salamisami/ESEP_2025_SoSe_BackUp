#ifndef TRAFFIC_GREEN_ON_SLOW_H
#define TRAFFIC_GREEN_ON_SLOW_H
#pragma once

#include "State.h"

class Traffic_Green_On_Slow : public State {
public: //============================================ contructors & destructors ============================================
	Traffic_Green_On_Slow(ContextData* data);
	virtual ~Traffic_Green_On_Slow();


public: //================================================ public functions ================================================
	void entry() override;
	void exit() override;

	State* button_start_pressed() override;



private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char



private: //================================================ private functions ================================================
	//void privateFunction();

};

#endif