#ifndef LETPIECETHROUGH_H
#define LETPIECETHROUGH_H
#pragma once

#include "HState.h"
#include "IdleLPT.h"



class LetPieceThrough : public HState {
public: //============================================ constructors & destructors ============================================
    LetPieceThrough(ContextData* data, int duration) ;
    virtual ~LetPieceThrough();
	

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
