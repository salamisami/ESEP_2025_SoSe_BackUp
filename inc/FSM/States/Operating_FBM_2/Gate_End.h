#ifndef GATE_END_H
#define GATE_END_H
#pragma once
 
#include "State.h"
 
class Gate_End : public State {
public: //============================================ constructors & destructors ============================================
    Gate_End(ContextData* data); //for all types of states
	//Gate_End(ContextData* data, State* initial_substate); //for HState
	//Gate_End(ContextData* data, std::deque<State*> initial_substates); //for OrthState
    virtual ~Gate_End();

 
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