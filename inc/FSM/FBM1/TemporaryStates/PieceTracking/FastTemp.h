#ifndef FASTTEMP_H
#define FASTTEMP_H
#pragma once

#include "State.h"
#include "SlowTemp.h"

class FastTemp : public State
{
public: //============================================ constructors & destructors ============================================
	FastTemp(ContextData *data);
	virtual ~FastTemp();

public: //================================================ public functions ================================================
	void entry() override;
	void exit() override;

	State *button_reset_pressed() override;

private: //================================================ private variables ================================================
		 // classes, STL containers, and structs
		 // pointers
		 // primitive types
		 // bool and char
private: //================================================ private functions ================================================
		 // void privateFunction();
};

#endif
