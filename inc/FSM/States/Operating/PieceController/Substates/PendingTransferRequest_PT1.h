#ifndef PENDINGTRANSFERREQUEST_PT1_H
#define PENDINGTRANSFERREQUEST_PT1_H
#pragma once

#include "State.h"

class PendingTransferRequest_PT1 : public State {
public: //============================================ constructors & destructors ============================================
    PendingTransferRequest_PT1(ContextData* data) ;
    virtual ~PendingTransferRequest_PT1();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
	State* clone() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
