#ifndef PIECEAPPEARED_H
#define PIECEAPPEARED_H
#pragma once
 
#include "State.h"
#include "ReadyForPiece.h"
 
class Piece_appeared : public State {
public: //============================================ constructors & destructors ============================================
    Piece_appeared(ContextData* data); //for all types of states
	//PieceAppeared(ContextData* data, State* initial_substate); //for HState
	//PieceAppeared(ContextData* data, std::deque<State*> initial_substates); //for OrthState
    virtual ~Piece_appeared();

 
public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
	State* clone() override;

	State*  piece_appeared_resolved() override;
<<<<<<< Updated upstream:inc/FSM/States/Operating_FBM_2/Pieceappeared.h

	State* request_transfer() override;
=======
>>>>>>> Stashed changes:inc/FSM/States/Operating_FBM_2/PieceAppeared.h
 
private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char

 
private: //================================================ private functions ================================================
	//void privateFunction();
};
 
#endif