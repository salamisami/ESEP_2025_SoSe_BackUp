#ifndef TRANSFER_H
#define TRANSFER_H
#pragma once
 
#include "State.h"
#include "Piece_Missing.h"
#include "TransferDone.h"



 
class Transfer : public State {
public: //============================================ constructors & destructors ============================================
    Transfer(ContextData* data); //for all types of states
	//Transfer(ContextData* data, State* initial_substate); //for HState
	//Transfer(ContextData* data, std::deque<State*> initial_substates); //for OrthState
    virtual ~Transfer();

 
public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
	State* clone() override;

	State* request_transfer() override;

	State* laser_back_blocked() override;
	State* laser_sorting_gate_blocked() override;
	State* laser_ramp_blocked() override;
	State* laser_front_blocked() override;
	State* timer(TIMER_ID id) override;
	State* id() override;



 
 
private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char

 
private: //================================================ private functions ================================================
	//void privateFunction();
};
 
#endif
