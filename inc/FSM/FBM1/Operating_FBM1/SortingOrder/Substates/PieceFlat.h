#ifndef PIECEFLAT_H
#define PIECEFLAT_H

#pragma once

#include "State.h"
#include "../../../Operating_FBM1/SortingOrder/Substates/PieceTall.h"
#include "../../../Operating_FBM1/SortingOrder/Substates/PieceTallWithMetal.h"

class PieceFlat : public State {
public: //============================================ constructors & destructors ============================================
    PieceFlat(ContextData* data) ;
    virtual ~PieceFlat();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
	State* clone() override;

	State* check_piece() override;
	State* reset_to_tall() override;
	State* reset_to_tall_w_metal() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
