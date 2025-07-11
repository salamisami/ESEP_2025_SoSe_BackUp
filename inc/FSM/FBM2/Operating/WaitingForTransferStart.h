#ifndef WAITINGFORTRANSFERSTART_H
#define WAITINGFORTRANSFERSTART_H
#pragma once
 
#include "State.h"
#include "ReadyForPiece.h"
#include "Pieceappeared.h"
#include "Transfer.h"
 
class WaitingForTransferStart : public State {
public: //============================================ constructors & destructors ============================================
    WaitingForTransferStart(ContextData* data); //for all types of states
	//WaitingForTransferStart(ContextData* data, State* initial_substate); //for HState
	//WaitingForTransferStart(ContextData* data, std::deque<State*> initial_substates); //for OrthState
    virtual ~WaitingForTransferStart();

 
public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
	State* clone() override;


	State* request_transfer() override;

	State* laser_back_blocked() override;
	State* laser_front_blocked() override;
	State* laser_sorting_gate_blocked() override;
	State* laser_ramp_blocked() override;

	State* transfer_start_other() override;
	State* transfer_start_tall() override;
	State* transfer_start_flat() override;
	State* transfer_start_tall_w_metal() override;
	State* transfer_start_tall_w_metal_sort_out() override;
	State* transfer_start_tall_sort_out() override;
	State* transfer_start_flat_sort_out() override;



 
 
private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char

 
private: //================================================ private functions ================================================
	//void privateFunction();
};
 
#endif
