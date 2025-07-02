/*
 * Fsm2.cpp
 *
 *  Created on: 02.07.2025
 *      Author: User
 */

#include "Fsm2.h"

Fsm2::Fsm2(ContexData* data): OrthState(data, {new NoRampFull(data), new RampNotFull(data), new Boot(data), new IdleReset(data)}) {}

Fsm2::Fsm2(ContexData* data, std::vector<State*> initial_substates): OrthState(data, initial_substates) {}

Fsm2::~Fsm2(): ~OrthState() {}

Fsm2::entry(){ }

Fsm2::exit() { }
