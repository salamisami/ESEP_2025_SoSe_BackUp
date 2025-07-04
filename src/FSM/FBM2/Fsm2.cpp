/*
 * Fsm2.cpp
 *
 *  Created on: 02.07.2025
 *      Author: User
 */

#include "Fsm2.h"

Fsm2::Fsm2(ContextData* data): OrthState(data, {new NoRampFull(data), new RampNotFull(data), new Boot(data), new IdleReset(data)}) {}

Fsm2::Fsm2(ContextData* data, std::vector<State*> initial_substates): OrthState(data, initial_substates) {}

Fsm2::~Fsm2(){}

void Fsm2::entry(){ }

void Fsm2::exit() { }
