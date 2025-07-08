#ifndef ADC_CLASS_H
#define ADC_CLASS_H

#pragma once
 
#include "State.h"
#include "Pieceappeared.h"
#include "Piece_Missing.h" 
#include "Measuring.h"

class ADC_Class : public State {
public: //============================================ constructors & destructors ============================================
    ADC_Class(ContextData* data); //for all types of states
	//ADC(ContextData* data, State* initial_substate); //for HState
	//ADC(ContextData* data, std::deque<State*> initial_substates); //for OrthState
    virtual ~ADC_Class();

 
public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
	State* clone() override;

	State* request_transfer() override;
	State* laser_back_blocked() override;
	State* laser_front_blocked() override;
	State* laser_sorting_gate_blocked() override;
	State* laser_ramp_blocked() override;

	State* adc_timeout() override;
	State* adc_new_piece() override;

 
 
private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char

 
private: //================================================ private functions ================================================
	//void privateFunction();
};
 
#endif
