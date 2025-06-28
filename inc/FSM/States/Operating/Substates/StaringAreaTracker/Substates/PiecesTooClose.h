#ifndef PIECESTOOCLOSE_H
#define PIECESTOOCLOSE_H
#pragma once

#include "State.h"
#include "StartingAreaBlocked.h"


class StartingAreaUnblocked : public State {
public: //============================================ constructors & destructors ============================================
    StartingAreaUnblocked(ContextData* data) ;
    virtual ~StartingAreaUnblocked();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
    
	State* error_pieces_too_close_fixed() override;

private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
