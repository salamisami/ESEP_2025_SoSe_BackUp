#ifndef ADCTOGATECDS_H
#define ADCTOGATECDS_H
#pragma once

#include "State.h"
#include "PieceAtGateCDS.h"

class ADCToGateCDS : public State {
public: //============================================ constructors & destructors ============================================
    ADCToGateCDS(ContextData* data) ;
    virtual ~ADCToGateCDS();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
    
	State* laser_sorting_gate_blocked() override;


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
