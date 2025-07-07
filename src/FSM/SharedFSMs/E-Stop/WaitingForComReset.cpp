/*
 * WaitingForComReset.cpp
 *
 *  Created on: 03.07.2025
 *      Author: User
 */

#include "WaitingForComReset.h"

void WaitingForComReset::entry() {
	PRINT_STATE;
}

void WaitingForComReset::exit() {
	PRINT_STATE;
}

State* WaitingForComReset::clone() { return new WaitingForComReset(data); }

State* WaitingForComReset::button_estop_pressed() {
	return new EStopViaLocal(data);
}

State* WaitingForComReset::com_button_estop_pressed() {
	return new EStopViaNeighbor(data);
}

State* WaitingForComReset::com_button_reset_pressed() {
	return State::EXIT_STATE;
}

State* WaitingForComReset::remote_stop() {
	return new EStopReleased(data);
}
