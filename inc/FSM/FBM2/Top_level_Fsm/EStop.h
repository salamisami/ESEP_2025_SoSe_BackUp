/*
 * EStop.h
 *
 *  Created on: 02.07.2025
 *      Author: User
 */

#ifndef SRC_FSM_FBM2_TOP_LEVEL_FSM_ESTOP_H_
#define SRC_FSM_FBM2_TOP_LEVEL_FSM_ESTOP_H_

#include "HState.h"
#include "ContextData.h"
#include "Modehandler.h"

class EStop : public HState {
public:
	EStop(ContextData* data,State* substate): HState(data, substate, new Modehandler(data)){};
	virtual ~EStop() :{};

	void entry() override;
	void exit() override;
	State* clone() override;

	State* error_c_lost_com() override;
	State* error_c_lost_mqtt() override;
};

#endif /* SRC_FSM_FBM2_TOP_LEVEL_FSM_ESTOP_H_ */
