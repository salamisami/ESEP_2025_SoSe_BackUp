#ifndef PSEUDOSTATE_H
#define PSEUDOSTATE_H
#pragma once

//This state is only purposed for placeholder state
#include "State.h"

class PseudoState : public State {
public: //============================================ constructors & destructors ============================================
    PseudoState(ContextData* data) ;
    virtual ~PseudoState();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
	State* clone() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
