#ifndef TRANSFERDONE_H
#define TRANSFERDONE_H
#pragma once
 
#include "State.h"
#include "Start_Gate.h"
#include "Start_ADC.h"
#include "Pieceappeared.h"

 
class TransferDone : public State {
public: //============================================ constructors & destructors ============================================
    TransferDone(ContextData* data); //for all types of states
	//TransferDone(ContextData* data, State* initial_substate); //for HState
	//TransferDone(ContextData* data, std::deque<State*> initial_substates); //for OrthState
    virtual ~TransferDone();

 
public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
	State* clone() override;

	State* request_transfer() override;
	State* laser_front_unblocked() override;
	State* laser_sorting_gate_blocked() override;
	State* laser_ramp_blocked() override;
	State* laser_back_blocked() override;

	

 
 
private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char

 
private: //================================================ private functions ================================================
	//void privateFunction();
};
 
#endif
