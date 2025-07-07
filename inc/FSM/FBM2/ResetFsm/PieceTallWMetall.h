/*
 * PieceTallWMetall.h
 *
 *  Created on: 04.07.2025
 *      Author: User
 */

#ifndef SRC_FSM_FBM2_RESETFSM_PIECETALLWMETALL_H_
#define SRC_FSM_FBM2_RESETFSM_PIECETALLWMETALL_H_
#include "ContextData.h"
#include "State.h"
#include "IdleReset.h"

class PieceTallWMetall : public State {
public:
	PieceTallWMetall(ContextData* data) : State(data){};
	virtual ~PieceTallWMetall(){};

	void entry() override;
	void exit() override;

	State* clone() override;

	State* error_w_lost() override;
	State* sorted() override;
};

#endif /* SRC_FSM_FBM2_RESETFSM_PIECETALLWMETALL_H_ */
