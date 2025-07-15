#ifndef PENDINGTRANSFERREQUESTNOTATEND_H
#define PENDINGTRANSFERREQUESTNOTATEND_H
#pragma once

#include "State.h"
#include "LocalDataPT1.h"
#include "Macros.h"
#include "MovingToEnd_PT1.h"
#include "ADC_PT1.h"

class PendingTransferRequestNotAtEnd : public State {
public: //============================================ constructors & destructors ============================================
	PendingTransferRequestNotAtEnd(ContextData* data, LocalDataPT1 localdata);
	virtual ~PendingTransferRequestNotAtEnd();


public: //================================================ public functions ================================================
	void entry() override;
	void exit() override;
	State* clone() override;
	State* fbm_2_busy() override;
	State* fbm_2_ready() override;

	State* timer(TIMER_ID id) override;


private: //================================================ private variables ================================================
	LocalDataPT1 localdata_;
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char



private: //================================================ private functions ================================================
	//void privateFunction();

};

#endif
