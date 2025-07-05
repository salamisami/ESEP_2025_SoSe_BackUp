#ifndef PIECETALL_H
#define PIECETALL_H
#pragma once

#include "State.h"
#include "PieceFlat.h"
#include "PieceTallWithMetal.h"

class PieceTall : public State {
public: //============================================ constructors & destructors ============================================
    PieceTall(ContextData* data) ;
    virtual ~PieceTall();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
	State* clone() override;
	
	State* tall_w_metal_piece() override;
	State* tall_piece() override;
	State* flat_piece() override;

	State* reset_to_flat() override;
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
