#ifndef SORTINGORDER_H
#define SORTINGORDER_H

#pragma once

#include "HState.h"
#include "../../Operating_FBM1/SortingOrder/Substates/PieceFlat.h"

class SortingOrder : public HState {
public: //============================================ constructors & destructors ============================================
    SortingOrder(ContextData* data) ;
    virtual ~SortingOrder();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
