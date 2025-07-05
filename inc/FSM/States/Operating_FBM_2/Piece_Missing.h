#ifndef PIECE_MISSING_H
#define PIECE_MISSING_H
#pragma once
 
#include "State.h"
 
class Piece_Missing : public State {
public: //============================================ constructors & destructors ============================================
    Piece_Missing(ContextData* data); //for all types of states
	//Piece_Missing(ContextData* data, State* initial_substate); //for HState
	//Piece_Missing(ContextData* data, std::deque<State*> initial_substates); //for OrthState
    virtual ~Piece_Missing();

 
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