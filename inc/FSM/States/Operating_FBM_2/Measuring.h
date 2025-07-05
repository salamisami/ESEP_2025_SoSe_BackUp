#ifndef MEASURING_H
#define MEASURING_H
#pragma once
 
#include "State.h"
 
class Measuring : public State {
public: //============================================ constructors & destructors ============================================
    Measuring(ContextData* data); //for all types of states
	//Measuring(ContextData* data, State* initial_substate); //for HState
	//Measuring(ContextData* data, std::deque<State*> initial_substates); //for OrthState
    virtual ~Measuring();

 
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