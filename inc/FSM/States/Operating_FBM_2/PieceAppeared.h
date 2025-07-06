#ifndef PIECEAPPEARED_H
#define PIECEAPPEARED_H
#pragma once
 
#include "State.h"
 
class PieceAppeared : public State {
public: //============================================ constructors & destructors ============================================
    PieceAppeared(ContextData* data); //for all types of states
	//PieceAppeared(ContextData* data, State* initial_substate); //for HState
	//PieceAppeared(ContextData* data, std::deque<State*> initial_substates); //for OrthState
    virtual ~PieceAppeared();

 
public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
	State* clone() override;

	State*  error_w_appeared_fixed() override;
 
private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char

 
private: //================================================ private functions ================================================
	//void privateFunction();
};
 
#endif