#ifndef MEASURING_H
#define MEASURING_H
#pragma once
 
#include "State.h"
#include "ADC_Gate.h"
#include "Piece_appeared.h"
 
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

	State* request_transfer() override;
	State* laser_back_blocked() override;
	State* laser_front_blocked() override;
	State* laser_sorting_gate_blocked() override;
	State* laser_ramp_blocked() override;

	State* adc_wh_detected() override;
	State* adc_wf_detected() override;
	State* adc_w_b_detected() override;
	State* adc_w_not_detected() override;
 
private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char

 
private: //================================================ private functions ================================================
	//void privateFunction();
};
 
#endif