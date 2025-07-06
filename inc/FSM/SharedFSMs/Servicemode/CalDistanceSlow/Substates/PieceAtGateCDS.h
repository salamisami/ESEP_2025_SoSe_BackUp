#ifndef PIECEATGATECDS_H
#define PIECEATGATECDS_H
#pragma once

#include "State.h"
#include "GateToEndCDS.h"

class PieceAtGateCDS : public State {
public: //============================================ constructors & destructors ============================================
    PieceAtGateCDS(ContextData* data) ;
    virtual ~PieceAtGateCDS();
	

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
