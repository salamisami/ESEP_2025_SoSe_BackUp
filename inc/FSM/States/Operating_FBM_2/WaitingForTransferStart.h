#ifndef WAITINGFORTRANSFERSTART_H
#define WAITINGFORTRANSFERSTART_H
#pragma once
 
#include "State.h"
 
class WaitingForTransferStart : public State {
public: //============================================ constructors & destructors ============================================
    WaitingForTransferStart(ContextData* data); //for all types of states
	//WaitingForTransferStart(ContextData* data, State* initial_substate); //for HState
	//WaitingForTransferStart(ContextData* data, std::deque<State*> initial_substates); //for OrthState
    virtual ~WaitingForTransferStart();

 
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