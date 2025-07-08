#ifndef GATE_H
#define GATE_H

#pragma once
 
#include "State.h"
#include "Sorting_out.h"
#include "Pieceappeared.h"
#include "Gate_End.h"
#include "LeavingGate_PT2.h"

class Gate : public State {
public: //============================================ constructors & destructors ============================================
    Gate(ContextData* data); //for all types of states
	//Gate(ContextData* data, State* initial_substate); //for HState
	//Gate(ContextData* data, std::deque<State*> initial_substates); //for OrthState
    virtual ~Gate();

 
public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
	State* clone() override;

  State* laser_front_blocked() override; 
  State* laser_ramp_blocked() override;
  State* laser_back_blocked() override;
  State* request_transfer() override;
  State* let_through() override;
  State* sorting_out_fbm2() override;
  State* timer(TIMER_ID id)override;
 
 
private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
  PieceEnum piece_data;

 
private: //================================================ private functions ================================================
	//void privateFunction();
  State* check_piece();
  PieceEnum validate_piece(const ScannedPiece& scanned_piece, const bool& has_metal);
};
 
#endif
