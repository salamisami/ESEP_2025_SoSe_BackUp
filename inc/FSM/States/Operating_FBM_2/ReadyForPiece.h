#ifndef READYFORPIECE_H
#define READYFORPIECE_H
#pragma once
 
#include "State.h"
 
class ReadyForPiece : public State {
public: //============================================ constructors & destructors ============================================
    ReadyForPiece(ContextData* data); //for all types of states
	//ReadyForPiece(ContextData* data, State* initial_substate); //for HState
	//ReadyForPiece(ContextData* data, std::deque<State*> initial_substates); //for OrthState
    virtual ~ReadyForPiece();

 
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