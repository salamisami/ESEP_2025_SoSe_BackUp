/*
 * WaitingForComReset.cpp
 *
 *  Created on: 03.07.2025
 *      Author: User
 */

#include "WaitingForComReset.h"

void WaitingForComReset::entry(){ }

void WaitingForComReset::exit(){ }

State* WaitingForComReset::clone(){ return new WaitingForComReset(data);}

State* WaitingForComReset::button_estop_pressed(){
	return new EstopViaLocal(data);
}

State* WaitingForComReset::com_button_estop_pressed(){
	return new EstopViaNeighbor(data);
}

State* WaitingForComReset::com_button_reset_pressed(){
	return State::EXIT_STATE;
}

State* WaitingForComReset::remote_stop(){
	return new EStopReleased(data);
}
