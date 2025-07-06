/*
 * Fsm2.cpp
 *
 *  Created on: 02.07.2025
 *      Author: User
 */

#include "../../inc/FSM/Fsm.h"

Fsm::Fsm(ContextData* data) : OrthState(data, { new Boot(data), new IdleReset(data) }) {};
Fsm::Fsm(ContextData* data, std::deque<State*> initial_substates) : OrthState(data, initial_substates) {};

Fsm::~Fsm() {}

void Fsm::entry() {}

void Fsm::exit() {}
