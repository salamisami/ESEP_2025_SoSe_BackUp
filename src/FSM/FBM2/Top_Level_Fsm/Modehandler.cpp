/*
 * Modehandler.cpp
 *
 *  Created on: 02.07.2025
 *      Author: User
 */

#include "../../../../inc/FSM/FBM2/Top_level_Fsm/Modehandler.h"

void Modehandler::entry(){ }

void Modehandler::exit() { }

State* Modehandler::clone(){
	return new Modehandler(data,this->clone_substates());
}

State* Modehandler::error_c_lost_com(){
	Modehandler* cloned = this->clone();
	data->modehandler_history->push(cloned);
	return new ErrorCom(data);
}

State* Modehandler::error_c_lost_mqtt(){
	Modehandler* cloned = this->clone();
	data->modehandler_history->push(cloned);
	return new ErrorCom(data);
}

State* Modehandler::button_estop_pressed(){
	Modehandler* cloned = this->clone();
	data->modehandler_history->push(cloned);
	return new EStop(data,EStopViaLocal);
}

State* Modehandler::com_button_estop_pressed(){
	Modehandler* cloned = this->clone();
	data->modehandler_history->push(cloned);
	return new EStop(data,EStopViaNeighbour);
}

State* Modehandler::remote_stop(){
	Modehandler* cloned = this->clone();
	data->modehandler_history->push(cloned);
	return new EStop(data,EStopReleased);
}
