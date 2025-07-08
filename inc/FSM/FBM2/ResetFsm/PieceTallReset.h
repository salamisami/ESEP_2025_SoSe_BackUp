/*
 * PieceTallReset.h
 *
 *  Created on: 04.07.2025
 *      Author: User
 */

#ifndef SRC_FSM_FBM2_RESETFSM_PIECETALLRESET_H_
#define SRC_FSM_FBM2_RESETFSM_PIECETALLRESET_H_
#include "ContextData.h"
#include "State.h"
#include "IdleReset.h"

class PieceTallReset : public State {
public:
	PieceTallReset(ContextData* data) : State(data){};
	virtual ~PieceTallReset(){};

	void entry() override;
	void exit() override;

	State* clone() override;

	State* sorted() override;
	State* error_w_lost() override;
};

#endif /* SRC_FSM_FBM2_RESETFSM_PIECETALLRESET_H_ */
