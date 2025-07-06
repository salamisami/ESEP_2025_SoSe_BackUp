#ifndef PIECEAPPEAREDNOERROR_H
#define PIECEAPPEAREDNOERROR_H
#pragma once

#include "State.h"
#include "PieceAppearedFehlerUnquittiert.h"

class PieceAppearedNoError : public State {
public: //============================================ constructors & destructors ============================================
    PieceAppearedNoError(ContextData* data) ;
    virtual ~PieceAppearedNoError();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* clone() override;

	State* error_w_appear() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif