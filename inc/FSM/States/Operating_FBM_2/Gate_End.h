#ifndef GATE_END_H
#define GATE_END_H

#pragma once
 
#include "State.h"
#include "PieceTracker.h"
#include "End.h"
#include "Pieceappeared.h" 
class Gate_End : public State {
public: //============================================ constructors & destructors ============================================
    Gate_End(ContextData* data); //for all types of states
	//Gate_End(ContextData* data, State* initial_substate); //for HState
	//Gate_End(ContextData* data, std::deque<State*> initial_substates); //for OrthState
    virtual ~Gate_End();

 
public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
	State* clone() override;

  State* request_transfer() override;
  State* timer(TIMER_ID id) override;
  State* laser_front_blocked() override;
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
