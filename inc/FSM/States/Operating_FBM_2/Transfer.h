#ifndef TRANSFER_H
#define TRANSFER_H
#pragma once
 
#include "State.h"
 
class Transfer : public State {
public: //============================================ constructors & destructors ============================================
    Transfer(ContextData* data); //for all types of states
	//Transfer(ContextData* data, State* initial_substate); //for HState
	//Transfer(ContextData* data, std::deque<State*> initial_substates); //for OrthState
    virtual ~Transfer();

 
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