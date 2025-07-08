/*
 * WaitingForLocalReset.h
 *
 *  Created on: 03.07.2025
 *      Author: User
 */

#ifndef INC_FSM_SHAREDFSMS_E_STOP_WAITINGFORLOCALRESET_H_
#define INC_FSM_SHAREDFSMS_E_STOP_WAITINGFORLOCALRESET_H_

#include "State.h"
#include "ContextData.h"
#include "EStopViaLocal.h"
#include "EStopViaNeighbor.h"
#include "EStopReleased.h"

class WaitingForLocalReset : public State {
public:
	WaitingForLocalReset(ContextData* data) : State(data){};
	virtual ~WaitingForLocalReset(){};

	void entry() override;
	void exit() override;
	State* clone() override;

	State* button_reset_pressed() override;
	State* button_estop_pressed() override;
	State* com_button_estop_pressed() override;
	State* remote_stop() override;
};

#endif /* INC_FSM_SHAREDFSMS_E_STOP_WAITINGFORLOCALRESET_H_ */
