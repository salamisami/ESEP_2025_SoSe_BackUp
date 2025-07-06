#ifndef ADCTOGATECDF_H
#define ADCTOGATECDF_H
#pragma once

#include "State.h"
#include "PieceAtGateCDF.h"

class ADCToGateCDF : public State {
public: //============================================ constructors & destructors ============================================
    ADCToGateCDF(ContextData* data) ;
    virtual ~ADCToGateCDF();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* clone() override;
    
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
