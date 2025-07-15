#ifndef PIECESTOOCLOSE_H
#define PIECESTOOCLOSE_H
#pragma once

#include "State.h"
#include "StartingAreaUnblocked.h"


class PiecesTooClose : public State {
public: //============================================ constructors & destructors ============================================
    PiecesTooClose(ContextData* data) ;
    virtual ~PiecesTooClose();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* clone() override;
    
	State* piece_appeared_resolved() override;

private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
