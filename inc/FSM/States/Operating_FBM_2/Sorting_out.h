#ifndef SORTING_OUT_H
#define SORTING_OUT_H
#pragma once
 
#include "State.h"
 
class Sorting_out : public State {
public: //============================================ constructors & destructors ============================================
    Sorting_out(ContextData* data); //for all types of states
	//Sorting_out(ContextData* data, State* initial_substate); //for HState
	//Sorting_out(ContextData* data, std::deque<State*> initial_substates); //for OrthState
    virtual ~Sorting_out();

 
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