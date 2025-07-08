/*
 * IdleReset.h
 *
 *  Created on: 04.07.2025
 *      Author: User
 */

#ifndef SRC_FSM_FBM2_RESETFSM_IDLERESET_H_
#define SRC_FSM_FBM2_RESETFSM_IDLERESET_H_
#include "ContextData.h"
#include "State.h"
#include "PieceFlatReset.h"
#include "PieceTallReset.h"
#include "PieceTallWMetall.h"

class IdleReset : public State {
public:
	IdleReset(ContextData* data) : State(data){};
	virtual ~IdleReset(){};

	void entry() override;
	void exit() override;

	State* clone() override;

	State* transfer_start_tall() override;
	State* transfer_start_flat() override;
	State* transfer_start_tall_w_metal() override;
};

#endif /* SRC_FSM_FBM2_RESETFSM_IDLERESET_H_ */
