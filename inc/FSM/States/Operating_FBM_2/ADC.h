#ifndef ADC_H
#define ADC_H
#pragma once
 
#include "State.h"
 
class ADC : public State {
public: //============================================ constructors & destructors ============================================
    ADC(ContextData* data); //for all types of states
	//ADC(ContextData* data, State* initial_substate); //for HState
	//ADC(ContextData* data, std::deque<State*> initial_substates); //for OrthState
    virtual ~ADC();

 
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