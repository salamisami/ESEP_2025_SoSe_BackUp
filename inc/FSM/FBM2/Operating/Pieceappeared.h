#ifndef PIECEAPPEARED_H
#define PIECEAPPEARED_H
#pragma once
 
#include "State.h"
#include "ReadyForPiece.h"
 
class Pieceappeared : public State {
public: //============================================ constructors & destructors ============================================
    Pieceappeared(ContextData* data); //for all types of states
	//PieceAppeared(ContextData* data, State* initial_substate); //for HState
	//PieceAppeared(ContextData* data, std::deque<State*> initial_substates); //for OrthState
    virtual ~Pieceappeared();

 
public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
	State* clone() override;

	State*  piece_appeared_resolved() override;

	State* request_transfer() override;
 
private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char

 
private: //================================================ private functions ================================================
	//void privateFunction();
};
 
#endif
