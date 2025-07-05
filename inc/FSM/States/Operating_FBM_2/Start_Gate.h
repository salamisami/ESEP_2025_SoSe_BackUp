#ifndef START_GATE_H
#define START_GATE_H
#pragma once
 
#include "State.h"
 
class Start_Gate : public State {
public: //============================================ constructors & destructors ============================================
    Start_Gate(ContextData* data); //for all types of states
	//Start_Gate(ContextData* data, State* initial_substate); //for HState
	//Start_Gate(ContextData* data, std::deque<State*> initial_substates); //for OrthState
    virtual ~Start_Gate();

 
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