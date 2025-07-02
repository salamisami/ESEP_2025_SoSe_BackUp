#ifndef ESTOPTEST_H
#define ESTOPTEST_H
#pragma once

#include "State.h"

class EStopTest : public State {
public: //============================================ constructors & destructors ============================================
    EStopTest(ContextData* data) ;
    virtual ~EStopTest();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
	State* clone() override;


	State* button_estop_pressed() override;
	State* button_estop_released() override;

	State* button_reset_pressed() override;
	State* button_reset_released() override;


	//COM------------------------------

	
	State* com_button_estop_pressed() override;
	State* com_button_estop_released() override;

	State* com_button_reset_pressed() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
