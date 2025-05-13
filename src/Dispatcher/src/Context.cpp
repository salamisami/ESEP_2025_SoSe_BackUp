/*
 * Context.cpp
 *
 *  Created on: 07.05.2025
 *      Author: Thomas
 */

#include "Context.h"

Context::Context(Action *action, Data *data) {
	state = new NoConnections();
	state->set_action(action);
	state->set_data(data);
	this->action = action;
	this->data = data;
	state->entry();
}

Context::~Context() {
	delete state;
}

void Context::dispatch_message(){
	state->dispatch_message();
}

void Context::dispatcher_ready(){
	state->dispatcher_ready();
}

void Context::fsm_not_ready(){
	state->fsm_not_ready();
}

void Context::fsm_ready(){
	state->fsm_ready();
}

void Context::hal_not_ready(){
	state->hal_not_ready();
}

void Context::hal_ready(){
	state->hal_ready();
}

void Context::mqtt_not_ready(){
	state->mqtt_not_ready();
}

void Context::mqtt_ready(){
	state->mqtt_ready();
}

void Context::qnet_not_ready(){
	state->qnet_not_ready();
}

void Context::qnet_ready(){
	state->qnet_ready();
}
