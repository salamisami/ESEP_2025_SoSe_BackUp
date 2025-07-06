#ifndef PIECEATADCCDF_H
#define PIECEATADCCDF_H
#pragma once

#include "State.h"
#include "ADCToGateCDF.h"

class PieceAtADCCDF : public State {
public: //============================================ constructors & destructors ============================================
    PieceAtADCCDF(ContextData* data) ;
    virtual ~PieceAtADCCDF();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* clone() override;

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
