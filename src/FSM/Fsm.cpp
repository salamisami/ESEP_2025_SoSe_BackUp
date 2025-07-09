/*
 * Fsm2.cpp
 *
 *  Created on: 02.07.2025
 *      Author: User
 */

#include "../../inc/FSM/Fsm.h"

#ifdef FBM_1
Fsm::Fsm(ContextData* data) : OrthState(data, {
    new NoRampFull(data),
    new RampNotFull(data),
    new IdleIM(data),
    new SortingOrder(data),
    new MQTTNoError(data),
	new COMNoError(data)

}) {};
#else
#ifdef FBM_2
Fsm::Fsm(ContextData* data) : OrthState(data, {
    new NoRampFull(data),
    new RampNotFull(data),
    new IdleIM(data),
    new IdleReset(data),
    new MQTTNoError(data),
	new COMNoError(data)
}) {};

#endif
#endif

Fsm::Fsm(ContextData* data, std::deque<State*> initial_substates) : OrthState(data, initial_substates) {};
Fsm::~Fsm() {}

void Fsm::entry() {
    OrthState::entry();
}

void Fsm::exit() {
    OrthState::exit();
}

State* Fsm::clone() {
    return new Fsm(data, clone_substates());
}