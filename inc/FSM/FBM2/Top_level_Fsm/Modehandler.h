/*
 * Modehandler.h
 *
 *  Created on: 02.07.2025
 *      Author: User
 */

#ifndef SRC_FSM_FBM2_TOP_LEVEL_FSM_MODEHANDLER_H_
#define SRC_FSM_FBM2_TOP_LEVEL_FSM_MODEHANDLER_H_

#include "OrthState.h"

class Modehandler : public OrthState{
public:
	Modehandler(Contextdata* data) : OrthState(data, {new IdleIM}) {};
	virtual ~Modehandler() : ~OrthState() { };

	void entry() override;
	void exit() override;
	State* clone() override;

	State* error_c_lost_com() override;
	State* error_c_lost_mqtt() override;

	State* button_estop_pressed() override;
	State* com_button_estop_pressed() override;
	State* remote_stop() override;

};

#endif /* SRC_FSM_FBM2_TOP_LEVEL_FSM_MODEHANDLER_H_ */
