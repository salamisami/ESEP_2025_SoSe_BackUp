#ifndef TRANSFERDONE_H
#define TRANSFERDONE_H
#pragma once
 
#include "State.h"
 
class TransferDone : public State {
public: //============================================ constructors & destructors ============================================
    TransferDone(ContextData* data); //for all types of states
	//TransferDone(ContextData* data, State* initial_substate); //for HState
	//TransferDone(ContextData* data, std::deque<State*> initial_substates); //for OrthState
    virtual ~TransferDone();

 
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