#ifndef GATE_H
#define GATE_H
#pragma once
 
#include "State.h"
 
class Gate : public State {
public: //============================================ constructors & destructors ============================================
    Gate(ContextData* data); //for all types of states
	//Gate(ContextData* data, State* initial_substate); //for HState
	//Gate(ContextData* data, std::deque<State*> initial_substates); //for OrthState
    virtual ~Gate();

 
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