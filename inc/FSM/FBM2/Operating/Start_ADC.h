#ifndef START_ADC_H
#define START_ADC_H

#pragma once
 
#include "State.h"
#include "Pieceappeared.h"
#include "ADC_State.h"
 
class Start_ADC : public State {
public: //============================================ constructors & destructors ============================================
    Start_ADC(ContextData* data); //for all types of states
	//Start_ADC(ContextData* data, State* initial_substate); //for HState
	//Start_ADC(ContextData* data, std::deque<State*> initial_substates); //for OrthState
    virtual ~Start_ADC();

 
public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
	State* clone() override;

	State* request_transfer() override;
	State* laser_back_blocked() override;
	State* laser_front_blocked() override;
	State* laser_sorting_gate_blocked() override;
	State* laser_ramp_blocked() override;

	State* timer(TIMER_ID id) override;
 
 
private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char

 
private: //================================================ private functions ================================================
	//void privateFunction();
};
 
#endif
