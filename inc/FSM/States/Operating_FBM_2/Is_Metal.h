#ifndef IS_METAL_H
#define IS_METAL_H
#pragma once
 
#include "State.h"
 
class Is_Metal : public State {
public: //============================================ constructors & destructors ============================================
    Is_Metal(ContextData* data); //for all types of states
	//Is_Metal(ContextData* data, State* initial_substate); //for HState
	//Is_Metal(ContextData* data, std::deque<State*> initial_substates); //for OrthState
    virtual ~Is_Metal();

 
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