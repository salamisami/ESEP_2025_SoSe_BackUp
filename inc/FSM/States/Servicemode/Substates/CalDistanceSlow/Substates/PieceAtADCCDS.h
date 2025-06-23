#ifndef PIECEATADCCDS_H
#define PIECEATADCCDS_H
#pragma once

#include "State.h"
#include "ADCToGateCDS.h"

class PieceAtADCCDS : public State {
public: //============================================ constructors & destructors ============================================
    PieceAtADCCDS(ContextData* data) ;
    virtual ~PieceAtADCCDS();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* adc_top_area_unblocked() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
