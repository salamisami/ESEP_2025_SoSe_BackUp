/*
 * WaitingForLocalReset.cpp
 *
 *  Created on: 03.07.2025
 *      Author: User
 */

#include "WaitingForLocalReset.h"

void WaitingForLocalReset::entry(){ }

void WaitingForLocalReset::exit(){ }

State* WaitingForLocalReset::clone(){
	return new WaitingForLocalReset(data);
}

State* WaitingForLocalReset::button_reset_pressed(){
	return State::EXIT_STATE;
}

State* WaitingForLocalReset::button_estop_pressed(){
	return new EStopViaLocal(data);
}

State* WaitingForLocalReset::com_button_estop_pressed(){
	return new EStopViaNeighbor(data);
}

State* WaitingForLocalReset::remote_stop(){
	return new EStopReleased(data);
}

