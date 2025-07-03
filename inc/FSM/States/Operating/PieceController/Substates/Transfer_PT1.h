#ifndef TRANSFER_PT1_H
#define TRANSFER_PT1_H
#pragma once

#include "State.h"
#include "LocalDataPT1.h"

class Transfer_PT1 : public State {
public: //============================================ constructors & destructors ============================================
    Transfer_PT1(ContextData* data, LocalDataPT1 localdata) ;
    virtual ~Transfer_PT1();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
	State* clone() override;

	State* transfer_done() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	LocalDataPT1 localdata_;
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
