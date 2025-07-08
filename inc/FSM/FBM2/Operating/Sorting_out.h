#ifndef SORTING_OUT_H
#define SORTING_OUT_H
#pragma once
 
#include "State.h"
#include "Piece_Missing.h"
#include "ReadyForPiece.h"
#include "Pieceappeared.h"

 
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

  State* timer(TIMER_ID id) override; 
  State* laser_ramp_blocked() override;
  State* laser_back_blocked() override;
  State* laser_front_blocked() override;
  State* laser_gate_blocked() override;
  State* request_transfer() override;
private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers 
	//primitive types
	//bool and char

 
private: //================================================ private functions ================================================
	//void privateFunction();
};
 
#endif
