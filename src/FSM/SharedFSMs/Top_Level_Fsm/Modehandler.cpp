/*
 * Modehandler.cpp
 *
 *  Created on: 02.07.2025
 *      Author: User
 */

#include "Modehandler.h"

Modehandler::Modehandler(ContextData* data) : OrthState(data, {new IdleIM(data)}){}
Modehandler::Modehandler(ContextData* data, std::deque<State*> substates) : OrthState(data, substates){}

void Modehandler::entry(){ }

void Modehandler::exit() { }

State* Modehandler::clone(){
	return new Modehandler(data,this->clone_substates());
}

State* Modehandler::error_c_lost_com(){
	State* cloned = this->clone();
	data->modehandler_history->push(cloned);
	return new ErrorCom(data);
}

State* Modehandler::error_c_lost_mqtt(){
	State* cloned = this->clone();
	data->modehandler_history->push(cloned);
	return new ErrorCom(data);
}

State* Modehandler::button_estop_pressed(){
	// State* cloned = this->clone();
	// data->modehandler_history->push(cloned);
	return new EStop(data,new EStopViaLocal(data));
}

State* Modehandler::com_button_estop_pressed(){
	State* cloned = this->clone();
	data->modehandler_history->push(cloned);
	return new EStop(data,new EStopViaNeighbor(data));
}

State* Modehandler::remote_stop(){
	State* cloned = this->clone();
	data->modehandler_history->push(cloned);
	return new EStop(data,new EStopReleased(data));
}
