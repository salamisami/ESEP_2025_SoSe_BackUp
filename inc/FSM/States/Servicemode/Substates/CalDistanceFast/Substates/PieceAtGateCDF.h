#ifndef PIECEATGATECDF
#define PIECEATGATECDF
#pragma once

#include "State.h"
#include "GateToEndCDF.h"

class PieceAtGateCDF : public State {
public: //============================================ constructors & destructors ============================================
    PieceAtGateCDF(ContextData* data) ;
    virtual ~PieceAtGateCDF();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
    
	State* laser_sorting_gate_unblocked() override;


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
