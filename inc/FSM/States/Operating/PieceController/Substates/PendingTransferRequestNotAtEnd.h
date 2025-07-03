#ifndef PENDINGTRANSFERREQUESTNOTATEND_H
#define PENDINGTRANSFERREQUESTNOTATEND_H
#pragma once

#include "State.h"

class PendingTransferRequestNotAtEnd : public State {
public: //============================================ constructors & destructors ============================================
    PendingTransferRequestNotAtEnd(ContextData* data) ;
    virtual ~PendingTransferRequestNotAtEnd();
	

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
