#ifndef IS_METAL_H
#define IS_METAL_H
#pragma once
 
#include "State.h"
 
class Is_Metal : public State {
public: //============================================ constructors & destructors ============================================
    Is_Metal(ContextData* data); //for all types of states
	//Is_Metal(ContextData* data, State* initial_substate); //for HState
	//Is_Metal(ContextData* data, std::deque<State*> initial_substates); //for OrthState
    virtual ~Is_Metal();

 
public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
	State* clone() override;
  State* request_transfer() override;
  State* laser_sorting_gate_blocked() override;
  State* timer() override;
  State* laser_ramp_blocked() override;
  State* laser_back_blocked() override;
  State* laser_front_blocked() override;
// 

//REQUEST_TARNSFER /FBM_2_BUSY   laser_sorting_gate_blocked

  //TIMER:After(100ms)/getArea(),getPosition() laser_front_blocked,laser_ramp_blocked,laser_back_blocked,
 
private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char

 
private: //================================================ private functions ================================================
	//void privateFunction();
};
 
#endif
