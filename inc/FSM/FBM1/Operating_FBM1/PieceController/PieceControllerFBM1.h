#ifndef PIECECONTROLLERFBM1_H
#define PIECECONTROLLERFBM1_H
#pragma once

#include "OrthState.h"
#include "Start_PT1.h"


class PieceControllerFBM1 : public OrthState {
public: //============================================ constructors & destructors ============================================
    PieceControllerFBM1(ContextData* data);
	PieceControllerFBM1(ContextData* data, std::deque<State*> substates);
    virtual ~PieceControllerFBM1();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
	State* clone() override;

	State* new_piece() override;

	
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

protected:
	virtual State* laser_back_blocked() override;
	virtual State* metal_detected() override;
	virtual State* laser_sorting_gate_blocked() override;

	virtual State* handle_event_using_function(State* (State::* handler_function)()) override;
	//virtual State* timer(TIMER_ID id) override;
	//virtual State* custom_handler_function(State* (State::* handler_function)());
	
};

#endif
