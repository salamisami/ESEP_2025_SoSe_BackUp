#ifndef PENDINGTRANSFERREQUEST_PT1_H
#define PENDINGTRANSFERREQUEST_PT1_H
#pragma once

#include "State.h"
#include "LocalDataPT1.h"
#include "Transfer_PT1.h"

class PendingTransferRequest_PT1 : public State {
public: //============================================ constructors & destructors ============================================
    PendingTransferRequest_PT1(ContextData* data, LocalDataPT1 localdata);
    virtual ~PendingTransferRequest_PT1();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
	State* clone() override;

	State* fbm_2_busy() override;
	State* fbm_2_ready() override;
	State* timer(TIMER_ID id) override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	LocalDataPT1 localdata_;
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	void send_transfer_start();
	
};

#endif
