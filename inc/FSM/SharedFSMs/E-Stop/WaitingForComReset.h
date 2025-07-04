/*
 * WaitingForComReset.h
 *
 *  Created on: 03.07.2025
 *      Author: User
 */

#ifndef INC_FSM_SHAREDFSMS_E_STOP_WAITINGFORCOMRESET_H_
#define INC_FSM_SHAREDFSMS_E_STOP_WAITINGFORCOMRESET_H_
#include "State.h"

class WaitingForComReset : public State{
public:
	WaitingForComReset(ContextData* data) : State(data){};
	virtual ~WaitingForComReset(){};

	void entry() override;
	void exit() override;
	State* clone() override;

	State* button_estop_pressed() override;
	State* com_button_estop_pressed() override;
	State* com_button_reset_pressed() override;
	State* remote_stop() override;

};

#endif /* INC_FSM_SHAREDFSMS_E_STOP_WAITINGFORCOMRESET_H_ */
